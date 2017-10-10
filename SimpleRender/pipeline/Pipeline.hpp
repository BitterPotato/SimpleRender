#ifndef STAGE_FLOW_HPP
#define STAGE_FLOW_HPP

#define CLIP_ENABLE

#include "common/setup.hpp"
#include "mesh/Container.hpp"

class Vertex;
class FVertex;

#include "RenderState.hpp"
#include "VertexShader.hpp"
#include "FragShader.hpp"
#include "gl_utils.hpp"

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

	// clip, may increase or decrease vertexes
	MY_UTIL_DECL void clip(const GL_MODE &mode, FVertexContainer &fVertexData, IndexContainer &indexContainer) ;

	MY_SMALL_FUNC_DECL void afterClip(const FVertex& fVertex, Vertex& outVertex) const;

};

#include "Pipeline.inl"

#endif