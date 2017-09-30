#include "Pipeline.hpp"

#include "raster/Raster.hpp"
#include "raster/FragCache.hpp"
#include "common/Vertex.hpp"
#include "common/Frag.hpp"

using Gl::Raster;
using Mesh::Triangle;


void Pipeline::useProgram(const unique_ptr<VertexShader> &vertexShader, const unique_ptr<FragShader> &fragShader) {
    if (!mRenderState.isDataValid)
        return;

    // keep the lifetime of Vertex Data
    auto& mode = mRenderState.mMode;
    auto &fVertexData = *mRenderState.fVertexContainerPtr;
    auto &indexContainer = *mRenderState.indexContainerPtr;

    // get camera position and run bsp
#ifdef BSP_ENABLE
    // get view point
    mRenderState.mBSPTree->transferTo(mRenderState.getCameraPosition(), indexContainer);
#endif

    // before clip
    for (auto iter = fVertexData.begin(); iter != fVertexData.end(); iter++) {
        // 1. vertex shader
        FVertex &curFVertex = *iter;
        vertexShader->shade(curFVertex, curFVertex);

        // 2. pipeline deal（model - lookat - projection transform）
        this->pipeTrans(curFVertex);
    }

    // 3. clip
#ifdef CLIP_ENABLE
    this->clip(mode, fVertexData, indexContainer);
#endif

    // 3.5 homogeneous && viewport transform
    VertexContainer vertexContainer;
    for (auto iter = fVertexData.begin(); iter != fVertexData.end(); iter++) {
        Vertex vertex;
        this->afterClip(*iter, vertex);
        vertexContainer.push_back(vertex);
    }

    // 4. raster
    FragCache fragCache(mRenderState.width, mRenderState.height);
    Raster::raster(mRenderState.mMode, mRenderState.mPattern, vertexContainer, indexContainer, mRenderState.mTexture, fragCache);

    // 5. frag vertex
    fragCache.runFrags(fragShader);
}

void clipPoints(FVertexContainer &fVertexData, IndexContainer &indexContainer) {
    for (auto iter = fVertexData.begin(); iter != fVertexData.end(); ) {
        if (!isInVisualBody((*iter).point))
            iter = fVertexData.erase(iter);
        else
            iter++;
    }
}

void clipLines(FVertexContainer &fVertexData, IndexContainer &indexContainer) {
    using std::next;

    for (auto iter = indexContainer.begin(); iter != indexContainer.end();) {
        int& indexA = *iter;
        int& indexB = *(next(iter));
        const FVertex &vertexA = fVertexData[indexA];
        const FVertex &vertexB = fVertexData[indexB];

        if (isInVisualBody(vertexA.point) && isInVisualBody(vertexB.point)) {
            // do nothing
            iter = next(iter, 2);
        }
            // TODO: verify when perspective
        else if (isInVisualBody(vertexA.point)) {
            FVertex interVertex;
            computeInterSect(vertexA, vertexB, interVertex);
            int interIndex = fVertexData.push_back(interVertex);

            indexB = interIndex;

            iter = next(iter, 2);
        } else if (isInVisualBody(vertexB.point)) {
            FVertex interVertex;
            computeInterSect(vertexB, vertexA, interVertex);
            int interIndex = fVertexData.push_back(interVertex);

            indexA = interIndex;

            iter = next(iter, 2);
        } else {
            // TODO: the line segment the two vertexes compose may pass through the visual body

            // remove two point indexes
            iter = indexContainer.erase(iter, 2);
        }
    }
}

void clipTriangles(FVertexContainer &fVertexData, IndexContainer &indexContainer) {
    using std::next;
    for (auto iter = indexContainer.begin(); iter != indexContainer.end();) {
        int *indexAp = &((*iter));
        int *indexBp = &(*next(iter));
        int *indexCp = &(*next(iter, 2));
        const FVertex* vertexAP = &fVertexData[*indexAp];
        const FVertex* vertexBP = &fVertexData[*indexBp];
        const FVertex* vertexCP = &fVertexData[*indexCp];

        if (isInVisualBody(vertexAP->point) && isInVisualBody(vertexBP->point) && isInVisualBody(vertexCP->point)) {
            iter = next(iter, 3);
            // do nothing
        } else if (
                isInVisualBody(vertexAP->point) + isInVisualBody(vertexBP->point) + isInVisualBody(vertexCP->point) ==
                2) {
            FVertex interVertexThis;
            FVertex interVertexThat;
            if (!isInVisualBody(vertexBP->point)) {
                myswap(indexBp, indexAp);
                // swap pointer of pointer
                myswap(&vertexBP, &vertexAP);
                myswap(indexBp, indexCp);
                myswap(&vertexBP, &vertexCP);
            } else if (!isInVisualBody(vertexCP->point)) {
                myswap(indexCp, indexAp);
                myswap(&vertexCP, &vertexAP);
                myswap(indexCp, indexBp);
                myswap(&vertexCP, &vertexBP);
            }

            computeInterSect(*vertexBP, *vertexAP, interVertexThis);
            computeInterSect(*vertexCP, *vertexAP, interVertexThat);

            int indexThis = fVertexData.push_back(interVertexThis);
            int indexThat = fVertexData.push_back(interVertexThat);

            // erase ad move the iter to the next position
            iter = indexContainer.erase(iter, 3);

            iter = indexContainer.insert(iter, indexThis);
            iter = indexContainer.insert(iter, *indexBp);
            iter = indexContainer.insert(iter, *indexCp);
            iter = indexContainer.insert(iter, indexThis);
            iter = indexContainer.insert(iter, *indexCp);
            iter = indexContainer.insert(iter, indexThat);
        } else if (
                isInVisualBody(vertexAP->point) + isInVisualBody(vertexBP->point) + isInVisualBody(vertexCP->point) ==
                1) {
            FVertex interVertexThis;
            FVertex interVertexThat;

            // assume vertexA is in visual body
            if (isInVisualBody(vertexBP->point)) {
                myswap(indexBp, indexAp);
                myswap(&vertexBP, &vertexAP);
                myswap(indexBp, indexCp);
                myswap(&vertexBP, &vertexCP);
            } else if (isInVisualBody(vertexCP->point)) {
                myswap(indexCp, indexAp);
                myswap(&vertexCP, &vertexAP);
                myswap(indexCp, indexBp);
                myswap(&vertexCP, &vertexBP);
            }

            computeInterSect(*vertexAP, *vertexBP, interVertexThis);
            computeInterSect(*vertexAP, *vertexCP, interVertexThat);

            int indexThis = fVertexData.push_back(interVertexThis);
            int indexThat = fVertexData.push_back(interVertexThat);

            iter = indexContainer.erase(iter, 3);

            iter = indexContainer.insert(iter, *indexAp);
            iter = indexContainer.insert(iter, indexThis);
            iter = indexContainer.insert(iter, indexThat);
        } else {
            // TODO: the triangle the three vertexes compose may pass through the visual body
            iter = indexContainer.erase(iter, 3);
        }
    }
}

void Pipeline::clip(const GL_MODE &mode, FVertexContainer &fVertexData, IndexContainer &indexContainer) {
    switch (mode) {
        case GL_POINTS:
            clipPoints(fVertexData, indexContainer);
            break;
        case GL_LINES:
            clipLines(fVertexData, indexContainer);
            break;
        case GL_TRIANGLES:
        case GL_TRIANGLES_STRIP:
            clipTriangles(fVertexData, indexContainer);
            break;
        default:
            break;
    }
}