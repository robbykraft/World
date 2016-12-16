#ifdef OS_WINDOWS
#  include "../lib/glew-2.0.0/include/GL/glew.h"
#  include "../lib/glew-2.0.0/src/wglew.c"
#else
#  include "../lib/glew-2.0.0/include/GL/glew.h"
#  include "../lib/glew-2.0.0/src/glew.c"
#endif

#include "../world.h"

GLuint shader = 0;
GLuint shader2 = 0;

void setup() {
	hideHelpfulOrientation();
	shader = loadShader( "shaders/simple.vert", "shaders/cave.frag" );
}
void update() {
	float resolution[2] = {WIDTH, HEIGHT};
	setShaderUniformVec2f(shader, "u_resolution", resolution);
	setShaderUniform1f(shader, "u_time", frameNum/60.0);
}
void draw3D() { }
void draw2D() {
	glUseProgram(shader);
	drawRect(0,0,0, WIDTH, HEIGHT);
	glUseProgram(0);
}
void keyDown(unsigned int key) { }
void keyUp(unsigned int key) { }
void mouseDown(unsigned int button) { }
void mouseUp(unsigned int button) { }
void mouseMoved(int x, int y) { }