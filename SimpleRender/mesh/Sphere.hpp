//
// Created by WJ Yang on 2017/9/23.
//

#ifndef SIMPLERENDER_SPHERE_HPP
#define SIMPLERENDER_SPHERE_HPP

#include "Shape.hpp"
#include "math/TVector.hpp"

#define TESS_MODE1

namespace Mesh {
    class Sphere : public Shape {
    public:
        Sphere(fvec3 c, float r) : center(c), radius(r) {}

        MY_COMP_FUNC_DECL void tessellate(vector<FVertex> &outVertexData) const override;

    private:
        fvec3 center;
        float radius;
        int t;

        MY_COMP_FUNC_DECL void callPush(const fvec3 &vertexA, const fvec3 &vertexB, const fvec3 &vertexC,
                      const fvec3 &vertexAB, const fvec3 &vertexBC, const fvec3 &vertexCA,
                      vector<FVertex> &outVertexData) const ;

        MY_COMP_FUNC_DECL void middleof(const fvec3 &vertexThis, const fvec3 &vertexThat, fvec3 &outVertex) const ;

        MY_COMP_FUNC_DECL void subTessellate(const fvec3 &vertexA, const fvec3 &vertexB, const fvec3 &vertexC,
                           vector<FVertex> &outVertexData) const ;
    };
}


#endif //SIMPLERENDER_SPHERE_HPP
