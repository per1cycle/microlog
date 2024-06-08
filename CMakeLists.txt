cmake_minimum_required(VERSION 3.5)

project(Log)
set(CMAKE_BUILD_TYPE Debug)
include_directories(
  ${CMAKE_SOURCE_DIR}/include
)

add_subdirectory(src)

add_subdirectory(sample)