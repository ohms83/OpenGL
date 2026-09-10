cmake_minimum_required(VERSION 3.31)
project(OpenGL_Engine)

# Enable CTest
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)

message("CMAKE_BUILD_TYPE  ${CMAKE_BUILD_TYPE}")

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})

include(FetchContent)

set(3RD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty)

add_subdirectory(src)
add_subdirectory(3rdparty)

find_package(OpenGL REQUIRED)

message("SOURCES=${SOURCES}")

add_executable(OpenGL_Engine ${SOURCES})

target_link_libraries(OpenGL_Engine
    PRIVATE SDL3::SDL3
    PRIVATE glad
    PRIVATE OpenGL::GL
    PRIVATE assimp::assimp)

target_include_directories(OpenGL_Engine
    PRIVATE ${3RD_PARTY_DIR}/include)