//
// Created by WJ Yang on 2017/9/22.
//

#include "Frag.hpp"

Frag& Frag::operator=(Frag frag) {
    swap(*this, frag);
    return *this;
}
Frag& Frag::operator=(Frag&& frag) noexcept {
    if (&frag != this) {
        point = frag.point;
        info = frag.info;
    }
    return *this;
}
void swap(Frag& first, Frag& second) // nothrow
{
    // enable ADL (not necessary in our case, but good practice)
    using std::swap;

    // by swapping the members of two objects,
    // the two objects are effectively swapped
    swap(first.point, second.point);
    swap(first.info, second.info);
}