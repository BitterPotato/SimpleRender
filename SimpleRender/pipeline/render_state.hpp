#ifndef RENDER_STATE_HPP
#define RENDER_STATE_HPP

//#define BSP_ENABLE

#include "bsp.hpp"
#include "vertex_shader.hpp"
#include "frag_shader.hpp"
#include "render_struc.hpp"

#include "../math/tvector_trans.hpp"
#include "../math/tmatrix_trans.hpp"

#include "../raster/Frag.hpp"
#include "../raster/Texture.hpp"

#include <vector>
#include <memory>

using math::frontviewMatrix;
using math::perspectiveMatrix;
using math::lookatMatrix;
using math::eulerAsMatrix;
using math::asMat4;
using math::radians;
using math::translate;
using math::viewportMatrixReflectY;

using std::vector;
using std::unique_ptr;

#define TRIANGLE_POINTS 3
#define LINE_POINTS 2

class RenderState {
public:
	GL_MODE mMode;
	GL_PATTERN mPattern = GL_NORMAL;
	unique_ptr<Texture> mTexture;

	// the lifecycle was controlled outside
	unique_ptr<VertexShader> mVertexShader;
	unique_ptr<FragShader> mFragShader;

	// for render pipeline
	int width, height;
	fmat4 mTransformMatrix = fmat4(1.0f);
	fmat4 mLookatMatrix = fmat4(1.0f);
	fmat4 mProjMatrix = fmat4(1.0f);
	fmat3 mViewportMatrix = fmat3(1.0f);

	bool isDataValid = false;
#ifdef BSP_ENABLE
	BSPTree* mBSPTree;
#endif
#ifndef BSP_ENABLE
	vector<FVertex>* vertexDataPtr;
#endif
	
	RenderState() {
		mTransformMatrix = asMat4(eulerAsMatrix(pitch, yaw, roll, EULER_ORDER));
		mLookatMatrix = lookatMatrix(cameraPosition, cameraCenter, cameraUp);
		mProjMatrix = frontviewMatrix(fvec3(-1.0f, -1.0f, 0.0f),
			fvec3(1.0f, 1.0f, -2.0f));
	}
	~RenderState() {
#ifdef BSP_ENABLE
		delete mBSPTree;
#endif
#ifndef BSP_ENABLE
		if (vertexDataPtr != nullptr)
			delete vertexDataPtr;
#endif
	}

	const fvec3& getCameraPosition() const {
		return cameraPosition;
	}
	void triggerCameraFlatMove(const CAMERA_MOVE move, const float degree);

	void triggerCameraCircleMove(const CAMERA_MOVE move, const float degree);

	void triggerCameraRotate(const CAMERA_ROTATE rotate, const float radians);

	void attachViewport(const int width, const int height) {
		this->width = width;
		this->height = height;
		this->mViewportMatrix = viewportMatrixReflectY(static_cast<float>(width), static_cast<float>(height));
	}

	void attachShader(unique_ptr<VertexShader>& vertexShader, unique_ptr<FragShader>& fragShader) {
		mVertexShader.reset(vertexShader.release());
		mFragShader.reset(fragShader.release());
	}

	bool checkDataAndRet(const GL_MODE& mode, const vector<FVertex>& vertexData) const;

	void RenderState::attachVertexData(const GL_MODE& Mode, vector<FVertex>& outVertexData);
private:
	const string EULER_ORDER = "xyz";

	// for application
	// default camera
	fvec3 cameraPosition = fvec3(0.0f, 0.0f, 1.0f);
	fvec3 cameraCenter = fvec3(0.0f, 0.0f, 0.0f);
	fvec3 cameraUp = fvec3(0.0f, 1.0f, 0.0f);

	// thing rotate
	int pitch = 0, yaw = 0, roll = 0;
	
};
#endif
