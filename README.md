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

![](http://oi0xi3dzx.bkt.clouddn.com/graphics/theory/orthographic.gif)

### perspective circumstance

![](http://oi0xi3dzx.bkt.clouddn.com/graphics/theory/perspective.gif)

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

