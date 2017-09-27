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

bool RenderState::checkDataAndRet(const GL_MODE& mode, const vector<FVertex>& vertexData) const {
	switch (mode) {
	case GL_LINES:
		if (vertexData.size() % LINE_POINTS != 0) {
//			throw logic_error("not enough points for triangles");
			return false;
		}
		break;
	case GL_TRIANGLES:
		if (vertexData.size() % TRIANGLE_POINTS != 0) {
//			throw logic_error("not enough points for triangles");
			return false;
		}
	}
	return true;
}

// turn over the control
void RenderState::attachVertexData(const GL_MODE& mode, vector<FVertex>& outVertexData) {
	this->mMode = mode;

	if (!checkDataAndRet(mMode, outVertexData)) {
		isDataValid = false;
		return;
	}
	isDataValid = true;

#ifdef BSP_ENABLE
	// trigger construct BSP
	// may modify the outVertexData
	mBSPTree = new BSPTree(mMode, outVertexData);
#endif
#ifndef BSP_ENABLE 
	// TODO: maybe wrong usage
	this->vertexDataPtr = unique_ptr<vector<FVertex>>(&outVertexData);
#endif
}