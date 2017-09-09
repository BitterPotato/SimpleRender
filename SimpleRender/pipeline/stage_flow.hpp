#ifndef STAGE_FLOW_HPP
#define STAGE_FLOW_HPP

#include "vertex_shader.hpp"
#include "frag_shader.hpp"
#include "raster_stage.hpp"
#include "../raster/Texture.hpp"
#include "../platform/framebuffer.hpp"
#include "../math/tmatrix_trans.hpp"
#include "../math/tvector_trans.hpp"

#include <vector>
#include <exception>
#include <stdexcept>
#include <cmath>

using gl::raster;
using math::viewportMatrixReflectY;
using math::viewportMatrix;
using math::homogeneous;

using std::vector;
using std::logic_error;

#define TRIANGLE_POINTS 3
#define LINE_POINTS 2

namespace gl {
class Pipeline {
public:
	Pipeline() {

	}
	void confTransform(const fmat4& transformMatrix) {
		this->mTransformMatrix = transformMatrix;
	}
	void confCamera(const fmat4& lookatMatrix) {
		this->mLookatMatrix = lookatMatrix;
	}
	void confProjection(const fmat4& projMatrix) {
		this->mProjMatrix = projMatrix;
	}
	void confViewport(const int& width, const int& height) {
		this->width = width;
		this->height = height;
		this->mViewportMatrix = viewportMatrixReflectY(static_cast<float>(width), static_cast<float>(height));
	}

	void confMode(const GL_MODE& mode) {
		this->mMode = mode;
	}

	void confPattern(const GL_PATTERN& pattern) {
		this->mPattern = pattern;
	}

	void confTexture(Texture* texture) {
		this->texture = texture;
	}

	void useProgram(const vector<FVertex>& vertexData, const VertexShader& vertexShader, const FragShader& fragShader) const {
		if (!isDataValid(mMode, vertexData))
			return;

		vector<FVertex> beforeClipVertexData;
		for (auto iter = vertexData.begin(); iter != vertexData.end(); iter++) {
			// 1. vertex shader
			FVertex& afterVS = FVertex();
			vertexShader.shade(*iter, afterVS);

			// 2. pipeline deal£¨model - lookat - projection transform£©
			this->pipeTrans(afterVS);
			beforeClipVertexData.push_back(afterVS);
		}
		// 3. clip 
		vector<FVertex> afterClipVertexData;
		this->clip(mMode, beforeClipVertexData, afterClipVertexData);
		
		// 3.5 homogeneous && viewport transform
		vector<Vertex> beforeRasterVertexData;
		for (auto iter = afterClipVertexData.begin(); iter != afterClipVertexData.end(); iter++) {
			Vertex vertex = Vertex();
			this->afterClip(*iter, vertex);
			beforeRasterVertexData.push_back(vertex);
		}

		// 4. raster
		FragCache fragCache;
		raster(mMode, mPattern, beforeRasterVertexData, texture, fragCache);

		// 5. frag vertex
		fragCache.runFrags(fragShader);
	}

	Pipeline(const Pipeline& pipeline) = delete;
	Pipeline& operator=(Pipeline pipeline) = delete;
	~Pipeline() {
		if (texture != nullptr)
			delete texture;
	}
private:
	GL_MODE mMode;
	GL_PATTERN mPattern = GL_NORMAL;

	int width, height;

	fmat4 mTransformMatrix = fmat4(1.0f);
	fmat4 mLookatMatrix = fmat4(1.0f);
	fmat4 mProjMatrix = fmat4(1.0f);
	fmat3 mViewportMatrix = fmat3(1.0f);

	Texture* texture = nullptr;

	bool isDataValid(const GL_MODE& mode, const vector<FVertex> vertexData) const {
		switch (mode) {
		case GL_LINES:
			if (vertexData.size() % LINE_POINTS != 0) {
				throw logic_error("not enough points for triangles");
				return false;
			}
			break;
		case GL_TRIANGLES:
			if (vertexData.size() % TRIANGLE_POINTS != 0) {
				throw logic_error("not enough points for triangles");
				return false;
			}
		}
		return true;
	}

	void pipeTrans(FVertex& fVertex) const {
		fvec4 outCoord4(fVertex.x, fVertex.y, fVertex.z, 1.0f);
		// 1. Model - World Transform	
		// 2. World - Camera Transform
		// 3. Camera - Clip Transform
		outCoord4 = mLookatMatrix*mTransformMatrix*outCoord4;
		outCoord4 = mProjMatrix*outCoord4;
		//outCoord4 = mProjMatrix*mLookatMatrix*mTransformMatrix*outCoord4;

		fVertex.x = outCoord4[0];
		fVertex.y = outCoord4[1];
		fVertex.z = outCoord4[2];
		fVertex.w = outCoord4[3];
	}

	inline bool isInVisualBody(const FVertex& fVertex) const {
		float x = fVertex.x;
		float y = fVertex.y;
		float z = fVertex.z;
		float w = fVertex.w;

		return x >= -w && x <= w
			&& y >= -w && y <= w
			&& z >= -w && z <= w;
	}

	inline void dicideAssignTo(const float& t, float& val) const {
		if (t >= 0.0f && t <= 1.0f && t < val)
			val = t;
	}

	void computeInterSect(const FVertex& vertexIn, const FVertex& vertexOut, FVertex& outVertex) const {

		float ix = vertexIn.x;
		float iy = vertexIn.y;
		float iz = vertexIn.z;
		float iw = vertexIn.w;

		float ox = vertexOut.x;
		float oy = vertexOut.y;
		float oz = vertexOut.z;
		float ow = vertexOut.w;

		// line segment: vertexIn + t(VertexOut-vertexIn)
		// t \in [0, 1]
		float val = 1.0f;
		float tx;
		if (vertexOut.x > vertexIn.x) {
			// will intersect with plane: x = iw + t(ow - iw)
			// notice: divide zero will not cause exception
			tx = (iw - ix) / ((ox - ow) - (ix - iw));
		}
		else {
			tx = (-iw - ix) / ((ox - ow) - (ix - iw));
		}
		dicideAssignTo(tx, val);
		float ty;
		if (vertexOut.y > vertexIn.y) {
			// will intersect with plane: x = iw + t(ow - iw)
			ty = (iw - iy) / ((oy - ow) - (iy - iw));
		}
		else {
			ty = (-iw - iy) / ((oy - ow) - (iy - iw));
		}
		dicideAssignTo(ty, val);
		float tz;
		if (vertexOut.z > vertexIn.z) {
			// will intersect with plane: x = iw + t(ow - iw)
			tz = (iw - iz) / ((oz - ow) - (iz - iw));
		}
		else {
			tz = (-iw - iz) / ((oz - ow) - (iz - iw));
		}
		dicideAssignTo(tz, val);

		inter(vertexIn, vertexOut, val, outVertex);
	}

	void pushMore(vector<FVertex>& vertexData, const FVertex& vertexA, const FVertex& vertexB, const FVertex& vertexC) const {
		vertexData.push_back(vertexA);
		vertexData.push_back(vertexB);
		vertexData.push_back(vertexC);
	}

	//if (!isInVisualBody(vertexA)) {
	//	computeInterSect(vertexB, vertexA, interVertexThis);
	//	computeInterSect(vertexC, vertexA, interVertexThat);

	//	pushMore(outVertexData, interVertexThis, vertexB, vertexC);
	//	pushMore(outVertexData, interVertexThis, vertexC, interVertexThat);
	//}
	//else if (!isInVisualBody(vertexB)) {
	//	computeInterSect(vertexA, vertexB, interVertexThis);
	//	computeInterSect(vertexC, vertexB, interVertexThat);

	//	pushMore(outVertexData, interVertexThis, vertexC, vertexA);
	//	pushMore(outVertexData, interVertexThis, interVertexThat, vertexC);
	//}
	//else if (!isInVisualBody(vertexC)) {
	//	computeInterSect(vertexA, vertexC, interVertexThis);
	//	computeInterSect(vertexB, vertexC, interVertexThat);

	//	pushMore(outVertexData, interVertexThis, vertexA, vertexB);
	//	pushMore(outVertexData, interVertexThis, vertexB, interVertexThat);
	//}
	void dealWithTwo(vector<FVertex>& outVertexData, const FVertex& vertexOut, const FVertex& vertexFirst, const FVertex& vertexSecond, const bool reverse) const {
		FVertex interVertexThis, interVertexThat;
		computeInterSect(vertexFirst, vertexOut, interVertexThis);
		computeInterSect(vertexSecond, vertexOut, interVertexThat);

		pushMore(outVertexData, interVertexThis, vertexFirst, vertexSecond);
		if (reverse)
			pushMore(outVertexData, interVertexThis, vertexSecond, interVertexThat);
		else
			pushMore(outVertexData, interVertexThis, interVertexThat, vertexSecond);
	}
	void dealWithOne(vector<FVertex>& outVertexData, const FVertex& vertexIn, const FVertex& vertexFirst, const FVertex& vertexSecond) const {
		FVertex interVertexThis, interVertexThat;
		computeInterSect(vertexIn, vertexFirst, interVertexThis);
		computeInterSect(vertexIn, vertexSecond, interVertexThat);

		pushMore(outVertexData, vertexIn, interVertexThis, interVertexThat);
	}
	// clip, may increase or decrease vertexes
	void clip(const GL_MODE& mode, const vector<FVertex>& vertexData, vector<FVertex>& outVertexData) const {
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
					outVertexData.push_back(*(iter+1));
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
					computeInterSect(*(iter+1), *iter, interVertex);

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

	void afterClip(const FVertex& fVertex, Vertex& outVertex) const {
		// 3_5. as for perspective projection, needs a stage called 'Homogeneous'
		fvec3 outCoord3 = homogeneous(fvec4(fVertex.x, fVertex.y, fVertex.z, fVertex.w));

		// 4. Clip - Viewport Transform
		outCoord3[2] = 1.0f;
		outCoord3 = mViewportMatrix * outCoord3;

		// output
		outVertex.x = outCoord3[0];
		outVertex.y = outCoord3[1];

		// save info that doesn't change
		*outVertex.info = *fVertex.info;
		outVertex.tex = fVertex.tex;

		// save homogeneous info
		outVertex.h = fVertex.w;
	}

};

}
#endif