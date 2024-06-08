cmake_minimum_required(VERSION 3.5)

project(Log)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD_REQUIRED 17)
include_directories(
  ${CMAKE_SOURCE_DIR}/include
)

add_subdirectory(src)

add_subdirectory(sample)