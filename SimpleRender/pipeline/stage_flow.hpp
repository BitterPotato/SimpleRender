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

using gl::raster;
using math::viewportMatrix;
using math::homogeneous;

using std::vector;

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
		this->mViewportMatrix = viewportMatrix(static_cast<float>(width), static_cast<float>(height));
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

	inline void useProgram(vector<FVertex>& vertexData, const VertexShader& vertexShader, const FragShader& fragShader) const {
		vector<Vertex> vecVertex;
		for (auto iter = vertexData.begin(); iter != vertexData.end(); iter++) {
			// 1. vertex shader
			FVertex& afterVS = FVertex();
			vertexShader.shade(*iter, afterVS);

			// 2. pipeline deal
			Vertex& beforeRaster = Vertex();
			this->pipeTrans(afterVS, beforeRaster);

			// vector will do deep copy
			vecVertex.push_back(beforeRaster);
		}
		// 3. raster
		FragCache fragCache;
		raster(mMode, mPattern, vecVertex, texture, fragCache);

		// 4. frag vertex
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

	inline void pipeTrans(const FVertex& fVertex, Vertex& outVertex) const {
		// save info that doesn't change
		*outVertex.info = *fVertex.info;
		outVertex.tex = fVertex.tex;
		
		fvec4 outCoord4(fVertex.x, fVertex.y, fVertex.z, 1.0f);
		// 1. Model - World Transform	
		// 2. World - Camera Transform
		// 3. Camera - Clip Transform
		outCoord4 = mProjMatrix*mLookatMatrix*mTransformMatrix*outCoord4;

		// 3_5. as for perspective projection, needs a stage called 'Homogeneous'
		// save homogeneous info
		outVertex.h = outCoord4[3];
		fvec3 outCoord3 = homogeneous(outCoord4);

		// 4. Clip - Viewport Transform
		outCoord3[2] = 1.0f;
		outCoord3 = mViewportMatrix * outCoord3;

		// output
		outVertex.x = outCoord3[0];
		outVertex.y = outCoord3[1];
	}

};

}
#endif