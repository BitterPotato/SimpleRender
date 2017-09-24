#ifndef BSP_HPP
#define BSP_HPP

#include "RenderSetup.hpp"
#include "common/Frag.hpp"
#include "common/FVertex.hpp"
#include "math/TVector_Trans.hpp"

using math::cross;
using math::dot;
using math::asVec3;

struct Triangle {
public:
	// vertex index
	int va, vb, vc;

	fvec3 normal;
	float remainder;
	
	Triangle(int va, int vb, int vc) {
		this->va = va;
		this->vb = vb;
		this->vc = vc;
	}
	Triangle(vector<FVertex>& vertexList, int va, int vb, int vc) {
		this->va = va;
		this->vb = vb;
		this->vc = vc;

		FVertex& a = vertexList[va];
		FVertex& b = vertexList[vb];
		FVertex& c = vertexList[vc];

		fvec3 vecAB = fvec3(b.point[X] - a.point[X], b.point[Y] - a.point[Y], b.point[Z] - a.point[Z]);
		fvec3 vecBC = fvec3(c.point[X] - b.point[X], c.point[Y] - b.point[Y], c.point[Z] - b.point[Z]);
		fvec3 cordA = fvec3(a.point[X], a.point[Y], a.point[Z]);
		normal = cross(vecAB, vecBC);
		remainder = -dot(normal, cordA);
	}
	// -: from v to see tri, tri is anticlockwise
	// 0: on tri
	// +: from v to see tri, tri is clockwise
	MY_SMALL_FUNC_DECL float distToTri(const fvec3& vec) const {
		return dot(normal, vec) + remainder;
	}
	MY_SMALL_FUNC_DECL void intersectToTri(const FVertex& vThis, const FVertex& vThat, FVertex& interVertex) const {
		fvec3 vecThis = asVec3(vThis);
		fvec3 vecThat = asVec3(vThat);

		float t = -(remainder + dot(vecThis, normal) / dot(normal, vecThat - vecThis));
		
		inter(vThis, vThat, t, interVertex);
	}
	MY_NFRIEND_FUNC_DECL void pushBackTri(vector<FVertex>& vertexList, vector<FVertex>& outVertexList, const Triangle* tri) {
		outVertexList.push_back(vertexList[tri->va]);
		outVertexList.push_back(vertexList[tri->vb]);
		outVertexList.push_back(vertexList[tri->vc]);
	}
};
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

	BSPTree(const GL_MODE& mode, vector<FVertex>& _vertexList) : vertexList(_vertexList){
		switch (mode)
		{
		case GL_TRIANGLES:
			for (int i = 0; i < _vertexList.size(); i += 3) {
				addTri(i, i+1, i+2);
			}
			break;
		default:
			break;
		}
	}
    ~BSPTree() {
        if (root)
            delete root;
    }

    MY_COMP_FUNC_DECL void transferTo(const fvec3& cameraPosi, vector<FVertex>& outTriList) const;

private:
	const float epsilon = 0.01;

	BSPNodeP root;
	vector<FVertex>& vertexList;

    MY_COMP_FUNC_DECL void subTransferTo(const BSPNodeP node, const fvec3& cameraPosi, vector<FVertex>& outTriList) const;

    MY_COMP_FUNC_DECL void addTri(const int vertexA, const int vertexB, const int vertexC) ;

    MY_SMALL_FUNC_DECL float dist(const Triangle* tri, const int v) const;

	MY_COMP_FUNC_DECL void addBSPNodeWrapper(BSPNodeP* node, Triangle* tri) ;

	MY_COMP_FUNC_DECL void addBSPNode(BSPNodeP node, Triangle* tri) ;
};



#endif