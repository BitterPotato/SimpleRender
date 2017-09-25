//
// Created by WJ Yang on 2017/9/22.
//

#include "Point.hpp"

bool isInVisualBody(const FPoint4D& point) {
    return point[X] >= -point[W] && point[X] <= point[W]
           && point[Y] >= -point[W] && point[Y] <= point[W]
           && point[Z] >= -point[W] && point[Z] <= point[W];
}