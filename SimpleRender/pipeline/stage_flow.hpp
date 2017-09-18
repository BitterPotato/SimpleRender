#ifndef STAGE_FLOW_HPP
#define STAGE_FLOW_HPP

//#define CLIP_ENABLE

#include "vertex_shader.hpp"
#include "frag_shader.hpp"
#include "raster_stage.hpp"
#include "../raster/Texture.hpp"
#include "../platform/framebuffer.hpp"
#include "../math/tmatrix_trans.hpp"
#include "../math/tvector_trans.hpp"
#include "render_state.hpp"
#include "gl_utils.hpp"

#include <vector>
#include <exception>
#include <stdexcept>
#include <cmath>
#include <memory>

using gl::raster;
using math::homogeneous;

using std::vector;

namespace gl {
class Pipeline {
public:
	Pipeline(RenderState& renderState) : mRenderState(renderState) {}

	void requestRender() {
		useProgram(mRenderState.mVertexShader, mRenderState.mFragShader);
	}

	Pipeline(const Pipeline& pipeline) = delete;
	Pipeline& operator=(Pipeline pipeline) = delete;
	~Pipeline() {
	}
private:
	RenderState& mRenderState;

	void useProgram(const unique_ptr<VertexShader>& vertexShader, const unique_ptr<FragShader>& fragShader);

	void pipeTrans(FVertex& fVertex) const;

	// TODO: form structure
	void pushMore(vector<FVertex>& vertexData, const FVertex& vertexA, const FVertex& vertexB, const FVertex& vertexC) const {
		vertexData.push_back(vertexA);
		vertexData.push_back(vertexB);
		vertexData.push_back(vertexC);
	}

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
	void clip(const GL_MODE& mode, const vector<FVertex>& vertexData, vector<FVertex>& outVertexData) const;

	void afterClip(const FVertex& fVertex, Vertex& outVertex) const;

};

}
#endif