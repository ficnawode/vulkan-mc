cmake_minimum_required(VERSION 3.23)

project(vk-mc C CXX)

set(CMAKE_CXX_STANDARD 20)

include(cmake/fetch_content.cmake)
include(cmake/find_packages.cmake)

enable_testing()
include(GoogleTest)

add_subdirectory(thirdparty)
add_subdirectory(exec)
add_subdirectory(lib)
add_subdirectory(test)
