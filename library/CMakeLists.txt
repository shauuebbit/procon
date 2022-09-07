cmake_minimum_required(VERSION 3.14)
project(procon_library)

set(CMAKE_CXX_STANDARD 17)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

add_library(ProconLibrary INTERFACE)
