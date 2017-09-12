#ifndef BSP_HPP
#define BSP_HPP

#include "stage_struc.hpp"
#include "../raster/Frag.hpp"
#include "../math/tvector_trans.hpp"

#include <vector>
#include <cmath>

using math::cross;
using math::dot;

using std::abs;
using std::vector;

struct Triangle {
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

		fvec3 vecAB = fvec3(b.x - a.x, b.y - a.y, b.z - a.z);
		fvec3 vecBC = fvec3(c.x - b.x, c.y - b.y, c.z - b.z);
		fvec3 cordA = fvec3(a.x, a.y, a.z);
		normal = cross(vecAB, vecBC);
		remainder = -dot(normal, cordA);
	}
	// -: from v to see tri, tri is anticlockwise
	// 0: on tri
	// +: from v to see tri, tri is clockwise
	float distToTri(const fvec3& vec) const {
		return dot(normal, vec) + remainder;
	}
	void intersectToTri(const FVertex& vThis, const FVertex& vThat, FVertex& interVertex) const {
		fvec3 vecThis = extractVec(vThis);
		fvec3 vecThat = extractVec(vThat);

		float t = -(remainder + dot(vecThis, normal) / dot(normal, vecThat - vecThis));
		
		inter(vThis, vThat, t, interVertex);
	}
	friend void pushBackTri(vector<FVertex>& vertexList, vector<FVertex>& outVertexList, const Triangle* tri) {
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

	void transferTo(const fvec3& cameraPosi, vector<FVertex>& outTriList) {
		subTransferTo(root, cameraPosi, outTriList);
	}

	void subTransferTo(const BSPNodeP node, const fvec3& cameraPosi, vector<FVertex>& outTriList) {
		if (!node)
			return;

		// TODO: why in this order
		if (node->tri->distToTri(cameraPosi) > 0) {
			subTransferTo(node->minus, cameraPosi, outTriList);
			pushBackTri(vertexList, outTriList, node->tri);
			subTransferTo(node->plus, cameraPosi, outTriList);
		}
		else {
			subTransferTo(node->plus, cameraPosi, outTriList);
			pushBackTri(vertexList, outTriList, node->tri);
			subTransferTo(node->minus, cameraPosi, outTriList);
		}
	}
	~BSPTree() {
		if (root)
			delete root;
	}
private:
	const float epsilon = 0.01;

	BSPNodeP root;
	vector<FVertex>& vertexList;

	void addTri(const int vertexA, const int vertexB, const int vertexC) {
		// init Triangle
		Triangle* tri = new Triangle(vertexA, vertexB, vertexC);
		
		addBSPNodeWrapper(&root, tri);
	}

	inline float dist(const Triangle* tri, const int v) {
		float dis = tri->distToTri(extractVec(vertexList[v]));
		return abs(dis) < epsilon ? 0.0f : dis;
	}

	void addBSPNodeWrapper(BSPNodeP* node, Triangle* tri) {
		if (*node == nullptr) {
			*node = new BSPNode(tri);
		}
		else {
			addBSPNode(*node, tri);
		}
	}

	void addBSPNode(BSPNodeP node, Triangle* tri) {
		float fa = dist(node->tri, tri->va);
		float fb = dist(node->tri, tri->vb);
		float fc = dist(node->tri, tri->vc);

		if (fa <= 0 && fb <= 0 && fc <= 0) {
			addBSPNodeWrapper(&node->minus, tri);
		}
		else if (fa >= 0 && fb >= 0 && fc >= 0) {
			addBSPNodeWrapper(&node->plus, tri);
		}
		// smell but right here
		else if (fa == 0 || fb == 0 || fc == 0){
			// one vertex on tri, one vertex on plus side, one vertex on minus side

			// convert to vc on tri
			if (fa == 0) {
				swap(&fa, &fc);
				swap(&tri->va, &tri->vc);
				swap(&fa, &fb);
				swap(&tri->va, &tri->vb);
			}
			if (fb == 0) {
				swap(&fb, &fc);
				swap(&tri->vb, &tri->vc);
				swap(&fa, &fb);
				swap(&tri->va, &tri->vb);
			}

			FVertex vD; int indexVD = vertexList.size();
			node->tri->intersectToTri(vertexList[tri->va], vertexList[tri->vb], vD);
			
			vertexList.push_back(vD);

			Triangle* aDc = new Triangle(tri->va, indexVD, tri->vc);
			Triangle* cDb = new Triangle(tri->vc, indexVD, tri->vb);

			if (fa <= 0) {
				addBSPNodeWrapper(&node->minus, aDc);
				addBSPNodeWrapper(&node->plus, cDb);
			}
			else {
				addBSPNodeWrapper(&node->plus, aDc);
				addBSPNodeWrapper(&node->minus, cDb);
			}
			delete tri;
		}
		else {
			// one/ two vertexs on each side

			// convert to vc on one side, va & vb on the other
			if(fa*fc >= 0) {
				swap(&fb, &fc);
				swap(&tri->vb, &tri->vc);
				swap(&fa, &fb);
				swap(&tri->va, &tri->vb);
			}
			if (fb*fc >= 0) {
				swap(&fa, &fc);
				swap(&tri->va, &tri->vc);
				swap(&fa, &fb);
				swap(&tri->va, &tri->vb);
			}

			FVertex vA, vB; 
			int indexVA = vertexList.size();
			int indexVB = indexVA + 1;
			node->tri->intersectToTri(vertexList[tri->va], vertexList[tri->vc], vA);
			node->tri->intersectToTri(vertexList[tri->vb], vertexList[tri->vc], vB);

			Triangle* abA = new Triangle(tri->va, tri->vb, indexVA);
			Triangle* bBA = new Triangle(tri->vb, indexVB, indexVA);
			Triangle* ABc = new Triangle(indexVA, indexVB, tri->vc);

			if (fc <= 0) {
				addBSPNodeWrapper(&node->minus, ABc);
				addBSPNodeWrapper(&node->plus, bBA);
				addBSPNodeWrapper(&node->plus, abA);
			}
			else {
				addBSPNodeWrapper(&node->plus, ABc);
				addBSPNodeWrapper(&node->minus, bBA);
				addBSPNodeWrapper(&node->minus, abA);
			}
			delete tri;
		}
	}
};



#endif