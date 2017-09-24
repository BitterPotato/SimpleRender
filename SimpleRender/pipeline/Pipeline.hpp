#ifndef STAGE_FLOW_HPP
#define STAGE_FLOW_HPP

//#define CLIP_ENABLE

#include "MyVertexShader.hpp"
#include "MyFragShader.hpp"
#include "raster/Raster.hpp"
#include "material/Texture.hpp"
#include "platform/FrameBuffer.hpp"
#include "math/TMatrix_Trans.hpp"
#include "math/TVector_Trans.hpp"
#include "RenderState.hpp"
#include "gl_utils.hpp"

#include <vector>
#include <exception>
#include <stdexcept>
#include <cmath>
#include <memory>

using math::homogeneous;

using std::vector;

class Pipeline {
public:
	Pipeline(RenderState& renderState) : mRenderState(renderState) {}

	MY_SMALL_FUNC_DECL void requestRender() {
		useProgram(mRenderState.mVertexShader, mRenderState.mFragShader);
	}

	Pipeline(const Pipeline& pipeline) = delete;
	Pipeline& operator=(Pipeline pipeline) = delete;
	~Pipeline() {
	}
private:
	RenderState& mRenderState;

	MY_COMP_FUNC_DECL void useProgram(const unique_ptr<VertexShader>& vertexShader, const unique_ptr<FragShader>& fragShader);

	MY_SMALL_FUNC_DECL void pipeTrans(FVertex& fVertex) const;

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
	MY_UTIL_DECL void clip(const GL_MODE& mode, const vector<FVertex>& vertexData, vector<FVertex>& outVertexData) const;

	MY_SMALL_FUNC_DECL void afterClip(const FVertex& fVertex, Vertex& outVertex) const;

};

#endif