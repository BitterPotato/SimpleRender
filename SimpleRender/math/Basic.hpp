#ifndef BASIC_HPP
#define BASIC_HPP

#include "common/setup.hpp"

namespace math {
    MY_SMALL_NAME_FUNC_DECL int ipart(float x);

    MY_SMALL_NAME_FUNC_DECL float fpart(float x);

    MY_SMALL_NAME_FUNC_DECL float rfpart(float x);

    MY_SMALL_NAME_FUNC_DECL int mround(float x);
}
#include "Basic.inl"

#endif