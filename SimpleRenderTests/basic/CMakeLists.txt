include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(SimpleRenderTests SimpleRenderTests.cpp)

target_link_libraries(SimpleRenderTests gtest gtest_main SimpleRenderLib)