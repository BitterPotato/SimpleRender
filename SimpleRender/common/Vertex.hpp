//
// Created by WJ Yang on 2017/9/22.
//

#ifndef SIMPLERENDER_VERTEX_HPP
#define SIMPLERENDER_VERTEX_HPP

#include "Info.hpp"
#include "Point.hpp"

// after viewport
class Vertex {
public:
    Vertex(IPoint2D p = IPoint2D(), Info i = Info(), TexCoord t = TexCoord(), float h = 0.0f) :
            point(p), info(i), tex(t), homo(h){}
//    Vertex(const Vertex& vertex) :
//            point(vertex.point), info(vertex.info), tex(vertex.tex), homo(vertex.homo) {}
    ~Vertex();

    MY_OPERATOR_DECL Vertex& operator=(const Vertex& vertex);
    MY_OPERATOR_DECL Vertex& operator=(Vertex vertex);
    MY_SFRIEND_FUNC_DECL void swap(Vertex& first, Vertex& second);
    MY_SMALL_UTIL_DECL void inter(const TexCoord& first, const TexCoord& second, const TexCoord& third, TexCoord& out, const fvec3& ratio);


//    private:
    IPoint2D point;
    Info info;
    TexCoord tex;
    // save the homogeneous divide value
    float homo;
};


#endif //SIMPLERENDER_VERTEX_HPP
