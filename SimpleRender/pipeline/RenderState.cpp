#include "RenderState.hpp"
#include "common/FVertex.hpp"

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

void RenderState::triggerCameraCircleMove(const CAMERA_MOVE move, const float degree) {
	switch (move)
	{
	case UP_MOVE:
		cameraPosition[1] += degree;
		break;
	case DOWN_MOVE:
		cameraPosition[1] -= degree;
		break;
	case LEFT_MOVE:
		cameraPosition[0] -= degree;
		break;
	case RIGHT_MOVE:
		cameraPosition[0] += degree;
		break;
	default:
		break;
	}
	mLookatMatrix = lookatMatrix(cameraPosition, cameraCenter, cameraUp);
}

void RenderState::triggerCameraRotate(const CAMERA_ROTATE rotate, const float radians) {
	switch (rotate)
	{
	case PITCH_ANTI:
		pitch += radians;
		break;
	case PITCH:
		pitch -= radians;
		break;
	case YAW_ANTI:
		yaw += radians;
		break;
	case YAW:
		yaw -= radians;
		break;
	case ROLL_ANTI:
		roll += radians;
		break;
	case ROLL:
		roll -= radians;
		break;
	default:
		break;
	}
	// rotate the thing itself at current
	mTransformMatrix = asMat4(eulerAsMatrix(pitch, yaw, roll, EULER_ORDER));

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
			if(isDataValid = checkData(mode, fVertexContainerPtr->size())) {
				// when BSPTree is constructed, fVertexData in the RenderState can be disposed
				mBSPTree = new BSPTree(mMode, *fVertexContainerPtr);
			}
			else {
				// do nothing, not valid data
			}
		}
		else {
			isDataValid = true;
			this->indexContainerPtr = make_shared<IndexContainer >(indexContainerPtr);
		}
#endif
#ifndef BSP_ENABLE
		isDataValid = true;
		this->indexContainerPtr = make_shared<IndexContainer >(indexContainer);
#endif
	}