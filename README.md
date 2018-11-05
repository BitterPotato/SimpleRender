# Simple Render

A small render engine written in C++11.

## Done

* basic math operations

* simplified pipeline

  * vertex transformation

  * clip by partition

  * line/ triangle rasterization

    > wireframe mode

  * blend operations and factors

    > rgba to hsv

* perspective-right texture mapping

* simplified custom file format

* BSP/ z-buffer

* First-person Camera 

* Meshes

  * cube/ sphere
  * vertex-index structures

## TODO

* Phong
* Ray tracing
* ...

## Screenshots

### orthographic circumstance

![](http://45.63.110.68/uploads/big/6cb5ec0e4e26bb1b2c7449f1aa81fa5c.gif)

### perspective circumstance

![](http://45.63.110.68/uploads/big/9c6ad23ce502a4f3cee7a38201c6853d.gif)

## Getting Started

1. Install cmake and mingw

2. build
```
cmake -G "MinGW Makefiles"
mingw32-make
```


## Acknowledgements

* [如何开始用 C++ 写一个光栅化渲染器](https://www.zhihu.com/question/24786878)
* [Fundamentals of Computer Graphics](https://book.douban.com/subject/2116178/)

