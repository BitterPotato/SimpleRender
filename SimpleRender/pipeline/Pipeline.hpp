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
using Gl::Raster;

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
    MY_UTIL_DECL void pushMore(vector<FVertex>& vertexData, const FVertex& vertexA, const FVertex& vertexB, const FVertex& vertexC) {
		vertexData.push_back(vertexA);
		vertexData.push_back(vertexB);
		vertexData.push_back(vertexC);
	}

    MY_UTIL_DECL void dealWithTwo(vector<FVertex>& outVertexData, const FVertex& vertexOut, const FVertex& vertexFirst, const FVertex& vertexSecond, const bool reverse) {
		FVertex interVertexThis, interVertexThat;
		computeInterSect(vertexFirst, vertexOut, interVertexThis);
		computeInterSect(vertexSecond, vertexOut, interVertexThat);

		pushMore(outVertexData, interVertexThis, vertexFirst, vertexSecond);
		if (reverse)
			pushMore(outVertexData, interVertexThis, vertexSecond, interVertexThat);
		else
			pushMore(outVertexData, interVertexThis, interVertexThat, vertexSecond);
	}
    MY_UTIL_DECL void dealWithOne(vector<FVertex>& outVertexData, const FVertex& vertexIn, const FVertex& vertexFirst, const FVertex& vertexSecond) {
		FVertex interVertexThis, interVertexThat;
		computeInterSect(vertexIn, vertexFirst, interVertexThis);
		computeInterSect(vertexIn, vertexSecond, interVertexThat);

		pushMore(outVertexData, vertexIn, interVertexThis, interVertexThat);
	}

	// clip, may increase or decrease vertexes
	MY_UTIL_DECL void clip(const GL_MODE& mode, const vector<FVertex>& vertexData, vector<FVertex>& outVertexData) ;

	MY_SMALL_FUNC_DECL void afterClip(const FVertex& fVertex, Vertex& outVertex) const;

};

#endif