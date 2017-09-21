cmake_minimum_required(VERSION 3.8.2)
project(SimpleRender)

set(CMAKE_CXX_STANDARD 17)

#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

#message( STATUS ${CMAKE_SOURCE_DIR} )
#message( WARNING ${CMAKE_SOURCE_DIR}/SimpleRender/lib/ )
link_directories("${CMAKE_SOURCE_DIR}/SimpleRender/lib/")

set(SOURCE_FILES
        SimpleRender/format/scf_parser.hpp
        SimpleRender/geometry/Triangle.hpp
        SimpleRender/main/SimpleDelegate.cpp
        SimpleRender/main/SimpleDelegate.hpp
        SimpleRender/main/SimpleRender.cpp
        SimpleRender/material/color.cpp
        SimpleRender/material/color.hpp
        SimpleRender/math/basic.cpp
        SimpleRender/math/basic.hpp
        SimpleRender/math/tmatrix.hpp
        SimpleRender/math/tmatrix_gl.hpp
        SimpleRender/math/tmatrix_rotate.hpp
        SimpleRender/math/tmatrix_trans.hpp
        SimpleRender/math/tvector.hpp
        SimpleRender/math/tvector_trans.hpp
        SimpleRender/mesh/shape.hpp
        SimpleRender/mesh/sphere.cpp
        SimpleRender/pipeline/blend.cpp
        SimpleRender/pipeline/blend.hpp
        SimpleRender/pipeline/bsp.cpp
        SimpleRender/pipeline/bsp.hpp
        SimpleRender/pipeline/frag_shader.cpp
        SimpleRender/pipeline/frag_shader.hpp
        SimpleRender/pipeline/gl_utils.hpp
        SimpleRender/pipeline/raster_stage.hpp
        SimpleRender/pipeline/render_state.cpp
        SimpleRender/pipeline/render_state.hpp
        SimpleRender/pipeline/render_struc.hpp
        SimpleRender/pipeline/stage_flow.cpp
        SimpleRender/pipeline/stage_flow.hpp
        SimpleRender/pipeline/vertex_shader.cpp
        SimpleRender/pipeline/vertex_shader.hpp
        SimpleRender/platform/framebuffer.hpp
        SimpleRender/platform/uniform.hpp
        SimpleRender/platform/winbuffer.cpp
        SimpleRender/platform/winform.cpp
        SimpleRender/raster/Frag.hpp
        SimpleRender/raster/FragCache.cpp
        SimpleRender/raster/FragCache.hpp
        SimpleRender/raster/Line.hpp
        SimpleRender/raster/Point.hpp
        SimpleRender/raster/Texture.hpp
        SimpleRender/raster/Triangle.hpp
        SimpleRender/third/FreeImage.h
        SimpleRender/third/FreeImagePlus.h
        SimpleRender/util/func.hpp SimpleRender/raster/FITexture.cpp)

add_executable(SimpleRender ${SOURCE_FILES})

target_link_libraries(SimpleRender -lFreeImage)