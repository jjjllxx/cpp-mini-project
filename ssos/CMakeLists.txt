cmake_minimum_required(VERSION 3.21)
project(SSOS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wno-pragmas -Wno-comment")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SSOS_TARGET ssos)
set(SSOS_SOURCES
    Interface.cpp
    Menu.cpp
    Buyer.cpp
    Seller.cpp
    main.cpp
)

add_executable(${SSOS_TARGET} ${SSOS_SOURCES})

set_target_properties(${SSOS_TARGET} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")