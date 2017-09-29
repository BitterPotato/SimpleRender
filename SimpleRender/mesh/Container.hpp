//
// Created by WJ Yang on 2017/9/28.
//

#ifndef SIMPLERENDER_VERTEXCONTAINER_HPP
#define SIMPLERENDER_VERTEXCONTAINER_HPP

#include "common/setup.hpp"
#include "pipeline/RenderSetup.hpp"
#include <list>
#include "common/Vertex.hpp"
#include "common/FVertex.hpp"

template<typename T, typename C>
class Container {
public:
//    typedef std::list<T> Room;
//    typedef typename std::list<T>::iterator It;
//    typedef typename std::list<T>::const_iterator CIt;

//    typedef std::vector<T> Room;
//    typedef typename std::vector<T>::iterator It;
//    typedef typename std::vector<T>::const_iterator CIt;
    Container() {}

    typedef C Room;
    typedef typename C::iterator It;
    typedef typename C::const_iterator CIt;

    // Iterate
    MY_SMALL_FUNC_DECL auto begin();

    MY_SMALL_FUNC_DECL auto end();

    MY_SMALL_FUNC_DECL const auto begin() const;

    MY_SMALL_FUNC_DECL const auto end() const;

    // push_back
    MY_SMALL_FUNC_DECL int push_back(const T& item);

    // replace
    MY_SMALL_FUNC_DECL void replace(It it, T item);

    // remove
    MY_SMALL_FUNC_DECL auto erase(It it);

    MY_SMALL_FUNC_DECL auto erase(It first, int len);

    MY_SMALL_FUNC_DECL void clear();

    // insert before
    MY_SMALL_FUNC_DECL auto insert(It it, const T& item);

    MY_SMALL_FUNC_DECL int size() const noexcept ;

    MY_OPERATOR_DECL const T& operator[](int n) const;

    // share_count

private:
    Room mRoom;
};

// use in global
//class Vertex;
using VertexContainer = Container<Vertex, std::vector<Vertex>>;

//class FVertex;
using FVertexContainer = Container<FVertex, std::vector<FVertex>>;

using IndexContainer = Container<int, std::list<int>>;

namespace Mesh {
    class Triangle {
    public:
        Triangle(int a, int b, int c) :
                indexA(a), indexB(b), indexC(c) {}
        // will modify content
        int indexA, indexB, indexC;
    };

    MY_SMALL_FUNC_DECL void push_back_line(IndexContainer& indexContainer, const int vertexA, const int vertexB) {
        indexContainer.push_back(vertexA);
        indexContainer.push_back(vertexB);
    }
    MY_SMALL_FUNC_DECL void push_back_tri(IndexContainer& indexContainer, const int vertexA, const int vertexB,
        const int vertexC) {
        indexContainer.push_back(vertexA);
        indexContainer.push_back(vertexB);
        indexContainer.push_back(vertexC);
    }
    MY_SMALL_FUNC_DECL void push_back_tri(IndexContainer& indexContainer, const Triangle& tri) {
        indexContainer.push_back(tri.indexA);
        indexContainer.push_back(tri.indexB);
        indexContainer.push_back(tri.indexC);
    }

    MY_SMALL_FUNC_DECL void push_back_vertex_tri(IndexContainer& triContainer, VertexContainer& verContainer,
                                                    const Vertex& vertexA, const Vertex& vertexB, const Vertex& vertexC) {
        int indexA = verContainer.push_back(vertexA);
        int indexB = verContainer.push_back(vertexB);
        int indexC = verContainer.push_back(vertexC);
        push_back_tri(triContainer, indexA, indexB, indexC);
    }

    MY_STORAGE_FUNC_DECL void createIndexContainer(GL_MODE mode, const int dataSize, IndexContainer& indexContainer) {
        indexContainer.clear();
        switch(mode) {
            case GL_POINTS:
                for(int i = 0; i < dataSize; i++)
                    indexContainer.push_back(i);
                break;
            case GL_LINES:
                for(int i = 0; i < dataSize; i+=LINE_COUNT)
                    push_back_line(indexContainer, i, i+1);
                break;
            case GL_TRIANGLES:
                for(int i = 0; i < dataSize; i+=TRI_COUNT)
                    push_back_tri(indexContainer, i, i+1, i+2);
                break;
            case GL_TRIANGLES_STRIP:
                int i = TRI_COUNT - 1;
                for(; i < dataSize; i++)
                    push_back_tri(indexContainer, i-2, i-1, i);
                break;
        }
    }
//    void for_each(GL_MODE mode, VertexContainer& vertexContainer, IndexContainer& indexContainer, function<void (auto iter)> func) {
//        switch(mode) {
//            case GL_POINTS:
//                for(auto iter = indexContainer.begin(); iter!= indexContainer
//                        .end(); ) {
//                    if(func)
//                        func(iter);
//                }
//                break;
//            case GL_LINES:
//                break;
//            case GL_TRIANGLES:
//            case GL_TRIANGLES_STRIP:
//                break;
//        }
//    }
}


#include "Container.inl"


#endif //SIMPLERENDER_VERTEXCONTAINER_HPP
