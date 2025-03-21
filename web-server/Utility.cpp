#include "Utility.h"

#include <arpa/inet.h>
#include <array>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>

void ws::startServer()
{
    u_short            port = 6579; // 默认监听端口号 port 为6379
    struct sockaddr_in clientName {};
    socklen_t          clientNameLen = sizeof(clientName);

    const int serverSock = ws::startup(port);

    std::cout << "http server_sock is " << serverSock << '\n';
    std::cout << "http running on port " << port << '\n';

    while (true)
    {
        const int clientSock = accept(serverSock,
                                      (struct sockaddr*) &clientName,
                                      &clientNameLen);

        std::cout << "New connection....  ip: " << inet_ntoa(clientName.sin_addr) << ", port: "
                  << ntohs(clientName.sin_port) << '\n';

        if (clientSock == -1)
        {
            ws::dieWithError("accept");
        }

        std::thread newThread(ws::acceptRequest, clientSock);
        newThread.detach();
    }
    close(serverSock);
}

//  处理监听到的 HTTP 请求
void ws::acceptRequest(const int client)
{
    const std::string buf    = ws::getHttpLine(client);
    std::size_t       idx    = buf.find(' ');
    const std::string method = buf.substr(0, idx);

    if (strcasecmp(method.c_str(), "GET") != 0 && strcasecmp(method.c_str(), "POST") != 0)
    {
        ws::onUnimplemented(client);
        return;
    }

    bool shouldUseCgi = strcasecmp(method.c_str(), "POST") == 0;

    while (buf[idx] == ' ' && idx < buf.size())
    {
        idx++;
    }

    std::string url;
    while (buf[idx] != ' ' && idx < buf.size())
    {
        url.push_back(buf[idx]);
        idx++;
    }

    // GET请求url可能会带有?,有查询参数
    std::size_t queryIdx = 0;
    if (strcasecmp(method.c_str(), "GET") == 0)
    {
        while (url[queryIdx] != '?' && url[queryIdx] != '\0')
        {
            queryIdx++;
        }

        /* 如果有?表明是动态请求, 开启cgi */
        if (url[queryIdx] == '?')
        {
            shouldUseCgi  = true;
            url[queryIdx] = '\0';
            queryIdx++;
        }
    }

    // 如果请求参数为目录, 自动打开test.html
    const std::string path = std::filesystem::is_directory(url) == true
                                 ? "httpdocs" + url + "test.html"
                                 : "httpdocs" + url;

    if (std::filesystem::exists(path) == false)
    {
        ws::onNotFound(client);
    }
    else
    {
        const std::filesystem::perms perm = std::filesystem::status(path).permissions();
        if ((perm & std::filesystem::perms::owner_exec) != std::filesystem::perms::none
            || (perm & std::filesystem::perms::group_exec) != std::filesystem::perms::none
            || (perm & std::filesystem::perms::others_exec) != std::filesystem::perms::none)
        {
            shouldUseCgi = true;
        }

        shouldUseCgi == false
            ? ws::serveFile(client, path)
            : ws::executeCgi(client, path, method, url.substr(queryIdx));
    }

    close(client);
    std::cout << "connection close....client:" << client << ".\n";
}

void ws::dieWithError(const std::string& sc)
{
    perror(sc.c_str());
    exit(1);
}

// 执行cgi动态解析
void ws::executeCgi(const int          client,
                    const std::string& path,
                    const std::string& method,
                    const std::string& queryStr)
{
    int contentLength = -1;
    // 默认字符
    std::cout << path << '\n'
              << method << '\n'
              << queryStr << '\n';
    if (strcasecmp(method.c_str(), "GET") == 0)
    {
        std::string buf = ws::getHttpLine(client);
        while (buf.size() > 0 && "\n" != buf)
        {
            buf = ws::getHttpLine(client);
        }
    }
    else
    {
        std::string buf = ws::getHttpLine(client);
        while (buf.size() > 0 && "\n" != buf)
        {
            if (buf.find("Content-Length:") != std::string::npos)
            {
                contentLength = std::stoi(buf.substr(16));
            }

            buf = ws::getHttpLine(client);
        }

        if (contentLength == -1)
        {
            ws::onBadRequest(client);
            return;
        }
    }

    std::cout << "content length: " << contentLength << "\n";

    std::array<int, 2> cgiOutput {};
    std::array<int, 2> cgiInput {};

    if (pipe(cgiOutput.data()) < 0 || pipe(cgiInput.data()) < 0)
    {
        ws::onCannotExecute(client);
        return;
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        ws::onCannotExecute(client);
        return;
    }

    if (pid == 0) /* 子进程: 运行CGI 脚本 */
    {
        dup2(cgiInput[0], 0);
        dup2(cgiOutput[1], 1);

        close(cgiOutput[0]); // 关闭了cgi_output中的读通道
        close(cgiInput[1]);  // 关闭了cgi_input中的写通道

        setenv("REQUEST_METHOD", method.c_str(), 1);

        strcasecmp(method.c_str(), "GET") == 0
            ? setenv("QUERY_STRING", queryStr.c_str(), 1)
            : setenv("CONTENT_LENGTH", std::to_string(contentLength).c_str(), 1);

        execl(path.c_str(), path.c_str(), nullptr); // 执行CGI脚本
        exit(0);
    }
    else
    {
        close(cgiOutput[1]);
        close(cgiInput[0]);

        char c = 0;
        if (strcasecmp(method.c_str(), "POST") == 0)
        {
            for (int i = 0; i < contentLength; i++)
            {
                if (recv(client, &c, 1, 0) <= 0)
                {
                    std::cerr << "Failed to read from client\n";
                    break;
                }

                if (write(cgiInput[1], &c, 1) <= 0)
                {
                    std::cerr << "Failed to write to CGI script\n";
                    break;
                }
            }
        }

        const std::string buf = "HTTP/1.0 200 OK\r\n";
        send(client, buf.c_str(), buf.size(), 0);
        // 读取cgi脚本返回数据
        while (read(cgiOutput[0], &c, 1) > 0)
        {
            // 发送给浏览器
            if (send(client, &c, 1, 0) <= 0)
            {
                std::cerr << "Failed to send to client\n";
                break;
            }
        }

        // 运行结束关闭
        close(cgiOutput[0]);
        close(cgiInput[1]);

        int status = 0;
        waitpid(pid, &status, 0);
    }
}

// 解析一行http报文
std::string ws::getHttpLine(const int client)
{
    char c = '\0';

    std::string buf;

    while (c != '\n')
    {
        if (std::size_t n = recv(client, &c, 1, 0);
            n > 0)
        {
            if (c == '\r')
            {
                n = recv(client, &c, 1, MSG_PEEK);
                if (n > 0 && c == '\n')
                {
                    recv(client, &c, 1, 0);
                }
                else
                {
                    c = '\n';
                }
            }
            buf.push_back(c);
        }
        else
        {
            c = '\n';
        }
    }

    return buf;
}

// 如果不是CGI文件，也就是静态文件，直接读取文件返回给请求的http客户端即可
void ws::serveFile(const int          client,
                   const std::string& filename)
{
    std::string buf = ws::getHttpLine(client);

    while (buf.size() > 0 && buf != "\n")
    {
        buf = ws::getHttpLine(client);
    }

    // 打开文件
    if (std::ifstream resource(filename, std::ios::in);
        resource.is_open() == false)
    {
        ws::onNotFound(client);
    }
    else
    {
        ws::onHeaders(client, filename);

        std::string buf;
        // Read line by line using getline, which reads a full line including spaces
        while (std::getline(resource, buf))
        {
            // Send the current line to the client
            send(client, buf.c_str(), buf.size(), 0);
        }
        resource.close();
    }
}

// 启动服务端
int ws::startup(u_short& port)
{
    // 设置http socket
    const int httpd = socket(PF_INET, SOCK_STREAM, 0);
    if (httpd == -1)
    {
        ws::dieWithError("socket"); // 连接失败
    }

    const int option = 1;

    setsockopt(httpd, SOL_SOCKET, SO_REUSEADDR, (void*) &option, sizeof(option));

    struct sockaddr_in name {};
    memset(&name, 0, sizeof(name));
    name.sin_family      = AF_INET;
    name.sin_port        = htons(port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(httpd, (struct sockaddr*) &name, sizeof(name)) < 0)
    {
        ws::dieWithError("bind"); // 绑定失败
    }

    if (port == 0) /*动态分配一个端口 */
    {
        socklen_t namelen = sizeof(name);
        if (getsockname(httpd, (struct sockaddr*) &name, &namelen) == -1)
        {
            ws::dieWithError("getsockname");
        }
        port = ntohs(name.sin_port);
    }

    if (listen(httpd, 5) < 0)
    {
        ws::dieWithError("listen");
    }

    return httpd;
}

void ws::onHeaders(const int client, const std::string& filename)
{
    (void) filename; /* could use filename to determine file type */
                     // 发送HTTP头
    std::ostringstream buf;
    buf << "HTTP/1.0 200 OK\r\n"
        << SERVER_STRING
        << "Content-Type: text/html\r\n"
        << "\r\n";

    send(client, buf.str().c_str(), buf.str().size(), 0);
}

void ws::onBadRequest(const int client)
{
    std::ostringstream buf;

    buf << "HTTP/1.0 400 BAD REQUEST\r\n"
        << "Content-Type: text/html\r\n"
        << "\r\n"
        << "<P>Your browser sent a bad request, "
        << "such as a POST without a Content-Length.\r\n";

    send(client, buf.str().c_str(), buf.str().size(), 0);
}

void ws::onCannotExecute(const int client)
{
    std::ostringstream buf;

    buf << "HTTP/1.0 500 Internal Server Error\r\n"
        << "Content-type: text/html\r\n"
        << "\r\n"
        << "<P>Error prohibited CGI execution.\r\n";

    send(client, buf.str().c_str(), buf.str().size(), 0);
}

void ws::onNotFound(const int client)
{
    std::ostringstream buf;
    buf << "HTTP/1.0 404 NOT FOUND\r\n"
        << SERVER_STRING
        << "Content-Type: text/html\r\n"
        << "\r\n"
        << "<HTML><TITLE>Not Found</TITLE>\r\n"
        << "<BODY><P>The server could not fulfill\r\n"
        << "your request because the resource specified\r\n"
        << "is unavailable or nonexistent.\r\n"
        << "</BODY></HTML>\r\n";

    send(client, buf.str().c_str(), buf.str().size(), 0);
}

void ws::onUnimplemented(const int client)
{
    std::ostringstream buf;

    buf << "HTTP/1.0 501 Method Not Implemented\r\n"
        << SERVER_STRING
        << "Content-Type: text/html\r\n"
        << "\r\n"
        << "<HTML><HEAD><TITLE>Method Not Implemented\r\n"
        << "</TITLE></HEAD>\r\n"
        << "<BODY><P>HTTP request method not supported.\r\n"
        << "</BODY></HTML>\r\n";

    send(client, buf.str().c_str(), buf.str().size(), 0);
}