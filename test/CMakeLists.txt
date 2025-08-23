cmake_minimum_required(VERSION 3.14)
project(procon_library_test)

set(CMAKE_CXX_STANDARD 23)

add_compile_options(-fsplit-stack)
add_compile_options(-Wall -Wextra)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

if(WIN32)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_subdirectory(data_structure)
add_subdirectory(geometry)
add_subdirectory(graph)
add_subdirectory(math)
add_subdirectory(string)
add_subdirectory(util)
