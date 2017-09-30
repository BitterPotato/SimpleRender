//
// Created by WJ Yang on 2017/9/23.
//

#ifndef SIMPLERENDER_SPHERE_HPP
#define SIMPLERENDER_SPHERE_HPP

#include "Shape.hpp"
#include "math/TVector.hpp"

namespace Mesh {
    class Sphere : public Shape {
    public:
        Sphere(FVertex& c, float r) : center(c), radius(r) {}

        MY_COMP_FUNC_DECL void
        tessellate(FVertexContainer &outVertexData, IndexContainer &indexContainer) const override;

    private:
        FVertex& center;
        float radius;
        int t;

        MY_COMP_FUNC_DECL void
        middleof(const FPoint3D &pointThis, const FPoint3D &pointThat, FPoint3D &outPoint) const;
        MY_COMP_FUNC_DECL FVertex toFVertex(const FPoint3D& point) const;
        MY_COMP_FUNC_DECL void subTessellate(const FPoint3D &pointA, const FPoint3D &pointB, const FPoint3D &pointC,
                                   const int indexA, const int indexB, const int indexC,
                                   FVertexContainer& outputVertexData, IndexContainer& indexContainer, int n) const;
    };
}


#endif //SIMPLERENDER_SPHERE_HPP
