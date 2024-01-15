cmake_minimum_required(VERSION 3.0)

project(toy-rasterizer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

file(GLOB SOURCES "src/*.cpp")
add_executable(toy-rasterizer ${SOURCES})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(toy-rasterizer ${SDL2_LIBRARY})