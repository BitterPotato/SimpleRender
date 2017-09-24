//
// Created by WJ Yang on 2017/9/22.
//

#ifndef SIMPLERENDER_INFO_H
#define SIMPLERENDER_INFO_H

#include "material/Rgba.hpp"

class Info {
public:
    Info(RGBA b = RGBA(), float depth = 0.0f, int stencil = 0);
    Info(const Info& info);
    Info(Info&& info) noexcept;
    ~Info();

    MY_OPERATOR_DECL Info& operator=(const Info& info);
    MY_OPERATOR_DECL Info& operator=(Info info);
    MY_OPERATOR_DECL Info& operator=(Info&& info);
    MY_OPERATOR_DECL Info& operator*(const float ratio);
    MY_OPERATOR_DECL Info operator*(const float ratio) const;
    MY_OPERATOR_DECL Info& operator*=(const float ratio);

    MY_SFRIEND_FUNC_DECL void swap(Info& first, Info& second);
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


#endif //SIMPLERENDER_INFO_H
