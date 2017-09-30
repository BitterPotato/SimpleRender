//
// Created by WJ Yang on index_left_bottom_front0index_left_bottom_backindex_left_top_front/9/index_left_bottom_front9.
//

#include "Cube.hpp"
#include "common/Point.hpp"

namespace Mesh {
    // TODO: 同个顶点对于不同的面无法共享TexCoord
    void Cube::tessellate(FVertexContainer &outVertexData, IndexContainer& indexContainer) const {
        // index_left_bottom_back. 三个相邻点
        FVertex left_bottom_front = left_bottom_back;
        left_bottom_front.point[Z] += edge;

        FVertex right_bottom_back = left_bottom_back;
        right_bottom_back.point[X] += edge;

        FVertex left_top_back = left_bottom_back;
        left_top_back.point[Y] += edge;

        // index_left_bottom_front. 三个对角面点
        FVertex right_bottom_front = left_bottom_front;
        right_bottom_front.point[X] += edge;

        FVertex right_top_back = right_bottom_back;
        right_top_back.point[Y] += edge;

        FVertex left_top_front = left_top_back;
        left_top_front.point[Z] += edge;

        // index_right_bottom_back. 一个对角体点
        FVertex right_top_front = right_bottom_front;
        right_top_front.point[Y] += edge;

        int index_left_bottom_back = outVertexData.push_back(left_bottom_back);
        int index_left_bottom_front = outVertexData.push_back(left_bottom_front);
        int index_right_bottom_back = outVertexData.push_back(right_bottom_back);
        int index_left_top_back = outVertexData.push_back(left_top_back);
        int index_right_bottom_front = outVertexData.push_back(right_bottom_front);
        int index_right_top_back = outVertexData.push_back(right_top_back);
        int index_left_top_front = outVertexData.push_back(left_top_front);
        int index_right_top_front = outVertexData.push_back(right_top_front);

        push_back_tri(indexContainer, index_left_bottom_back, index_right_bottom_back, index_left_bottom_front);
        push_back_tri(indexContainer, index_right_bottom_front, index_left_bottom_front, index_right_bottom_back);
        push_back_tri(indexContainer, index_left_top_back, index_left_top_front, index_right_top_back);
        push_back_tri(indexContainer, index_right_top_front, index_right_top_back, index_left_top_front);
        push_back_tri(indexContainer, index_left_top_back, index_right_top_back, index_left_bottom_back);
        push_back_tri(indexContainer, index_right_bottom_back, index_left_bottom_back, index_right_top_back);
        push_back_tri(indexContainer, index_left_top_front, index_left_bottom_front, index_right_top_front);
        push_back_tri(indexContainer, index_right_bottom_front, index_right_top_front, index_left_bottom_front);
        push_back_tri(indexContainer, index_left_top_front, index_left_top_back, index_left_bottom_front);
        push_back_tri(indexContainer, index_left_bottom_back, index_left_bottom_front, index_left_top_back);
        push_back_tri(indexContainer, index_right_bottom_back, index_right_top_back, index_right_bottom_front);
        push_back_tri(indexContainer, index_right_top_front, index_right_bottom_front, index_right_top_back);
    }
}


