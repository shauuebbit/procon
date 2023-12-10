cmake_minimum_required(VERSION 3.14)
project(procon)

set(CMAKE_CXX_STANDARD 23)

add_compile_options(-fsplit-stack)
add_compile_options(-Wall -Wextra)

include_directories(library)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(library)
add_subdirectory(test)

add_executable(Main main.cpp)
