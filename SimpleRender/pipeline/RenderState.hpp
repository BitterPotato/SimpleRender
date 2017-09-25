#ifndef RENDER_STATE_HPP
#define RENDER_STATE_HPP

//#define BSP_ENABLE

#include "BSPTree.hpp"
#include "MyVertexShader.hpp"
#include "MyFragShader.hpp"
#include "RenderSetup.hpp"
#include "math/TVector_Trans.hpp"
#include "math/TMatrix_Trans.hpp"
#include "material/Texture.hpp"


using math::frontviewMatrix;
using math::perspectiveMatrix;
using math::lookatMatrix;
using math::eulerAsMatrix;
using math::asMat4;
using math::radians;
using math::translate;
using math::viewportMatrixReflectY;


#define TRIANGLE_POINTS 3
#define LINE_POINTS 2

class RenderState {
	friend class SimpleDelegate;
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
	unique_ptr<vector<FVertex>> vertexDataPtr;
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
		// do nothing
#endif
	}

	MY_SMALL_FUNC_DECL const fvec3& getCameraPosition() const {
		return cameraPosition;
	}
	MY_COMP_FUNC_DECL void triggerCameraFlatMove(const CAMERA_MOVE move, const float degree);

	MY_COMP_FUNC_DECL void triggerCameraCircleMove(const CAMERA_MOVE move, const float degree);

	MY_COMP_FUNC_DECL void triggerCameraRotate(const CAMERA_ROTATE rotate, const float radians);

	MY_SMALL_FUNC_DECL void attachViewport(const int width, const int height) {
		this->width = width;
		this->height = height;
		this->mViewportMatrix = viewportMatrixReflectY(static_cast<float>(width), static_cast<float>(height));
	}

	MY_SMALL_FUNC_DECL void attachShader(unique_ptr<VertexShader>& vertexShader, unique_ptr<FragShader>& fragShader) {
		mVertexShader.reset(vertexShader.release());
		mFragShader.reset(fragShader.release());
	}

	MY_COMP_FUNC_DECL bool checkDataAndRet(const GL_MODE& mode, const vector<FVertex>& vertexData) const;

	MY_COMP_FUNC_DECL void attachVertexData(const GL_MODE& Mode, vector<FVertex>& outVertexData);
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
