//
// Created by WJ Yang on 2017/9/22.
//

#ifndef SIMPLERENDER_VERTEX_HPP
#define SIMPLERENDER_VERTEX_HPP

#include "math/TVector.hpp"
#include "Info.hpp"
#include "Point.hpp"

// after viewport
class Vertex {
public:
    Vertex(ivec2 p = ivec2(), Info i = Info(), fvec2 t = fvec2(), float h = 0.0f) :
            point(p), info(i), tex(t), homo(h){}
//    Vertex(const Vertex& vertex) :
//            point(vertex.point), info(vertex.info), tex(vertex.tex), homo(vertex.homo) {}
    ~Vertex();

    MY_OPERATOR_DECL Vertex& operator=(const Vertex& vertex) {
        this->point = vertex.point;
        this->info = vertex.info;
        this->tex = vertex.tex;
        this->homo = vertex.homo;

        return *this;
    }
    MY_OPERATOR_DECL Vertex& operator=(Vertex vertex) {
        swap(*this, vertex);
        return *this;
    }
    MY_SFRIEND_FUNC_DECL void swap(Vertex& first, Vertex& second) {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;

        // by swapping the members of two objects,
        // the two objects are effectively swapped
        swap(first.point, second.point);
        swap(first.info, second.info);
        swap(first.tex, second.tex);
        swap(first.homo, second.homo);
    }
    MY_SMALL_UTIL_DECL void inter(const fvec2& first, const fvec2& second, const fvec2& third, fvec2& out, const fvec3& ratio) ;

//    private:
    ivec2 point;
    Info info;
    fvec2 tex;
    // save the homogeneous divide value
    float homo;
};

#include "Vertex.inl"

#endif //SIMPLERENDER_VERTEX_HPP
