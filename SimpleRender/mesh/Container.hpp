//
// Created by WJ Yang on 2017/9/28.
//

#ifndef SIMPLERENDER_VERTEXCONTAINER_HPP
#define SIMPLERENDER_VERTEXCONTAINER_HPP

#include "common/setup.hpp"

#include <list>

template<typename T, typename C>
class Container {
public:
//    typedef std::list<T> Room;
//    typedef typename std::list<T>::iterator It;
//    typedef typename std::list<T>::const_iterator CIt;

//    typedef std::vector<T> Room;
//    typedef typename std::vector<T>::iterator It;
//    typedef typename std::vector<T>::const_iterator CIt;

    typedef C Room;
    typedef typename C::iterator It;
    typedef typename C::const_iterator CIt;

    // Iterate
    MY_SMALL_FUNC_DECL auto begin();

    MY_SMALL_FUNC_DECL auto end();

    // push_back
    MY_SMALL_FUNC_DECL int push_back(const T& item);

    // replace
    MY_SMALL_FUNC_DECL void replace(It it, T item);

    // remove
    MY_SMALL_FUNC_DECL auto remove(It it);

    // insert before
    MY_SMALL_FUNC_DECL auto insert(It it, const T& item);

    MY_SMALL_FUNC_DECL int size() const noexcept ;

    // share_count

private:
    Room mRoom;
};

// use in global
class Vertex;
using VertexContainer = Container<Vertex, std::vector<Vertex>>;

namespace Mesh {
    class Triangle {
    public:
        Triangle(int a, int b, int c) :
            indexA(a), indexB(b), indexC(c) {}
        // will modify content
        int indexA, indexB, indexC;
    };

    using TriangleContainer = Container<Triangle, std::list<Triangle>>;
    MY_SMALL_STORAGE_DECL void push_back_vertex_tri(TriangleContainer& triContainer, VertexContainer& verContainer,
    const Vertex& vertexA, const Vertex& vertexB, const Vertex& vertexC) {
        int indexA = verContainer.push_back(vertexA);
        int indexB = verContainer.push_back(vertexB);
        int indexC = verContainer.push_back(vertexC);
        triContainer.push_back(Triangle(indexA, indexB, indexC));
    }
}

#include "Container.inl"


#endif //SIMPLERENDER_VERTEXCONTAINER_HPP
