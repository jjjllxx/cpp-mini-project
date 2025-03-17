cmake_minimum_required(VERSION 3.16)

project(JP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wno-pragmas -Wno-comment")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(JP_TARGET JsonParser)

set(JP_SOURCES
    main.cpp
)

include(json/CMakeLists.txt)

add_executable(${JP_TARGET} ${JP_SOURCES})

target_include_directories(${JP_TARGET} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)