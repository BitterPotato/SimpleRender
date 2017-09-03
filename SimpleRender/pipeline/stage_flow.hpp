#ifndef STAGE_FLOW_HPP
#define STAGE_FLOW_HPP

#include "vertex_shader.hpp"
#include "frag_shader.hpp"
#include "raster_stage.hpp"
#include "../platform/framebuffer.hpp"

#include <vector>

using gl::raster;
using std::vector;

namespace gl {
class Pipeline {
public:
	void confViewport(const int& width, const int& height) {
		this->width = width;
		this->height = height;
	}
	//void confCamera() {}
	void confMode(const GL_MODE& mode) {
		this->tMode = mode;
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
		raster(tMode, vecVertex, fragCache);

		// 4. frag vertex
		fragCache.runFrags(fragShader);
	}
private:
	GL_MODE tMode;

	int width, height;

	inline void pipeTrans(const FVertex& fVertex, Vertex& outVertex) const {
		*outVertex.info = *fVertex.info;
		
		// 1. Model - World Transform

		// 2. World - Camera Transform

		// 3. Camera - Clip Transform

		// 4. Clip - Viewport Transform
		outVertex.x = width / 2 * (1 + fVertex.x);
		outVertex.y = height / 2 * (1 + fVertex.y);
	}

};

}
#endif