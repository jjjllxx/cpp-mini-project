cmake_minimum_required(VERSION 3.21)
project(SDK)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wno-pragmas -Wno-comment")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SDK_TARGET suduko)
set(SDK_SOURCES
    I18n.cpp
    Interface.cpp
    Scene.cpp
    Utility.cpp
    main.cpp
)

add_executable(${SDK_TARGET} ${SDK_SOURCES})

set_target_properties(${SDK_TARGET} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")