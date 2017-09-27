#ifndef BUFFER_INL
#define BUFFER_INL

#include "FrameBuffer.hpp"

void FrameBuffer::linkForm(void* ptr) {
    fbuffer = (unsigned char*)ptr;
}
void FrameBuffer::setBufferStorage(const int width, const int height) {
    //if (fbuffer)
    //	free(fbuffer);
    this->width = width;
    this->height = height;
    memset(fbuffer, 0, width*height * 4);
}

#endif