#include "BSPTree.hpp"

void BSPTree::transferTo(const fvec3 &cameraPosi, vector<FVertex> &outTriList) const {
    subTransferTo(root, cameraPosi, outTriList);
}

void BSPTree::subTransferTo(const BSPNodeP node, const fvec3 &cameraPosi, vector<FVertex> &outTriList) const {
    if (!node)
        return;

    // TODO: why in this order
    if (node->tri->distToTri(cameraPosi) > 0) {
        subTransferTo(node->minus, cameraPosi, outTriList);
        pushBackTri(vertexList, outTriList, node->tri);
        subTransferTo(node->plus, cameraPosi, outTriList);
    } else {
        subTransferTo(node->plus, cameraPosi, outTriList);
        pushBackTri(vertexList, outTriList, node->tri);
        subTransferTo(node->minus, cameraPosi, outTriList);
    }
}

void BSPTree::addTri(const int vertexA, const int vertexB, const int vertexC) {
    // init Triangle
    Triangle *tri = new Triangle(vertexList, vertexA, vertexB, vertexC);

    addBSPNodeWrapper(&root, tri);
}

float BSPTree::dist(const Triangle *tri, const int v) const {
    float dis = tri->distToTri(asVec3(vertexList[v].point));
    return abs(dis) < epsilon ? 0.0f : dis;
}

void BSPTree::addBSPNodeWrapper(BSPNodeP *node, Triangle *tri) {
    if (*node == nullptr) {
        *node = new BSPNode(tri);
    } else {
        addBSPNode(*node, tri);
    }
}

void BSPTree::addBSPNode(BSPNodeP node, Triangle *tri) {
    float fa = dist(node->tri, tri->va);
    float fb = dist(node->tri, tri->vb);
    float fc = dist(node->tri, tri->vc);

    if (fa <= 0 && fb <= 0 && fc <= 0) {
        addBSPNodeWrapper(&node->minus, tri);
    } else if (fa >= 0 && fb >= 0 && fc >= 0) {
        addBSPNodeWrapper(&node->plus, tri);
    }
        // smell but right here
    else if (fa == 0 || fb == 0 || fc == 0) {
        // one vertex on tri, one vertex on plus side, one vertex on minus side

        // convert to vc on tri
        if (fa == 0) {
            myswap(&fa, &fc);
            myswap(&tri->va, &tri->vc);
            myswap(&fa, &fb);
            myswap(&tri->va, &tri->vb);
        }
        if (fb == 0) {
            myswap(&fb, &fc);
            myswap(&tri->vb, &tri->vc);
            myswap(&fa, &fb);
            myswap(&tri->va, &tri->vb);
        }

        FVertex vD;
        int indexVD = vertexList.size();
        node->tri->intersectToTri(vertexList[tri->va].point, vertexList[tri->vb].point, vD);

        vertexList.push_back(vD);

        Triangle *aDc = new Triangle(vertexList, tri->va, indexVD, tri->vc);
        Triangle *cDb = new Triangle(vertexList, tri->vc, indexVD, tri->vb);

        if (fa <= 0) {
            addBSPNodeWrapper(&node->minus, aDc);
            addBSPNodeWrapper(&node->plus, cDb);
        } else {
            addBSPNodeWrapper(&node->plus, aDc);
            addBSPNodeWrapper(&node->minus, cDb);
        }
        delete tri;
    } else {
        // one/ two vertexs on each side

        // convert to vc on one side, va & vb on the other
        if (fa * fc >= 0) {
            myswap(&fb, &fc);
            myswap(&tri->vb, &tri->vc);
            myswap(&fa, &fb);
            myswap(&tri->va, &tri->vb);
        }
        if (fb * fc >= 0) {
            myswap(&fa, &fc);
            myswap(&tri->va, &tri->vc);
            myswap(&fa, &fb);
            myswap(&tri->va, &tri->vb);
        }

        FVertex vA, vB;
        int indexVA = vertexList.size();
        int indexVB = indexVA + 1;
        node->tri->intersectToTri(vertexList[tri->va], vertexList[tri->vc], vA);
        node->tri->intersectToTri(vertexList[tri->vb], vertexList[tri->vc], vB);

        Triangle *abA = new Triangle(vertexList, tri->va, tri->vb, indexVA);
        Triangle *bBA = new Triangle(vertexList, tri->vb, indexVB, indexVA);
        Triangle *ABc = new Triangle(vertexList, indexVA, indexVB, tri->vc);

        if (fc <= 0) {
            addBSPNodeWrapper(&node->minus, ABc);
            addBSPNodeWrapper(&node->plus, bBA);
            addBSPNodeWrapper(&node->plus, abA);
        } else {
            addBSPNodeWrapper(&node->plus, ABc);
            addBSPNodeWrapper(&node->minus, bBA);
            addBSPNodeWrapper(&node->minus, abA);
        }
        delete tri;
    }
}
