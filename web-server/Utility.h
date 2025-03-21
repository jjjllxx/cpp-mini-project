#pragma once

#include <string>

namespace ws
{
const std::string SERVER_STRING = "Server: Random Name's http/0.1.0\r\n";

void startServer();
void acceptRequest(const int client);
void dieWithError(const std::string& sc);
void executeCgi(const int          client,
                const std::string& path,
                const std::string& method,
                const std::string& queryStr);
void serveFile(const int          client,
               const std::string& filename);

int         startup(u_short& port);
std::string getHttpLine(const int client);

void onHeaders(const int          client,
               const std::string& filename);
void onBadRequest(const int client);
void onCannotExecute(const int client);
void onNotFound(const int client);
void onUnimplemented(const int client);
} // namespace ws