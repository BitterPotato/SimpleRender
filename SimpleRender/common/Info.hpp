//
// Created by WJ Yang on 2017/9/22.
//

#ifndef SIMPLERENDER_INFO_HPP
#define SIMPLERENDER_INFO_HPP

#include "setup.hpp"
#include "math/TVector.hpp"
#include "material/Rgba.hpp"

class Info {
public:
    Info(RGBA b = RGBA(), float d = 0.0f, int s = 0) :
            rgba(b), depth(d), stencil(s){
#ifdef CONSTRUCT_INFO_ENABLE
        cout << "Info: constructor" << endl;
#endif
    }
//    Info(const Info& info) {
//        rgba = info.rgba;
//        depth = info.depth;
//        stencil = info.stencil;
//    }
//    Info(Info&& info) noexcept {
//        cout << "move constructor";
//    }
    ~Info();

    MY_OPERATOR_DECL Info& operator=(const Info& info) {
        assign(info);
        return *this;
    }
//    MY_OPERATOR_DECL Info& operator=(Info&& info) noexcept;
    MY_OPERATOR_DECL Info& operator*(const float ratio) {
        scale(ratio);
        return *this;
    }
    // TODO: test move
    MY_OPERATOR_DECL Info operator*(const float ratio) const {
        Info info = Info(*this);
        info.scale(ratio);
        return info;
    }
    MY_OPERATOR_DECL Info& operator*=(const float ratio) {
        scale(ratio);
        return *this;
    }

    MY_SFRIEND_FUNC_DECL void swap(Info& first, Info& second) {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;

        // by swapping the members of two objects,
        // the two objects are effectively swapped
        // attention: the input parameter aren't pointers, if RGBA implements
        // the swap function, then it will delivery
        swap(first.rgba, second.rgba);
        swap(first.depth, second.depth);
        swap(first.stencil, second.stencil);
    }
    // assert: move
    MY_SFRIEND_FUNC_DECL Info inter(const Info& from, const Info& to, const float t);
    MY_SFRIEND_FUNC_DECL void interDepth(const Info& first, const Info& second, const Info& third, Info& out, const fvec3& ratio);

    MY_NFRIEND_FUNC_DECL class Vertex;
//private:
    // depth can be integer, but that needs one more step:
    // map the z \in (n, f) -> (0, B-1)
    // for simplicity, just use float
    RGBA rgba;
    float depth;
    int stencil;
private:

    MY_SMALL_FUNC_DECL void assign(const Info& info);
    MY_SMALL_FUNC_DECL void scale(const float ratio);

//    static tuple<int, int, int, int, float, int> typeinfo = make_tuple(1, 1, 1, 1, 1.0f, 1);
};

#include "Info.inl"

#endif //SIMPLERENDER_INFO_H
