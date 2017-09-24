//
// Created by WJ Yang on 2017/9/22.
//

#ifndef SIMPLERENDER_SETUP_HPP
#define SIMPLERENDER_SETUP_HPP

#define MY_OPERATOR_DECL inline
#define MY_COMP_FUNC_DECL
#define MY_SMALL_FUNC_DECL inline
#define MY_SMALL_UTIL_DECL inline static
#define MY_UTIL_DECL static
#define MY_STORAGE_FUNC_DECL static
#define MY_NFRIEND_FUNC_DECL friend
#define MY_SFRIEND_FUNC_DECL inline friend

#include <iostream>
#include <algorithm>
#include <assert.h>
#include <vector>
#include <string>
#include <memory>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <functional>

using std::cout;
using std::cin;
using std::endl;
using std::max;
using std::min;
using std::string;
using std::vector;
using std::unique_ptr;
using std::shared_ptr;
using std::abs;
using std::tan;
using std::sin;
using std::cos;
using std::sqrt;
using std::logic_error;
using std::function;

template<typename T>
inline void myswap(T* a, T* b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

#endif //SIMPLERENDER_SETUP_HPP
