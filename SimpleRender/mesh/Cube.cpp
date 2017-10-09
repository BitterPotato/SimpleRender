//
// Created by WJ Yang on index_left_bottom_front0index_left_bottom_backindex_left_top_front/9/index_left_bottom_front9.
//

#include "Cube.hpp"
#include "common/Point.hpp"

namespace Mesh {
    // TODO: 同个顶点对于不同的面无法完美共享TexCoord，至少会有一对面被献祭
    // 如下我们献祭Top and Bottom
    void Cube::tessellate(FVertexContainer &outVertexData, IndexContainer& indexContainer) const {
        TexCoord tex_left_bottom = TexCoord(0.0f, 0.0f);
        TexCoord tex_left_top = TexCoord(0.0f, 1.0f);
        TexCoord tex_right_bottom = TexCoord(1.0f, 0.0f);
        TexCoord tex_right_top = TexCoord(1.0f, 1.0f);

        left_bottom_back.tex = tex_left_bottom;

        // index_left_bottom_back. 三个相邻点
        FVertex left_bottom_front = left_bottom_back;
        left_bottom_front.point[Z] += edge;
        left_bottom_front.tex = tex_right_bottom;

        FVertex right_bottom_back = left_bottom_back;
        right_bottom_back.point[X] += edge;
        right_bottom_back.tex = tex_right_bottom;

        FVertex left_top_back = left_bottom_back;
        left_top_back.point[Y] += edge;
        left_top_back.tex = tex_left_top;

        // index_left_bottom_front. 三个对角面点
        FVertex right_bottom_front = left_bottom_front;
        right_bottom_front.point[X] += edge;
        right_bottom_front.tex = tex_left_bottom;

        FVertex right_top_back = right_bottom_back;
        right_top_back.point[Y] += edge;
        right_top_back.tex = tex_right_top;

        FVertex left_top_front = left_top_back;
        left_top_front.point[Z] += edge;
        left_top_front.tex = tex_right_top;

        // index_right_bottom_back. 一个对角体点
        FVertex right_top_front = right_bottom_front;
        right_top_front.point[Y] += edge;
        right_top_front.tex = tex_left_top;

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
        
//        push_back_tri(indexContainer, 0, 2, 1);
//        push_back_tri(indexContainer, 4, 1, 2);
//        push_back_tri(indexContainer, 3, 6, 5);
//        push_back_tri(indexContainer, 7, 5, 6);
//        push_back_tri(indexContainer, 3, 5, 0);
//        push_back_tri(indexContainer, 2, 0, 5);
//        push_back_tri(indexContainer, 6, 1, 7);
//        push_back_tri(indexContainer, 4, 7, 1);
//        push_back_tri(indexContainer, 6, 3, 1);
//        push_back_tri(indexContainer, 0, 1, 3);
//        push_back_tri(indexContainer, 2, 5, 4);
//        push_back_tri(indexContainer, 7, 4, 5);
    }
}


