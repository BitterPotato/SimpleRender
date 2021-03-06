#ifndef RENDER_STRUC_HPP
#define RENDER_STRUC_HPP

enum GL_MODE : char {
	GL_POINTS,
	GL_LINES,
	GL_TRIANGLES,
	GL_TRIANGLES_STRIP
};

enum GL_PATTERN : char {
	GL_NORMAL,
	GL_WIREFRAME
};
enum CAMERA_MOVE : char {
	// means to up/ down/ left/ right/ front/ back
	UP_MOVE, DOWN_MOVE, LEFT_MOVE, RIGHT_MOVE, FRONT_MOVE, BACK_MOVE
};
enum CAMERA_ROTATE : char {
	PITCH_ANTI, PITCH,
	YAW_ANTI, YAW,
	ROLL_ANTI, ROLL
};

#endif