#ifndef BSP_HPP
#define BSP_HPP

#include "common/setup.hpp"

#include "geometry/Triangle3D.hpp"
#include "RenderSetup.hpp"
#include "common/FVertex.hpp"
#include "math/TVector_Trans.hpp"
#include "mesh/Container.hpp"

class Vertex;

//using Geometry::FTriangle3D;

//class Triangle : public FTriangle3D {
//	friend class BSPTree;
//public:
//	using FTriangle3D::FTriangle3D;
//	Triangle(FVertexContainer& vertexList, int va, int vb, int vc) :
//            FTriangle3D(asVec3(vertexList[va].point),
//                       asVec3(vertexList[vb].point),
//                       asVec3(vertexList[vc].point)) {
//		this->va = va;
//		this->vb = vb;
//		this->vc = vc;
//	}
//	MY_SMALL_FUNC_DECL void intersectToTri(const FVertex& vThis, const FVertex& vThat, FVertex& outVertex) const {
//		float ratio = FTriangle3D::intersectToTri(asVec3(vThis.point), asVec3(vThat.point));
//		inter(vThis, vThat, outVertex, ratio);
//	}
//	MY_NFRIEND_FUNC_DECL void pushBackTri(FVertexContainer& vertexList, FVertexContainer& outVertexList, const Triangle* tri) {
//		outVertexList.push_back(vertexList[tri->va]);
//		outVertexList.push_back(vertexList[tri->vb]);
//		outVertexList.push_back(vertexList[tri->vc]);
//	}
//private:
//	// vertex index
//	int va, vb, vc;
//};

using Mesh::Triangle;

struct BSPNode {
	BSPNode* plus;
	BSPNode* minus;
	Triangle* tri;
	
	BSPNode() {}
	BSPNode(Triangle* tri) {
		this->tri = tri;
		this->plus = nullptr;
		this->minus = nullptr;
	}
	BSPNode(BSPNode& node) = delete;
	BSPNode& operator=(const BSPNode& node) = delete;
	~BSPNode() {
		if (plus)
			delete plus;
		if (minus)
			delete minus;
		if(tri)
			delete tri;
	}
};
typedef BSPNode* BSPNodeP;

class BSPTree {
public:

	BSPTree(BSPTree& tree) = delete;
	BSPTree& operator=(const BSPTree& tree) = delete;

	BSPTree(const GL_MODE& mode, FVertexContainer& _vertexList) : vertexList(_vertexList){
		switch (mode)
		{
		case GL_TRIANGLES:
			for (int i = 0; i < _vertexList.size(); i += 3) {
				addTri(i, i+1, i+2);
			}
			break;
		case GL_TRIANGLES_STRIP:

			break;
		default:
			break;
		}
	}
    ~BSPTree() {
        if (root)
            delete root;
    }

    MY_COMP_FUNC_DECL void transferTo(const fvec3& cameraPosi, IndexContainer& outTriList) const;

private:

	BSPNodeP root = nullptr;
	FVertexContainer& vertexList;

    MY_COMP_FUNC_DECL void subTransferTo(const BSPNodeP node, const fvec3& cameraPosi, IndexContainer& outTriList) const;

    MY_COMP_FUNC_DECL void addTri(const int vertexA, const int vertexB, const int vertexC) ;

	MY_COMP_FUNC_DECL void addBSPNodeWrapper(BSPNodeP* node, Triangle* tri) ;

	MY_COMP_FUNC_DECL void addBSPNode(BSPNodeP node, Triangle* tri) ;

    MY_SMALL_FUNC_DECL float distToTri(const Triangle *tri, const FPoint3D &point) const;

    MY_SMALL_FUNC_DECL float distToTriWrapper(const Triangle *tri, const FPoint3D &point) const;

    MY_SMALL_FUNC_DECL float intersectToTri(const Triangle* tri, const FPoint3D& pThis, const FPoint3D& pThat) const;

    MY_SMALL_FUNC_DECL void intersectToTriWrapper(const Triangle* tri, const FVertex& vThis, const FVertex& vThat, FVertex& outVertex) const;
};

#include "BSPTree.inl"

#endif