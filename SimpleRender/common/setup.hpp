//
// Created by WJ Yang on 2017/9/22.
//

#ifndef SIMPLERENDER_SETUP_HPP
#define SIMPLERENDER_SETUP_HPP

#define MY_OPERATOR_DECL inline
#define MY_COMP_FUNC_DECL
#define MY_SMALL_FUNC_DECL inline
#define MY_SMALL_NAME_FUNC_DECL inline
#define MY_SMALL_UTIL_DECL inline static
#define MY_SMALL_STORAGE_DECL static inline
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
#include <cstring>

using std::cout;
using std::cin;
using std::endl;
using std::max;
using std::min;
using std::string;
using std::vector;
using std::unique_ptr;
using std::shared_ptr;
using std::make_shared;
using std::abs;
using std::tan;
using std::sin;
using std::cos;
using std::sqrt;
using std::logic_error;
using std::function;
using std::memset;

template<typename T>
MY_SMALL_STORAGE_DECL void myswap(T* a, T* b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * copy from winuser.h
 */
#define VK_LEFT           0x25
#define VK_UP             0x26
#define VK_RIGHT          0x27
#define VK_DOWN           0x28
#define VK_F1             0x70
#define VK_F2             0x71
#define VK_F3             0x72
#define VK_F4             0x73
#define VK_F5             0x74
#define VK_F6             0x75

#endif //SIMPLERENDER_SETUP_HPP
