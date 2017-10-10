#ifndef RENDER_STATE_HPP
#define RENDER_STATE_HPP

//#define BSP_ENABLE

#ifdef BSP_ENABLE
#include "BSPTree.hpp"
#endif

#include "VertexShader.hpp"
#include "FragShader.hpp"
#include "RenderSetup.hpp"
#include "math/TVector_Trans.hpp"
#include "math/TMatrix_GL.hpp"
#include "math/TMatrix_Rotate.hpp"

// TODO: why smart pointers cannot get together with forward declaration
//class Texture;
#include "material/Texture.hpp"
#include "mesh/Container.hpp"

using math::frontviewMatrix;
using math::perspectiveMatrix;
using math::lookatMatrix;
using math::eulerAsMatrix;
using math::asMat4;
using math::radians;
using math::translate;
using math::viewportMatrixReflectY;

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
;
	bool isDataValid = false;
#ifdef BSP_ENABLE
	BSPTree* mBSPTree;
#endif
	shared_ptr<IndexContainer> indexContainerPtr;
// add one reference count to the vertex data(so they won't be disposed)
	shared_ptr<FVertexContainer> fVertexContainerPtr;
	
	RenderState() {
		mLookatMatrix = lookatMatrix(cameraPosition, cameraCenter, cameraUp, mDirtVec, mRightVec, mUpVec);
        mBaseDirtVec = mDirtVec;
        // notice: modified based the camera position
		mProjMatrix = frontviewMatrix(fvec3(-1.0f, -1.0f, 0.0f), fvec3(1.0f, 1.0f, -2.0f));
//        mProjMatrix = perspectiveMatrix(radians(90.0f), 1.0f, -0.1f, 2.0f);
	}
	~RenderState() {
#ifdef BSP_ENABLE
        if(mBSPTree) {
			delete mBSPTree;
			mBSPTree = nullptr;
		}
#endif
		// do nothing
	}

	MY_SMALL_FUNC_DECL const fvec3& getCameraPosition() const {
		return cameraPosition;
	}
	MY_COMP_FUNC_DECL void triggerCameraFlatMove(const CAMERA_MOVE move, const float step);

	MY_COMP_FUNC_DECL void triggerCameraCircleMove(const CAMERA_MOVE move, const float step);

	MY_COMP_FUNC_DECL void triggerCameraRotate(const CAMERA_ROTATE rotate, const int degrees);

	MY_SMALL_FUNC_DECL void attachViewport(const int width, const int height) {
		this->width = width;
		this->height = height;
		this->mViewportMatrix = viewportMatrixReflectY(static_cast<float>(width), static_cast<float>(height));
	}

	MY_SMALL_FUNC_DECL void attachShader(unique_ptr<VertexShader>& vertexShader, unique_ptr<FragShader>& fragShader) {
		mVertexShader.reset(vertexShader.release());
		mFragShader.reset(fragShader.release());
	}

	MY_COMP_FUNC_DECL void attachVertexData(const GL_MODE& Mode, FVertexContainer& outVertexData, IndexContainer& indexContainer);
private:
	const string EULER_ORDER = "xyz";

	// for application
	// default camera
	fvec3 cameraPosition = fvec3(0.0f, 0.0f, 1.0f);
    fvec3 cameraCenter = fvec3(0.0f, 0.0f, 0.0f);
	fvec3 cameraUp = fvec3(0.0f, 1.0f, 0.0f);

    // since only rotate will change dirt vec
    fvec3 mBaseDirtVec;
    fvec3 mDirtVec;
    fvec3 mRightVec;
    fvec3 mUpVec;

	// thing rotate
	int pitch = 0, yaw = 0, roll = 0;

    MY_SMALL_FUNC_DECL bool supportBSP(const GL_MODE mode) const {
        return mode == GL_TRIANGLES || mode == GL_TRIANGLES_STRIP;
    }

    MY_COMP_FUNC_DECL bool checkData(const GL_MODE mode, const int dataSize) const ;
};
#endif
