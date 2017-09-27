set(SOURCE_FILES
        main/SimpleDelegate.cpp
        main/SimpleDelegate.hpp
        main/SimpleRender.cpp
        material/Rgba.cpp
        material/Rgba.hpp
        material/Rgba.inl
        math/Basic.hpp
        math/TMatrix.hpp
        math/TMatrix_Gl.hpp
        math/TMatrix_Rotate.hpp
        math/TMatrix_Trans.hpp
        math/TMatrix_Gl.inl
        math/TMatrix_Rotate.inl
        math/TMatrix_Trans.inl
        math/TVector.hpp
        math/TVector_Trans.hpp
        math/TVector_Trans.inl
        pipeline/BlendOptions.cpp
        pipeline/BlendOptions.hpp
        pipeline/BSPTree.cpp
        pipeline/BSPTree.hpp
        pipeline/MyFragShader.cpp
        pipeline/MyFragShader.hpp
        pipeline/gl_utils.hpp
        pipeline/RenderState.cpp
        pipeline/RenderState.hpp
        pipeline/RenderSetup.hpp
        pipeline/Pipeline.cpp
        pipeline/Pipeline.hpp
        pipeline/MyVertexShader.cpp
        pipeline/MyVertexShader.hpp
        platform/FrameBuffer.hpp
        platform/Form.hpp
        platform/FrameBuffer.cpp
        raster/FragCache.cpp
        raster/FragCache.hpp
        material/Texture.hpp
        raster/Triangle.hpp
        raster/Triangle.cpp
        third/FreeImage.h
        third/FreeImagePlus.h
        pipeline/MyVertexShader.hpp
        pipeline/MyFragShader.hpp
        material/FITexture.hpp
        material/FITexture.cpp common/Info.cpp common/Info.hpp material/Hsv.cpp material/Hsv.hpp common/Vertex.cpp common/Vertex.hpp common/setup.hpp common/FVertex.cpp common/FVertex.hpp common/Point.cpp common/Point.hpp common/Frag.cpp common/Frag.hpp geometry/Shape2D.cpp geometry/Shape2D.hpp geometry/Triangle2D.cpp geometry/Triangle2D.hpp format/Parser.cpp format/Parser.hpp mesh/Shape.cpp mesh/Shape.hpp mesh/Sphere.cpp mesh/Sphere.hpp geometry/Shape3D.cpp geometry/Shape3D.hpp geometry/Triangle3D.cpp geometry/Triangle3D.hpp raster/Raster.cpp raster/Raster.hpp platform/WinForm.cpp platform/WinForm.hpp pipeline/VertexShader.hpp pipeline/FragShader.hpp raster/Line.cpp raster/Line.hpp raster/Point.cpp raster/Point.hpp)

add_executable(SimpleRender ${SOURCE_FILES})
add_library(SimpleRenderLib ${SOURCE_FILES})
#set_source_files_properties(PROP)

target_link_libraries(SimpleRender -lFreeImage)