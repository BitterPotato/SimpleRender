#include "BSPTree.hpp"

void BSPTree::transferTo(const fvec3 &cameraPosi, IndexContainer& outTriList) const {
    // TODO: temp
    cout << cameraPosi[X] << " " << cameraPosi[Y] << " " << cameraPosi[Z] << endl;
    outTriList.clear();
    subTransferTo(root, cameraPosi, outTriList);
}

void BSPTree::subTransferTo(const BSPNodeP node, const fvec3 &cameraPosi, IndexContainer& outTriList) const {
    if (!node)
        return;

    // TODO: why in this order
    if (distToTri(node->tri, cameraPosi) > 0) {
        subTransferTo(node->minus, cameraPosi, outTriList);
        Mesh::push_back_tri(outTriList, *node->tri);
        subTransferTo(node->plus, cameraPosi, outTriList);
    } else {
        subTransferTo(node->plus, cameraPosi, outTriList);
        Mesh::push_back_tri(outTriList, *node->tri);
        subTransferTo(node->minus, cameraPosi, outTriList);
    }
}


void BSPTree::addTri(const int vertexA, const int vertexB, const int vertexC) {
    // init Triangle
    Triangle *tri = new Triangle(vertexA, vertexB, vertexC);

    addBSPNodeWrapper(&root, tri);
}

// pointer of pointer
void BSPTree::addBSPNodeWrapper(BSPNodeP* node, Triangle *tri) {
    if (*node == nullptr) {
        *node = new BSPNode(tri);
    } else {
        addBSPNode(*node, tri);
    }
}

void BSPTree::addBSPNode(BSPNodeP node, Triangle *tri) {
    float fa = distToTriWrapper(node->tri, asVec3(vertexList[tri->indexA].point));
    float fb = distToTriWrapper(node->tri, asVec3(vertexList[tri->indexB].point));
    float fc = distToTriWrapper(node->tri, asVec3(vertexList[tri->indexC].point));

    if (fa <= 0 && fb <= 0 && fc <= 0) {
        addBSPNodeWrapper(&(node->minus), tri);
    } else if (fa >= 0 && fb >= 0 && fc >= 0) {
        addBSPNodeWrapper(&(node->plus), tri);
    }
        // smell but right here
    else if (fa == 0 || fb == 0 || fc == 0) {
        // one vertex on tri, one vertex on plus side, one vertex on minus side

        // convert to vc on tri
        if (fa == 0) {
            myswap(&fa, &fc);
            myswap(&tri->indexA, &tri->indexC);
            myswap(&fa, &fb);
            myswap(&tri->indexA, &tri->indexB);
        }
        if (fb == 0) {
            myswap(&fb, &fc);
            myswap(&tri->indexB, &tri->indexC);
            myswap(&fa, &fb);
            myswap(&tri->indexA, &tri->indexB);
        }

        FVertex vD;
        intersectToTriWrapper(node->tri, vertexList[tri->indexA], vertexList[tri->indexB], vD);

        int indexVD = vertexList.push_back(vD);

        Triangle *aDc = new Triangle(tri->indexA, indexVD, tri->indexC);
        Triangle *cDb = new Triangle(tri->indexC, indexVD, tri->indexB);

        if (fa <= 0) {
            addBSPNodeWrapper(&(node->minus), aDc);
            addBSPNodeWrapper(&(node->plus), cDb);
        } else {
            addBSPNodeWrapper(&(node->plus), aDc);
            addBSPNodeWrapper(&(node->minus), cDb);
        }
        delete tri;
    } else {
        // one/ two vertexs on each side

        // convert to vc on one side, va & vb on the other
        if (fa * fc >= 0) {
            myswap(&fb, &fc);
            myswap(&tri->indexB, &tri->indexC);
            myswap(&fa, &fb);
            myswap(&tri->indexA, &tri->indexB);
        }
        if (fb * fc >= 0) {
            myswap(&fa, &fc);
            myswap(&tri->indexA, &tri->indexC);
            myswap(&fa, &fb);
            myswap(&tri->indexA, &tri->indexB);
        }

        FVertex vA, vB;
        intersectToTriWrapper(node->tri, vertexList[tri->indexA], vertexList[tri->indexC], vA);
        intersectToTriWrapper(node->tri, vertexList[tri->indexB], vertexList[tri->indexC], vB);

        int indexVA = vertexList.push_back(vA);
        int indexVB = vertexList.push_back(vB);

        Triangle *abA = new Triangle(tri->indexA, tri->indexB, indexVA);
        Triangle *bBA = new Triangle(tri->indexB, indexVB, indexVA);
        Triangle *ABc = new Triangle(indexVA, indexVB, tri->indexC);

        if (fc <= 0) {
            addBSPNodeWrapper(&(node->minus), ABc);
            addBSPNodeWrapper(&(node->plus), bBA);
            addBSPNodeWrapper(&(node->plus), abA);
        } else {
            addBSPNodeWrapper(&(node->plus), ABc);
            addBSPNodeWrapper(&(node->minus), bBA);
            addBSPNodeWrapper(&(node->minus), abA);
        }
        delete tri;
    }
}
