#include "stage_flow.hpp"

namespace gl {
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
			FVertex& afterVS = FVertex();
			vertexShader->shade(*iter, afterVS);

			// 2. pipeline deal£¨model - lookat - projection transform£©
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
			Vertex vertex = Vertex();
			this->afterClip(*iter, vertex);
			beforeRasterVertexData.push_back(vertex);
		}

		// 4. raster
		FragCache fragCache(mRenderState.width, mRenderState.height);
		raster(mRenderState.mMode, mRenderState.mPattern, beforeRasterVertexData, mRenderState.mTexture, fragCache);

		// 5. frag vertex
		fragCache.runFrags(fragShader);
	}

	void Pipeline::pipeTrans(FVertex& fVertex) const {
		fvec4 outCoord4(fVertex.x, fVertex.y, fVertex.z, 1.0f);
		// 1. Model - World Transform	
		// 2. World - Camera Transform
		// 3. Camera - Clip Transform
		outCoord4 = mRenderState.mLookatMatrix*mRenderState.mTransformMatrix*outCoord4;
		outCoord4 = mRenderState.mProjMatrix*outCoord4;
		//outCoord4 = mProjMatrix*mLookatMatrix*mTransformMatrix*outCoord4;

		fVertex.x = outCoord4[0];
		fVertex.y = outCoord4[1];
		fVertex.z = outCoord4[2];
		fVertex.w = outCoord4[3];
	}

	void Pipeline::clip(const GL_MODE& mode, const vector<FVertex>& vertexData, vector<FVertex>& outVertexData) const {
		switch (mode) {
		case GL_POINTS:
			for (auto iter = vertexData.begin(); iter != vertexData.end(); iter++) {
				if (isInVisualBody(*iter))
					outVertexData.push_back(*iter);
			}
			break;
		case GL_LINES:
			for (auto iter = vertexData.begin(); iter != vertexData.end(); iter += 2) {
				if (isInVisualBody(*iter) && isInVisualBody(*(iter + 1))) {
					outVertexData.push_back(*iter);
					outVertexData.push_back(*(iter + 1));
				}
				// TODO: verify when perspective
				else if (isInVisualBody(*iter)) {
					FVertex interVertex;
					computeInterSect(*iter, *(iter + 1), interVertex);

					outVertexData.push_back(*iter);
					outVertexData.push_back(interVertex);
				}
				else if (isInVisualBody(*(iter + 1))) {
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

				if (isInVisualBody(vertexA) && isInVisualBody(vertexB) && isInVisualBody(vertexC)) {
					pushMore(outVertexData, vertexA, vertexB, vertexC);
				}
				else if (isInVisualBody(vertexA) + isInVisualBody(vertexB) + isInVisualBody(vertexC) == 2) {
					FVertex interVertexThis;
					FVertex interVertexThat;
					// TODO: haven't considered the condition, that the triangle intersect with two planes
					if (!isInVisualBody(vertexA)) {
						dealWithTwo(outVertexData, vertexA, vertexB, vertexC, false);
					}
					else if (!isInVisualBody(vertexB)) {
						dealWithTwo(outVertexData, vertexB, vertexA, vertexC, true);
					}
					else if (!isInVisualBody(vertexC)) {
						dealWithTwo(outVertexData, vertexC, vertexA, vertexB, false);
					}
				}
				else if (isInVisualBody(vertexA) + isInVisualBody(vertexB) + isInVisualBody(vertexC) == 1) {
					FVertex interVertexThis;
					FVertex interVertexThat;

					// TODO: haven't considered the condition, that the triangle intersect with two or three planes
					if (isInVisualBody(vertexA)) {
						dealWithOne(outVertexData, vertexA, vertexB, vertexC);
					}
					else if (isInVisualBody(vertexB)) {
						dealWithOne(outVertexData, vertexB, vertexC, vertexA);
					}
					else if (isInVisualBody(vertexC)) {
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

	void Pipeline::afterClip(const FVertex& fVertex, Vertex& outVertex) const {
		// 3_5. as for perspective projection, needs a stage called 'Homogeneous'
		fvec3 outCoord3 = homogeneous(fvec4(fVertex.x, fVertex.y, fVertex.z, fVertex.w));

		// 4. Clip - Viewport Transform
		outCoord3[2] = 1.0f;
		outCoord3 = mRenderState.mViewportMatrix * outCoord3;

		// output
		outVertex.x = outCoord3[0];
		outVertex.y = outCoord3[1];

		// save info that doesn't change
		*outVertex.info = *fVertex.info;
		outVertex.info->depth = fVertex.z;
		outVertex.tex = fVertex.tex;

		// save homogeneous info
		outVertex.h = fVertex.w;
	}
}