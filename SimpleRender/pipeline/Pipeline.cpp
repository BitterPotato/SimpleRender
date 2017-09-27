#include "Pipeline.hpp"

#include "raster/Raster.hpp"
#include "raster/FragCache.hpp"
#include "common/Vertex.hpp"
#include "common/Frag.hpp"

using Gl::Raster;

	void Pipeline::useProgram(const unique_ptr<VertexShader>& vertexShader, const unique_ptr<FragShader>& fragShader) {
		if (!mRenderState.isDataValid)
			return;

		// get camera position and run bsp
#ifdef BSP_ENABLE
		vector<FVertex> vertexData;
		// get view point
		mRenderState.mBSPTree->transferTo(mRenderState.getCameraPosition(), vertexData);
#endif
#ifndef BSP_ENABLE
		const auto vertexData = *mRenderState.vertexDataPtr;
#endif

		vector<FVertex> beforeClipVertexData;
		for (auto iter = vertexData.begin(); iter != vertexData.end(); iter++) {
			// 1. vertex shader
			FVertex afterVS;
			vertexShader->shade(*iter, afterVS);

			// 2. pipeline deal（model - lookat - projection transform）
			this->pipeTrans(afterVS);
			beforeClipVertexData.push_back(afterVS);
		}
		// 3. clip 
#ifdef CLIP_ENABLE
		vector<FVertex> afterClipVertexData;
		this->clip(mMode, beforeClipVertexData, afterClipVertexData);
#endif
#ifndef CLIP_ENABLE
		vector<FVertex>& afterClipVertexData = beforeClipVertexData;
#endif

		// 3.5 homogeneous && viewport transform
		vector<Vertex> beforeRasterVertexData;
		for (auto iter = afterClipVertexData.begin(); iter != afterClipVertexData.end(); iter++) {
			Vertex vertex;
			this->afterClip(*iter, vertex);
			beforeRasterVertexData.push_back(vertex);
		}

		// 4. raster
		FragCache fragCache(mRenderState.width, mRenderState.height);
		Raster::raster(mRenderState.mMode, mRenderState.mPattern, beforeRasterVertexData, mRenderState.mTexture, fragCache);

		// 5. frag vertex
		fragCache.runFrags(fragShader);
	}

	void Pipeline::clip(const GL_MODE& mode, const vector<FVertex>& vertexData, vector<FVertex>& outVertexData) {
		switch (mode) {
		case GL_POINTS:
			for (auto iter = vertexData.begin(); iter != vertexData.end(); iter++) {
				if (isInVisualBody((*iter).point))
					outVertexData.push_back(*iter);
			}
			break;
		case GL_LINES:
			for (auto iter = vertexData.begin(); iter != vertexData.end(); iter += 2) {
				if (isInVisualBody((*iter).point) && isInVisualBody((*(iter + 1)).point)){
					outVertexData.push_back(*iter);
					outVertexData.push_back(*(iter + 1));
				}
				// TODO: verify when perspective
				else if (isInVisualBody((*iter).point)) {
					FVertex interVertex;
					computeInterSect(*iter, *(iter + 1), interVertex);

					outVertexData.push_back(*iter);
					outVertexData.push_back(interVertex);
				}
				else if (isInVisualBody((*(iter + 1)).point)) {
					FVertex interVertex;
					computeInterSect(*(iter + 1), *iter, interVertex);

					outVertexData.push_back(*(iter + 1));
					outVertexData.push_back(interVertex);
				}
				else {
					// TODO: the line segment the two vertexes compose may pass through the visual body 
				}
			}
			break;
		case GL_TRIANGLES:
			for (auto iter = vertexData.begin(); iter != vertexData.end(); iter += 3) {
				const FVertex& vertexA = *iter;
				const FVertex& vertexB = *(iter + 1);
				const FVertex& vertexC = *(iter + 2);

				if (isInVisualBody(vertexA.point) && isInVisualBody(vertexB.point) && isInVisualBody(vertexC.point)) {
					pushMore(outVertexData, vertexA, vertexB, vertexC);
				}
				else if (isInVisualBody(vertexA.point) + isInVisualBody(vertexB.point) + isInVisualBody(vertexC.point) == 2) {
					FVertex interVertexThis;
					FVertex interVertexThat;
					// TODO: haven't considered the condition, that the triangle intersect with two planes
					if (!isInVisualBody(vertexA.point)) {
						dealWithTwo(outVertexData, vertexA, vertexB, vertexC, false);
					}
					else if (!isInVisualBody(vertexB.point)) {
						dealWithTwo(outVertexData, vertexB, vertexA, vertexC, true);
					}
					else if (!isInVisualBody(vertexC.point)) {
						dealWithTwo(outVertexData, vertexC, vertexA, vertexB, false);
					}
				}
				else if (isInVisualBody(vertexA.point) + isInVisualBody(vertexB.point) + isInVisualBody(vertexC.point) == 1) {
					FVertex interVertexThis;
					FVertex interVertexThat;

					// TODO: haven't considered the condition, that the triangle intersect with two or three planes
					if (isInVisualBody(vertexA.point)) {
						dealWithOne(outVertexData, vertexA, vertexB, vertexC);
					}
					else if (isInVisualBody(vertexB.point)) {
						dealWithOne(outVertexData, vertexB, vertexC, vertexA);
					}
					else if (isInVisualBody(vertexC.point)) {
						dealWithOne(outVertexData, vertexC, vertexA, vertexB);
					}
				}
				else {
					// TODO: the triangle the three vertexes compose may pass through the visual body 
				}
			}
			break;
			//case GL_TRIANGLES_STRIP:
			//	auto iter = vecVertex.begin();
			//	iter += 2;
			//	for (; iter != vecVertex.end(); iter++) {
			//		rasterUniverTriangle(pattern, *(iter - 2), *(iter - 1), *iter, texture, fragCache);
			//	}
			//	break;
		}
	}