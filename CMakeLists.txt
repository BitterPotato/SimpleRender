cmake_minimum_required(VERSION 3.8.2)
project(SimpleRender)

set(CMAKE_CXX_STANDARD 17)

include_directories(SimpleRender)
link_directories("${CMAKE_SOURCE_DIR}/SimpleRender/lib/")

add_subdirectory(SimpleRender)
add_subdirectory(SimpleRenderTests)

