#include "RenderState.hpp"
#include "common/FVertex.hpp"

using math::dirtVec;
using math::rightVec;

void RenderState::triggerCameraFlatMove(const CAMERA_MOVE move, const float degree) {
	switch (move)
	{
	case UP_MOVE:
		cameraPosition[1] += degree;
		cameraCenter[1] += degree;
		break;
	case DOWN_MOVE:
		cameraPosition[1] -= degree;
		cameraCenter[1] -= degree;
		break;
	case LEFT_MOVE:
		cameraPosition[0] -= degree;
		cameraCenter[0] -= degree;
		break;
	case RIGHT_MOVE:
		cameraPosition[0] += degree;
		cameraCenter[0] += degree;
		break;
	default:
		break;
	}
	mLookatMatrix = lookatMatrix(cameraPosition, cameraCenter, cameraUp);
}

// this method only change the position of camera
void RenderState::triggerCameraCircleMove(const CAMERA_MOVE move, const float degree) {
	switch (move)
	{
        case UP_MOVE: {
//            cameraPosition[1] += degree;
			cameraPosition = cameraPosition + mUpVec * degree;
            break;
        }
        case DOWN_MOVE: {
//            cameraPosition[1] -= degree;
			cameraPosition = cameraPosition - mUpVec * degree;
            break;
        }
        case LEFT_MOVE: {
            // along the right direction
            fvec3 right = rightVec(cameraPosition, cameraCenter, cameraUp);
            cameraPosition = cameraPosition - mRightVec * degree;
			cout << cameraPosition <<endl;
            break;
        }
        case RIGHT_MOVE: {
            cameraPosition = cameraPosition + mRightVec * degree;
			cout << cameraPosition <<endl;
            break;
        }
        case FRONT_MOVE: {
            // along the lookat direction
            cameraPosition = cameraPosition + mDirtVec * degree;
            break;
        }
        case BACK_MOVE: {
            cameraPosition = cameraPosition - mDirtVec * degree;
            break;
        }
        default: {
            break;
        }
	}
	mLookatMatrix = lookatMatrix(mDirtVec, mRightVec, mUpVec, cameraPosition);

}

void RenderState::triggerCameraRotate(const CAMERA_ROTATE rotate, const int degrees) {
	switch (rotate)
	{
	case PITCH_ANTI:
		pitch += degrees;
		break;
	case PITCH:
		pitch -= degrees;
		break;
	case YAW_ANTI:
		yaw += degrees;
		break;
	case YAW:
		yaw -= degrees;
		break;
//	case ROLL_ANTI:
//		roll += degrees;
//		break;
//	case ROLL:
//		roll -= degrees;
//		break;
	default:
		break;
	}
	mDirtVec = eulerAsMatrix(pitch, yaw, roll, EULER_ORDER) * mBaseDirtVec;
	cameraCenter = cameraPosition + mDirtVec;
    cout << cameraCenter << endl;
	mLookatMatrix = lookatMatrix(cameraPosition, cameraCenter, cameraUp, mDirtVec, mRightVec, mUpVec);
}

bool RenderState::checkData(const GL_MODE mode, const int dataSize) const {
	if(dataSize == 0)
		return false;

	switch(mode) {
		case GL_POINTS:
			return true;
		case GL_LINES:
			return dataSize % LINE_COUNT == 0;
		case GL_TRIANGLES:
			return dataSize % TRI_COUNT == 0;
		case GL_TRIANGLES_STRIP:
			return dataSize >= TRI_COUNT;
		default:
			return false;
	}
}

// turn over the control
void RenderState::attachVertexData(const GL_MODE& mode, FVertexContainer& outVertexData, IndexContainer& indexContainer) {
	this->mMode = mode;
    this->fVertexContainerPtr = make_shared<FVertexContainer >(outVertexData);

#ifdef BSP_ENABLE
		if(supportBSP(mode)) {
			if(isDataValid = checkData(mode, indexContainer.size())) {
				// when BSPTree is constructed, fVertexData in the RenderState can be disposed
				mBSPTree = new BSPTree(mMode, *fVertexContainerPtr, indexContainer);
				this->indexContainerPtr = make_shared<IndexContainer >(IndexContainer());
			}
			else {
				// do nothing, not valid data
			}
		}
		else {
			isDataValid = true;
			this->indexContainerPtr = make_shared<IndexContainer >(indexContainer);
		}
#endif
#ifndef BSP_ENABLE
		isDataValid = true;
		this->indexContainerPtr = make_shared<IndexContainer >(indexContainer);
#endif
	}