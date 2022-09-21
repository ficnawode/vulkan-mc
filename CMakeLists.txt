cmake_minimum_required(VERSION 3.23)

project(your_project_name_here C CXX)

set(CMAKE_CXX_STANDARD 20)

include(cmake/fetch_content.cmake)

enable_testing()
add_subdirectory(ThirdParty/glfw)
add_subdirectory(ThirdParty/glm)

include(GoogleTest)
include(cmake/find_packages.cmake)
include(cmake/compile_shaders.cmake)

add_subdirectory(exec)
add_subdirectory(lib)
add_subdirectory(test)
