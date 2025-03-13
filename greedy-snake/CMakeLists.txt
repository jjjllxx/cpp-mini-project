cmake_minimum_required(VERSION 3.21)
project(GS)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wno-pragmas -Wno-comment")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(GS_TARGET gs)
set(GS_SOURCES
    Controller.cpp
    Food.cpp
    Map.cpp
    Point.cpp
    Snake.cpp
    StartInterface.cpp
    Utils.cpp
    main.cpp
)

add_executable(${GS_TARGET} ${GS_SOURCES})
target_link_libraries(${GS_TARGET} ${CURSES_LIBRARIES})

set_target_properties(${GS_TARGET} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")