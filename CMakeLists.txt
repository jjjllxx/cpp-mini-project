cmake_minimum_required(VERSION 3.21)
project(SIMS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wno-pragmas -Wno-comment")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SIMS_TARGET sims)
set(SIMS_SOURCES
    Interface.cpp
    Staff.cpp
    Student.cpp
    main.cpp
)

add_executable(${SIMS_TARGET} ${SIMS_SOURCES})

set_target_properties(${SIMS_TARGET} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")