#ifndef WORLD_FRAMEWORK
#define WORLD_FRAMEWORK

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

///////////////////////////////////////////////////////////////////////////////////////
//      WORLD is a hyper minimalist framework for graphics (OpenGL) 
//   and user input (keyboard, mouse) in the Processing design paradigm
///////////////////////////////////////////////////////////////////////////////////////
//
//   HOW TO USE
//
//   1) make an empty .c file
//   2) #include "world.h"
//   3) implement the following functions below.
//      you're done! build with makefile: 'make', 'make run'
void setup();
void update();
void draw3D();
void draw2D();
void keyDown(unsigned int key);
void keyUp(unsigned int key);
void mouseDown(unsigned int button);
void mouseUp(unsigned int button);
void mouseMoved(int x, int y);
void worldDelegate(unsigned int code); 
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
//  SETTINGS
enum { LEFT, RIGHT };
unsigned char HANDED = LEFT; // 0:left, 1:right. flip coordinate axes orientation.
#define CONTINUOUS_REFRESH 1  // set 0 for maximum battery efficiency, only redraws screen upon input
static unsigned char SETTINGS = 0b11111111; // flip bits to turn on and off features. see documentation.
static unsigned char SIMPLE_SETTINGS = 255;  // simple mode (default) hooks helpful keyboard and visual feedback
static unsigned char ADVANCED_SETTINGS = 0;
// WINDOW 
static int WIDTH = 800;  // (readonly) adjust window dimensions. not able to be set at runtime
static int HEIGHT = 600; // (readonly)
static unsigned char FULLSCREEN = 0;  // fullscreen:1   window:0
static float ASPECT;  // (readonly) aspect ratio of window dimensions
// PROJECTION
static float NEAR_CLIP = 0.1;
static float FAR_CLIP = 10000.0;
static float FOV = 0.1;
// PERSPECTIVE
enum{  FPP,  POLAR,  ORTHO  }; // first persion, polar, orthographic
static unsigned char PERSPECTIVE = FPP;  // initialize point of view in this state
// CAMERA ORIENTATION AND POSITION
float ORIGIN[3] = {0.0f, 0.0f, 0.0f};  // x, y, z, location of the eye
float HORIZON[3] = {0.0f, 0.0f, 7.0f};   // azimuth, altitude, zoom (log)
float WINDOW[4]; // x, y, width, height
static float EYE_HEIGHT = 1.0;  // camera offset above the origin ground plane in first-person perspective mode.
// INPUT
static int mouseX = 0;  // get mouse location, units in pixels
static int mouseY = 0;
static unsigned char keyboard[256];  // get current pressed-state of each keyboard key (0:up, 1:pressed)
// mouse drag
static int mouseDownX, mouseDownY;  // mouse down drag distance
static int mouseDownStartX, mouseDownStartY;  // mouse down initial location
static float MOUSE_SENSITIVITY = 0.333f;
static float WALK_INTERVAL = 0.077f;  // first person walking speed. @ 60 UPS (updates/sec), walk speed (units/sec) = INTERVAL * UPS
static float ZOOM_SPEED = 0.1f;
// TIME
static unsigned long FRAME;  // # times the screen has drawn 
struct timespec START, CURRENT;
static float ELAPSED;  // elapsed time in seconds, includes fractional part
int YEAR, MONTH, DAY, HOUR, MINUTE, SECOND;

// TABLE OF CONTENTS:
int main(int argc, char **argv);  // initialize Open GL context
void typicalOpenGLSettings();  // colors, line width, glEnable
void reshapeWindow(int windowWidth, int windowHeight);  // contains viewport and frustum calls
void rebuildProjection();  // calls one of the three functions below
void toggleFullscreen();
// CHANGE PERSPECTIVE
void firstPersonPerspective();
void polarPerspective();
void orthoPerspective(float x, float y, float width, float height);
// DRAW, ALIGNMENT, INPUT HANDLING
void display();
void updateWorld();  // process input devices
// INPUT DEVICES
void moveOriginWithArrowKeys();
void mouseButtons(int button, int state, int x, int y);  // when mouse button state changes
void mouseMotion(int x, int y);   // when mouse is dragging screen
void mousePassiveMotion(int x, int y);  // when mouse is moving but not pressed
void keyboardDown(unsigned char key, int x, int y);
void keyboardUp(unsigned char key,int x,int y);
void specialDown(int key, int x, int y);
void specialUp(int key, int x, int y);
void keyboardSetIdleFunc();
// TINY OPENGL TOOLBOX: all 2D shapes are in the X Y plane, normal along the Z
void fill();    // fill vs. wireframe
void noFill(); 
void text(const char *text, float x, float y, float z);
void drawPoint(float x, float y, float z);
void drawLine(float x1, float y1, float z1, float x2, float y2, float z2);
// everything below uses fill() and noFill() to draw filled or wireframe
void drawRect(float x, float y, float z, float width, float height);
void drawPlane(float x, float y, float z, float width, float height, int subdivisions);
void drawCircle(float x, float y, float z, float radius);
void drawSphere(float x, float y, float z, float radius);
void drawTetrahedron(float scale);
void drawOctahedron(float scale);
void drawHexahedron(float scale);
void drawCube(float scale);
void drawIcosahedron(float scale);
void drawDodecahedron(float scale);
void drawUnitSquare(float x, float y, float z);
void drawUnitCircle(float x, float y, float z);
void drawUnitSphere(float x, float y, float z);
void drawUVSphereLines();
void drawPlatonicSolidFaces(char solidType);
void drawPlatonicSolidLines(char solidType);
void drawPlatonicSolidPoints(char solidType);
// combinations of shapes
void draw3DAxesLines(float x, float y, float z, float scale);
void drawCheckerboard(float walkX, float walkY, int numSquares);
void drawAxesGrid(float walkX, float walkY, float walkZ, int span, int repeats);
float modulusContext(float complete, int modulus);
float min(float one, float two);
float max(float one, float two);
// TEXTURES, SHADERS
GLuint loadTexture(const char *filename, int width, int height);
GLuint loadShader(char *vertex_path, char *fragment_path);
void setShaderUniform1f(GLuint shader, char *uniform, float value);
void setShaderUniformVec2f(GLuint shader, char *uniform, float *array);
void setShaderUniformVec3f(GLuint shader, char *uniform, float *array);
void setShaderUniformVec4f(GLuint shader, char *uniform, float *array);
void simpleLights();
void updateTime();
// preload for geometry primitives
void initPrimitives();
GLint _sphere_stacks = 20; //7;
GLint _sphere_slices = 30; //13;
static float _unit_circle_outline_vertices[192];
static float _unit_circle_outline_normals[192];
static float _unit_circle_outline_texCoord[192];
static float _unit_circle_fill_vertices[198]; // includes 1 more point: the center
static float _unit_circle_fill_normals[198];
static float _unit_circle_fill_texCoord[198];
float *_unit_sphere_vertices, *_unit_sphere_normals, *_unit_sphere_texture;
static float _invert_y_m[16] = {1,0,0,0,0,-1,0,0,0,0,1,0,0,0,0,1};
static unsigned char SHAPE_FILL = 1;
enum{ 
	SET_MOUSE_LOOK = 1 << 0,
	SET_KEYBOARD_MOVE = 1 << 1,
	SET_KEYBOARD_ZOOM = 1 << 2,
	SET_KEYBOARD_FUNCTIONS = 1 << 3,
	SET_SHOW_GROUND = 1 << 4,  // a 2D orientation grid
	SET_SHOW_GRID = 1 << 5    // a 3D orientation grid
};
enum { BIT_MOUSE_LOOK, BIT_KEYBOARD_MOVE, BIT_KEYBOARD_ZOOM, BIT_KEYBOARD_FUNCTIONS, BIT_SHOW_GROUND, BIT_SHOW_GRID };

#define ESCAPE_KEY 27
#define SPACE_BAR 32
#define RETURN_KEY 13
#define DELETE_KEY 127
#define EQUAL_KEY 61
#define PLUS_KEY 43
#define MINUS_KEY 45
#define UNDERBAR_KEY 95
#define PERIOD_KEY 46
#define GREATER_THAN_KEY 62
#define COMMA_KEY 44
#define LESS_THAN_KEY 60
// special key codes conflict with 0-127 ASCII codes, augmented them to 128-255 index range
#define UP_KEY GLUT_KEY_UP+128//229
#define DOWN_KEY GLUT_KEY_DOWN+128//231
#define RIGHT_KEY GLUT_KEY_RIGHT+128//230
#define LEFT_KEY GLUT_KEY_LEFT+128//228

int main(int argc, char **argv){
	// initialize glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(10,10);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutCreateWindow(argv[0]);
	// tie this program's functions to glut
	glutDisplayFunc(display);
	glutReshapeFunc(reshapeWindow);
	glutMouseFunc(mouseButtons);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mousePassiveMotion);
	glutKeyboardUpFunc(keyboardUp);
	glutKeyboardFunc(keyboardDown);
	glutSpecialFunc(specialDown);
	glutSpecialUpFunc(specialUp);
	if(CONTINUOUS_REFRESH){ glutIdleFunc(updateWorld); }
	// setup this program
	WINDOW[0] = 0.02 * -WIDTH*0.5;
	WINDOW[1] = 0.02 * -HEIGHT*0.5;
	WINDOW[2] = 0.02 * WIDTH;
	WINDOW[3] = 0.02 * HEIGHT;
	ASPECT = WINDOW[2] / WINDOW[3];
	memset(keyboard,0,256);
	clock_gettime(CLOCK_MONOTONIC, &START);
	FRAME = 0;
	initPrimitives();
	time_t t;
	srand((unsigned) time(&t));
	typicalOpenGLSettings();
	updateWorld();  // update must be called before draw, including first draw call
	glutPostRedisplay();
	setup();  // user defined function
	// begin main loop
	glutMainLoop();
	return 0;
}
void typicalOpenGLSettings(){
	firstPersonPerspective();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_SMOOTH); // GL_FLAT
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(1);
}
void reshapeWindow(int windowWidth, int windowHeight){
	WIDTH = windowWidth;
	HEIGHT = windowHeight;
	ASPECT = (float)WIDTH / (float)HEIGHT;
	glViewport(0, 0, (GLsizei) WIDTH, (GLsizei) HEIGHT);
	// update orthographic frame with new aspect ratio
	float newW = WINDOW[3] * ASPECT;
	float dW = WINDOW[2] - newW;
	WINDOW[2] = newW;
	WINDOW[0] += dW * 0.5;
	rebuildProjection();
	updateWorld();
}
void rebuildProjection(){
	switch(PERSPECTIVE){
		case FPP:   firstPersonPerspective(); break;
		case POLAR: polarPerspective(); break;
		case ORTHO: orthoPerspective(WINDOW[0], WINDOW[1], WINDOW[2], WINDOW[3]); break;
	}
}
void toggleFullscreen(){
	if(!FULLSCREEN){ glutFullScreen(); }
	else{
		reshapeWindow(WIDTH, HEIGHT);
		glutPositionWindow(0,0);
	}
	FULLSCREEN = !FULLSCREEN;
}
void firstPersonPerspective(){
	PERSPECTIVE = FPP;
	float a = (float)min(WIDTH, HEIGHT) / max(WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(WIDTH < HEIGHT){ glFrustum(-FOV, FOV, -FOV/a, FOV/a, NEAR_CLIP, FAR_CLIP); }
	else              { glFrustum(-FOV/a, FOV/a, -FOV, FOV, NEAR_CLIP, FAR_CLIP); }
	// change POV
	glRotatef(-90-HORIZON[1], 1, 0, 0);
	glRotatef(90+HORIZON[0], 0, 0, 1);
	// for left handed, invert the Y
	if(!HANDED){ glMultMatrixf(_invert_y_m); }
	// raise POV 1.0 above the floor, 1.0 is an arbitrary value
	glTranslatef(0.0f, 0.0f, -EYE_HEIGHT);
	glMatrixMode(GL_MODELVIEW);
}
void polarPerspective(){
	PERSPECTIVE = POLAR;
	float a = (float)min(WIDTH, HEIGHT) / max(WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(WIDTH < HEIGHT){ glFrustum(-FOV, FOV, -FOV/a, FOV/a, NEAR_CLIP, FAR_CLIP); }
	else              { glFrustum(-FOV/a, FOV/a, -FOV, FOV, NEAR_CLIP, FAR_CLIP); }
	// change POV
	glTranslatef(0, 0, -HORIZON[2]);
	glRotatef(-90+HORIZON[1], 1, 0, 0);
	glRotatef(90+180+HORIZON[0], 0, 0, 1);
	// for left handed, invert the Y
	if(!HANDED){ glMultMatrixf(_invert_y_m); }
	glMatrixMode(GL_MODELVIEW);
}
void orthoPerspective(float x, float y, float width, float height){
	PERSPECTIVE = ORTHO;
	WINDOW[0] = x;
	WINDOW[1] = y;
	WINDOW[2] = width;
	WINDOW[3] = height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	switch(HANDED){
		case LEFT: glOrtho(x, width + x, height + y, y, -FAR_CLIP, FAR_CLIP); break;
		case RIGHT: glOrtho(x, width + x, y, height + y, -FAR_CLIP, FAR_CLIP); break;
	}
	glMatrixMode(GL_MODELVIEW);
}
void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		glPushMatrix();
			glColor4f(1.0, 1.0, 1.0, 1.0);
			if(SETTINGS & (1 << BIT_KEYBOARD_MOVE)){ glTranslatef(-ORIGIN[0], -ORIGIN[1], -ORIGIN[2]); }
			draw3D();
		glPopMatrix();
		// 3D REPEATED STRUCTURE
		if(SETTINGS & (1 << BIT_SHOW_GRID)){
			float newX = modulusContext(-ORIGIN[0], 5);
			float newY = modulusContext(-ORIGIN[1], 5);
			float newZ = modulusContext(-ORIGIN[2], 5);
			glPushMatrix();
				glTranslatef(newX, newY, newZ);
				drawAxesGrid(newX, newY, newZ, 5, 4);
			glPopMatrix();
		}
		// 2D REPEATED STRUCTURE
		if(SETTINGS & (1 << BIT_SHOW_GROUND)){
			float newX = modulusContext(-ORIGIN[0], 2);
			float newY = modulusContext(-ORIGIN[1], 2);
			glPushMatrix();
				glTranslatef(newX, newY, -ORIGIN[2]);
				drawCheckerboard(newX, newY, 8);
			glPopMatrix();
		}
	glPopMatrix();
	
	// TO ORTHOGRAPHIC
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	switch(HANDED){
		case LEFT: glOrtho(0, WIDTH, HEIGHT, 0, -100.0, 100.0); break;
		case RIGHT: glOrtho(0, WIDTH, 0, HEIGHT, -100.0, 100.0); break;
	}
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glColor4f(1.0, 1.0, 1.0, 1.0);
		draw2D();
	glPopMatrix();
	rebuildProjection();

	// bring back buffer to the front on vertical refresh, auto-calls glFlush
	glutSwapBuffers();
	// glFlush();
}
void updateWorld(){
	FRAME += 1;
	updateTime();
	clock_gettime(CLOCK_MONOTONIC, &CURRENT);
	ELAPSED = (CURRENT.tv_sec - START.tv_sec);
	ELAPSED += (CURRENT.tv_nsec - START.tv_nsec) / 1000000000.0;
	// keyboard input
	if(SETTINGS & (1 << BIT_KEYBOARD_MOVE)){
		moveOriginWithArrowKeys();
	}
	if(SETTINGS & (1 << BIT_KEYBOARD_ZOOM)){
		if(keyboard[MINUS_KEY]){
			switch(PERSPECTIVE){
				case FPP:
					FOV += 0.001; break;
				case POLAR:
					HORIZON[2] += ZOOM_SPEED; break;
				case ORTHO: {
					float dH = -ZOOM_SPEED;
					WINDOW[3] -= dH;
					WINDOW[1] += dH * 0.5;
					float newW = WINDOW[3] * ((float)WIDTH / (float)HEIGHT);
					float dW = WINDOW[2] - newW;
					WINDOW[2] = newW;
					WINDOW[0] += dW * 0.5;
					} break;
			}
			rebuildProjection();
		}
		if(keyboard[PLUS_KEY]){
			switch(PERSPECTIVE){
				case FPP:
					FOV -= 0.001; break;
				case POLAR:
					HORIZON[2] -= ZOOM_SPEED; break;
				case ORTHO:{
					float dH = ZOOM_SPEED;
					WINDOW[3] -= dH;
					WINDOW[1] += dH * 0.5;
					float newW = WINDOW[3] * ((float)WIDTH / (float)HEIGHT);
					float dW = WINDOW[2] - newW;
					WINDOW[2] = newW;
					WINDOW[0] += dW * 0.5;
					} break;
			}
			rebuildProjection();
		}
	}
	update();
	glutPostRedisplay();
}
////////////////////////////////////////
//////////       TIME       ////////////
////////////////////////////////////////
void updateTime(){
	// input is human-readable: March 1st is month:03 day:01
	time_t current; time(&current);
	// todo, get time zone
	struct tm GMT;  GMT = *gmtime(&current);
	YEAR = GMT.tm_year + 1900; // The number of years since 1900   
	MONTH = GMT.tm_mon + 1;    // range 0 to 11  
	DAY = GMT.tm_mday;         // range 1 to 31  
	HOUR = GMT.tm_hour;        // range 0 to 23  
	MINUTE = GMT.tm_min;       // range 0 to 59  
	SECOND = GMT.tm_sec;       // range 0 to 59  
	// int tm_isdst;           // daylight saving time     
}
double j2000Days(int year, int month, int day, int hour, int minute, int second){
	double wholePart = 367*year-floor(7*(year+floor((month+9)/12.0))/4.0)+floor(275*month/9.0)+day-730531.5;
	double fractionalPart = (hour + minute/60.0 + second/3600.0)/24.0;
	// return value units in days
	return (double)wholePart + fractionalPart;
}
double j2000Seconds(int year, int month, int day, int hour, int minute, int second){
	return j2000Days(year, month, day, hour, minute, second) * 86400.0;
}
double j2000Centuries(int year, int month, int day, int hour, int minute, int second){
	return j2000Days(year, month, day, hour, minute, second) / 36525.0;
}
double j2000DaysNow(){ return j2000Days(YEAR, MONTH, DAY, HOUR, MINUTE, SECOND); }
double j2000SecondsNow(){ return j2000Days(YEAR, MONTH, DAY, HOUR, MINUTE, SECOND) * 86400.0; }
double j2000CenturiesNow(){ return j2000Days(YEAR, MONTH, DAY, HOUR, MINUTE, SECOND) / 36525.0; }
///////////////////////////////////////
//////////      SHADERS      //////////
///////////////////////////////////////
char *readFile(char *filename){
	char *buffer = 0;
	long length;
	FILE *f = fopen(filename, "rb");
	if(f){
		fseek(f, 0, SEEK_END);
		length = ftell(f);
		fseek(f, 0, SEEK_SET);
		buffer = malloc(length + 1);
		if(buffer) fread(buffer, 1, length, f);
		fclose(f);
		buffer[length] = 0; // fixes occasional extra characters at end of buffer
	}
	return buffer;
}
#ifdef __glew_h__
GLuint loadShader(char *vertex_path, char *fragment_path) {
	GLenum err = glewInit();
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	char *vSource = readFile(vertex_path);
	char *fSource = readFile(fragment_path);
	GLint result = GL_FALSE;
	int logLength;
	// vertex
	glShaderSource(vertexShader, 1, (const char *const *)&vSource, NULL);
	glCompileShader(vertexShader);
	// Check vertex shader
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
	if(logLength){
		char errorLog[logLength];
		glGetShaderInfoLog(vertexShader, logLength, NULL, &errorLog[0]);
		printf("VERTEX SHADER COMPILE %s", &errorLog[0]);
	}
	// fragment
	glShaderSource(fragmentShader, 1, (const char *const *)&fSource, NULL);
	glCompileShader(fragmentShader);
	// Check fragment shader
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);
	if(logLength){
		char errorLog[logLength];
		glGetShaderInfoLog(fragmentShader, logLength, NULL, &errorLog[0]);
		printf("FRAGMENT SHADER COMPILE %s", &errorLog[0]);
	}
	free(vSource);
	free(fSource);
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
	if(logLength){
		char programError[logLength]; programError[0] = 0;
		glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
		printf("LINKER %s", &programError[0]);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return program;
}
void setShaderUniform1f(GLuint shader, char *uniform, float value){
	if(shader){
		glUseProgram(shader);
		GLint loc = glGetUniformLocation(shader, uniform);
		if(loc != -1) glUniform1f(loc, value);
		glUseProgram(0);
	}
}
void setShaderUniformVec2f(GLuint shader, char *uniform, float *array){
	if(shader){
		glUseProgram(shader);
		GLint loc = glGetUniformLocation(shader, uniform);
		if(loc != -1) glUniform2fv(loc, 1, &array[0]);
		glUseProgram(0);
	}
}
void setShaderUniformVec3f(GLuint shader, char *uniform, float *array){
	if(shader){
		glUseProgram(shader);
		GLint loc = glGetUniformLocation(shader, uniform);
		if(loc != -1) glUniform3fv(loc, 1, &array[0]);
		glUseProgram(0);
	}
}
void setShaderUniformVec4f(GLuint shader, char *uniform, float *array){
	if(shader){
		glUseProgram(shader);
		GLint loc = glGetUniformLocation(shader, uniform);
		if(loc != -1) glUniform4fv(loc, 1, &array[0]);
		glUseProgram(0);
	}
}
#endif
///////////////////////////////////////
//////////       INPUT       //////////
///////////////////////////////////////
void moveOriginWithArrowKeys(){
	// process input devices if in first person perspective mode
	// map movement direction to the direction the person is facing
	// float lookAzimuth = lookOrientation[0]/180.0*M_PI;
	float lookAzimuth = (HANDED) ? HORIZON[0]/180.0*M_PI : -HORIZON[0]/180.0*M_PI;
	if(PERSPECTIVE == POLAR){ lookAzimuth += M_PI; }
	float dOrigin[3] = {0.0f, 0.0f, 0.0f};
	if(keyboard[UP_KEY] || keyboard['W'] || keyboard['w']){
		switch(HANDED){
			case LEFT:
				dOrigin[0] -= WALK_INTERVAL * cosf(lookAzimuth);
				dOrigin[1] += WALK_INTERVAL * sinf(lookAzimuth);
				break;
			case RIGHT:
				dOrigin[0] += WALK_INTERVAL * cosf(lookAzimuth);
				dOrigin[1] -= WALK_INTERVAL * sinf(lookAzimuth);
			break;
		}
	}
	if(keyboard[DOWN_KEY] || keyboard['S'] || keyboard['s']){
		switch(HANDED){
			case LEFT:
		dOrigin[0] += WALK_INTERVAL * cosf(lookAzimuth);
		dOrigin[1] -= WALK_INTERVAL * sinf(lookAzimuth);
			break;
			case RIGHT:
		dOrigin[0] -= WALK_INTERVAL * cosf(lookAzimuth);
		dOrigin[1] += WALK_INTERVAL * sinf(lookAzimuth);
			break;
		}
	}
	if(keyboard[LEFT_KEY] || keyboard['A'] || keyboard['a']){
		dOrigin[0] -= WALK_INTERVAL * cosf(lookAzimuth+M_PI_2);
		dOrigin[1] += WALK_INTERVAL * sinf(lookAzimuth+M_PI_2);
	}
	if(keyboard[RIGHT_KEY] || keyboard['D'] || keyboard['d']){
		dOrigin[0] += WALK_INTERVAL * cosf(lookAzimuth+M_PI_2);
		dOrigin[1] -= WALK_INTERVAL * sinf(lookAzimuth+M_PI_2);
	}
	if(keyboard['Q'] || keyboard['q'])
		dOrigin[2] += WALK_INTERVAL;
	if(keyboard['Z'] || keyboard['z'])
		dOrigin[2] -= WALK_INTERVAL;
	switch(HANDED){
		case LEFT:
			ORIGIN[0] -= dOrigin[0];
			ORIGIN[1] -= dOrigin[1];
		break;
		case RIGHT:
			ORIGIN[0] += dOrigin[0];
			ORIGIN[1] += dOrigin[1];
			// ORIGIN[2] += dOrigin[2];
		break;
	}
	ORIGIN[2] += dOrigin[2];
}
void mouseUpdatePerspective(int dx, int dy){
	switch(PERSPECTIVE){
		case FPP:
			HORIZON[0] -= (dx * MOUSE_SENSITIVITY);
			HORIZON[1] += (dy * MOUSE_SENSITIVITY);
			// HORIZON[2] = 0.0;
			firstPersonPerspective();
		break;
		case POLAR:
			HORIZON[0] -= (dx * MOUSE_SENSITIVITY);
			HORIZON[1] -= (dy * MOUSE_SENSITIVITY);
			// HORIZON[2] = 0.0;
			polarPerspective();
			break;
		case ORTHO:
			WINDOW[0] += dx / (WIDTH / WINDOW[2]);
			// WINDOW[1] -= dy / (HEIGHT / WINDOW[3]);
			switch(HANDED){
				case LEFT: WINDOW[1] += dy / (HEIGHT / WINDOW[3]); break;
				case RIGHT: WINDOW[1] -= dy / (HEIGHT / WINDOW[3]); break;
			}
			orthoPerspective(WINDOW[0], WINDOW[1], WINDOW[2], WINDOW[3]);
			break;
	}
}
// when mouse button state changes
void mouseButtons(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON){
		if(!state){  // button down
			mouseX = x;
			switch(HANDED){
				case LEFT: mouseY = y; break;
				case RIGHT: mouseY = HEIGHT - y; break;
			}
			mouseDownStartX = mouseX;
			mouseDownStartY = mouseY;
			mouseDown(button);
		}
		else {  // button up
			mouseUp(button);
		}
	}
	else if(button == GLUT_MIDDLE_BUTTON){
		if(!state)  mouseDown(button);
		else        mouseUp(button);
	}
	else if(button == GLUT_RIGHT_BUTTON){
		if(!state)  mouseDown(button);
		else        mouseUp(button);
	}
}
// when mouse is dragging screen
void mouseMotion(int x, int y){
	int y_correct = y;
	switch(HANDED){
		case LEFT: y_correct = y; break;
		case RIGHT: y_correct = HEIGHT - y; break;
	}
	// change since last mouse event
	if(SETTINGS & (1 << BIT_MOUSE_LOOK)){
		switch(HANDED){
			case LEFT: mouseUpdatePerspective(mouseX - x, mouseY - y_correct); break;
			case RIGHT: mouseUpdatePerspective(mouseX - x, y_correct - mouseY); break;
		}
	}
	// update new state
	mouseX = x;
	mouseY = y_correct;
	mouseDownX = mouseDownStartX - x;
	mouseDownY = mouseDownStartY - y_correct;
	mouseMoved(mouseX, mouseY);
	glutPostRedisplay();
}
// when mouse is moving but no buttons are pressed
void mousePassiveMotion(int x, int y){
	mouseX = x;
	switch(HANDED){
		case LEFT: mouseY = y; break;
		case RIGHT: mouseY = HEIGHT - y; break;
	}
	mouseMoved(mouseX, mouseY);
}
void keyboardDown(unsigned char key, int x, int y){
	if(keyboard[key] == 1){ return; }  // prevent repeated keyboard calls
	keyboard[key] = 1;
	if(SETTINGS & (1 << BIT_KEYBOARD_FUNCTIONS)){
		if(key == ESCAPE_KEY){ exit (0); }
		else if(key == 'F' || key == 'f'){
			toggleFullscreen();
		}
		else if(key == 'P' || key == 'p'){
			PERSPECTIVE = (PERSPECTIVE+1)%3;
			rebuildProjection();
		}
		else if(key == '.'){
			FOV += 0.01;
			rebuildProjection();
		}
		else if(key == ','){
			FOV -= 0.01;
			rebuildProjection();
		}
		else if(key == 'G' || key == 'g'){
			SETTINGS ^= SET_SHOW_GROUND;
			glutPostRedisplay();
		}
		else if (key == 'X' || key == 'x'){
			SETTINGS ^= SET_SHOW_GRID;
			glutPostRedisplay();
		}
	}
	keyDown(key);
	if(!CONTINUOUS_REFRESH){
		keyboardSetIdleFunc(); // for efficient screen draw, trigger redraw if needed
	}
}
void keyboardUp(unsigned char key, int x, int y){
	if(keyboard[key] == 0){ return; }  // prevent repeated keyboard calls
	keyboard[key] = 0;
	keyUp(key);
	if(!CONTINUOUS_REFRESH)
		keyboardSetIdleFunc();  // for efficient screen draw, turn off redraw if needed
}
void specialDown(int key, int x, int y){
	key += 128;  // special keys get stored in the 128-255 index range
	if(keyboard[key] == 1){ return; }  // prevent repeated keyboard calls
	keyboard[key] = 1;
	keyDown(key);
	if(!CONTINUOUS_REFRESH)
		keyboardSetIdleFunc();
}
void specialUp(int key, int x, int y){
	key += 128;  // special keys get stored in the 128-255 index range
	if(keyboard[key] == 0){ return; }  // prevent repeated keyboard calls
	keyboard[key] = 0;
	keyUp(key);
	if(!CONTINUOUS_REFRESH)
		keyboardSetIdleFunc();
}
void keyboardSetIdleFunc(){
	// if any key is pressed, idle function is set to re-draw screen
	unsigned char keyDown = 0;
	for(int i = 0; i < 256; i++){
		if(keyboard[i] == 1){
			keyDown = 1;
			break;
		}
	}
	if(keyDown){
		glutIdleFunc(updateWorld);
	} else {
		glutIdleFunc(NULL);
	}
}
///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////        TINY OPENGL TOOLBOX         //////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void fill(){ SHAPE_FILL = 1; }
void noFill(){ SHAPE_FILL = 0; }
// void text(const char *text, float x, float y, void *font){
void text(const char *text, float x, float y, float z){
	// GLUT_BITMAP_8_BY_13
	// GLUT_BITMAP_9_BY_15
	// GLUT_BITMAP_TIMES_ROMAN_10
	// GLUT_BITMAP_TIMES_ROMAN_24
	// GLUT_BITMAP_HELVETICA_10
	// GLUT_BITMAP_HELVETICA_12
	// GLUT_BITMAP_HELVETICA_18
	const char *c;
	// glRasterPos2f(x, 24+y);
	glRasterPos3f(x, y, z);
	for (c = text; *c != '\0'; c++){
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
	}
} 
void drawPoint(float x, float y, float z){
	GLfloat _point_vertex[] = { x, y, z };
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _point_vertex);
	glDrawArrays(GL_POINTS, 0, 1);
	glDisableClientState(GL_VERTEX_ARRAY);
}
void drawLine(float x1, float y1, float z1, float x2, float y2, float z2){
	GLfloat _lines_vertices[6] = {x1, y1, z1, x2, y2, z2};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _lines_vertices);
	glDrawArrays(GL_LINES, 0, 2);
	glDisableClientState(GL_VERTEX_ARRAY);
}
void drawUnitOriginSquareFill(){
	static const GLfloat _unit_square_vertex[] = {
		0.0f, 1.0f, 0.0f,     1.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f };
	static const GLfloat _unit_square_normals[] = {
		0.0f, 0.0f, 1.0f,     0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f };
	static const GLfloat _texture_coordinates[] = {0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);  
	glVertexPointer(3, GL_FLOAT, 0, _unit_square_vertex);
	glNormalPointer(GL_FLOAT, 0, _unit_square_normals);
	glTexCoordPointer(2, GL_FLOAT, 0, _texture_coordinates);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
void drawUnitOriginSquareWireframe(){
	static const GLfloat _unit_square_wireframe_vertex[] = {
		0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,    0.0f, 0.0f, 0.0f };
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _unit_square_wireframe_vertex);
	glDrawArrays(GL_LINES, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
}
void drawUnitSquare(float x, float y, float z){
	glPushMatrix();
		glTranslatef(x, y, z);
		switch(SHAPE_FILL){
			case 0: drawUnitOriginSquareWireframe(); break;
			default: drawUnitOriginSquareFill(); break;
		}
	glPopMatrix();
}
void drawRect(float x, float y, float z, float width, float height){
	glPushMatrix();
		glTranslatef(x, y, z);
		glScalef(width, height, 1.0);
		switch(SHAPE_FILL){
			case 0: drawUnitOriginSquareWireframe(); break;
			default: drawUnitOriginSquareFill(); break;
		}
	glPopMatrix();
}
void drawUnitPlaneWireframe(int subdivisions){
	GLfloat _plane_vertices[ (subdivisions+2) * 12 ];
	memset(_plane_vertices, 0, sizeof(_plane_vertices));
	for(int i = 0; i <= subdivisions+1; i++){
		float step = (float)i/subdivisions;
		_plane_vertices[ i * 12 + 0] = _plane_vertices[ i * 12 + 3] = _plane_vertices[ i * 12 + 7] = _plane_vertices[ i * 12 + 10] = step;
		_plane_vertices[ i * 12 + 4] = _plane_vertices[ i * 12 + 9] = 1.0;
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _plane_vertices);
	glDrawArrays(GL_LINES, 0, (subdivisions+1)*4);
	glDisableClientState(GL_VERTEX_ARRAY);
}
void drawUnitOriginPlane(int subdivisions){
	switch(SHAPE_FILL){
		case 0: drawUnitPlaneWireframe(subdivisions); break;
		default: drawUnitOriginSquareFill(); break;
	}
}
void drawPlane(float x, float y, float z, float width, float height, int subdivisions){
	glPushMatrix();
		glTranslatef(x, y, z);
		glScalef(width, height, 1.0);
		switch(SHAPE_FILL){
			case 0: drawUnitPlaneWireframe(subdivisions); break;
			default: drawUnitOriginSquareFill(); break;
		}
	glPopMatrix();
}
void drawUnitOriginSphereFill(){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);  
	glVertexPointer(3, GL_FLOAT, 0, _unit_sphere_vertices);
	glNormalPointer(GL_FLOAT, 0, _unit_sphere_normals);
	glTexCoordPointer(2, GL_FLOAT, 0, _unit_sphere_texture);
	// glDrawArrays(GL_LINE_LOOP, 0, _sphere_slices * _sphere_stacks * 2 );//(_sphere_slices+1) * 2 * (_sphere_stacks-1)+2  );
	glDrawArrays(GL_TRIANGLE_STRIP, 0,  _sphere_slices * _sphere_stacks * 2 );// (_sphere_slices+1) * 2 * (_sphere_stacks-1)+2  );
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
void drawUnitOriginSphereWireframe(int subdivisions){
	glPushMatrix();
		drawUnitCircle(0, 0, 0);  // equator
		// latitude
		for(float pos = 1.0/(subdivisions*0.5); pos < 1.0; pos += 1.0/(subdivisions*0.5)){
			glPushMatrix();
				float r = cosf(pos*M_PI*0.5);
				r = sqrt(1 - powf(pos,2));
				glScalef(r, r, 1.0);
				drawUnitCircle(0, 0, -pos);
				drawUnitCircle(0, 0, pos);
			glPopMatrix();
		}
		// longitude
		glRotatef(90, 0, 1, 0); drawUnitCircle(0, 0, 0);
		float angle = 180.0 / subdivisions;
		for(int pos = 0; pos < subdivisions-1; pos++){
			glRotatef(angle, 1, 0, 0); drawUnitCircle(0, 0, 0);
		}
	glPopMatrix();
}
void drawUnitSphere(float x, float y, float z){
	glPushMatrix();
		glTranslatef(x, y, z);
		switch(SHAPE_FILL){
			case 0: drawUnitOriginSphereWireframe(6); break;
			default: drawUnitOriginSphereFill(); break;
		}
	glPopMatrix();
}
void drawSphere(float x, float y, float z, float radius){
	glPushMatrix();
		glTranslatef(x, y, z);
		glScalef(radius, radius, radius);
		switch(SHAPE_FILL){
			case 0: drawUnitOriginSphereWireframe(6); break;
			default: drawUnitOriginSphereFill(); break;
		}
	glPopMatrix();
}
void drawUnitOriginCircleFill(){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);  
	glVertexPointer(3, GL_FLOAT, 0, _unit_circle_fill_vertices);
	glNormalPointer(GL_FLOAT, 0, _unit_circle_fill_normals);
	glTexCoordPointer(2, GL_FLOAT, 0, _unit_circle_fill_texCoord);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 66);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
void drawUnitOriginCircleWireframe(){
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _unit_circle_outline_vertices);
	glDrawArrays(GL_LINE_LOOP, 0, 64);
	glDisableClientState(GL_VERTEX_ARRAY);
}
void drawUnitOriginCircle(){
	switch(SHAPE_FILL){
		case 0: drawUnitOriginCircleWireframe(); break;
		default: drawUnitOriginCircleFill(); break;
	}
}
void drawUnitCircle(float x, float y, float z){
	glPushMatrix();
		glTranslatef(x, y, z);
		drawUnitOriginCircle();
	glPopMatrix();
}
void drawCircle(float x, float y, float z, float radius){
	glPushMatrix();
		glTranslatef(x, y, z);
		glScalef(radius, radius, 1.0);
		drawUnitOriginCircle();
	glPopMatrix();
}
void draw3DAxesLines(float x, float y, float z, float scale){
	static const GLfloat _axis_lines_vertices[] = {
		1.0f, 0.0f, 0.0f,    -1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,     0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,     0.0f, 0.0f, -1.0f};
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(scale, scale, scale);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _axis_lines_vertices);
	glDrawArrays(GL_LINES, 0, 6);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}
const float _tetrahedron_points[12] = {1.0,0.0,0.0,-0.3333,-0.9428,0.0,-0.3333,0.4714,0.81649,-0.3333,0.4714,-0.8164};
const unsigned short _tetrahedron_lines[12] = {2,3,2,0,2,1,3,0,3,1,0,1};
const unsigned short _tetrahedron_faces[12] = {2,1,3,2,3,0,2,0,1,3,1,0};
const float _tetrahedron_dual_points[12] = {-1.0,0.0,0.0,0.3333,0.9428,0.0,0.3333,-0.4714,0.81649,0.3333,-0.4714,-0.81649};
const unsigned short _tetrahedron_dual_lines[12] = {2,3,2,0,2,1,3,0,3,1,0,1};
const unsigned short _tetrahedron_dual_faces[12] = {2,1,3,2,3,0,2,0,1,3,1,0};
const float _octahedron_points[18] = {1.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,1.0,-1.0,0.0,0.0,0.0,-1.0,0.0,0.0,0.0,-1.0};
const unsigned short _octahedron_lines[24] = {1,0,1,2,1,5,1,3,3,2,2,0,0,5,5,3,4,2,4,3,4,5,4,0};
const unsigned short _octahedron_faces[24] = {1,0,2,1,5,0,4,0,5,4,2,0,1,2,3,1,3,5,4,5,3,4,3,2};
const float _hexahedron_points[24] = {0.57735,0.57735,0.57735,0.57735,0.57735,-0.57735,0.57735,-0.57735,-0.57735,0.57735,-0.57735,0.57735,-0.57735,0.57735,0.57735,-0.57735,0.57735,-0.57735,-0.57735,-0.57735,-0.57735,-0.57735,-0.57735,0.57735};
const unsigned short _hexahedron_lines[24] = {0,1,1,2,2,3,3,0,0,4,1,5,2,6,3,7,4,5,5,6,6,7,7,4};
const unsigned short _hexahedron_faces[24] = {0,3,2,1,4,0,1,5,0,3,7,4,7,4,5,6,3,7,6,2,1,5,6,2};
const unsigned short _hexahedron_triangle_faces[36] = {0,2,3,2,0,1,4,1,0,1,4,5,0,3,7,7,4,0,7,5,4,5,7,6,3,6,7,6,3,2,1,5,6,6,2,1};
const float _icosahedron_points[36] = {0.44721,-0.2763,0.85065,-0.44721,0.2763,0.85065,-0.44721,0.2763,-0.85065,0.44721,-0.2763,-0.85065,-0.44721,-0.7236,0.52573,0.44721,0.7236,0.52573,0.44721,0.7236,-0.52573,-0.44721,-0.7236,-0.52573,0.44721,-0.8944,0.0,1.0,0.0,0.0,-0.44721,0.8944,0.0,-1.0,0.0,0.0};
const unsigned short _icosahedron_lines[60] = {0,8,0,9,0,1,0,4,0,5,8,3,8,9,8,7,8,4,9,3,9,6,9,5,7,4,7,3,7,2,7,11,2,10,2,11,2,3,2,6,10,11,10,5,10,6,10,1,11,1,11,4,4,1,5,1,5,6,6,3};
const unsigned short _icosahedron_faces[60] = {8,7,4,7,8,3,8,4,0,8,0,9,9,3,8,9,0,5,9,5,6,9,6,3,3,2,7,3,6,2,0,4,1,0,1,5,11,4,7,11,7,2,11,2,10,1,11,10,11,1,4,10,6,5,10,5,1,10,2,6};
const float _dodecahedron_points[60] = {-0.7946,0.4911,0.3568,-0.1875,0.7946,-0.5773,-0.7946,0.4911,-0.3568,-0.7946,-0.1875,-0.5773,0.1875,0.3035,-0.9341,0.1875,0.9822,0.0,0.1875,-0.7946,-0.5773,-0.1875,-0.3035,-0.9341,-0.1875,-0.9822,0.0,-0.7946,-0.6070,0.0,0.7946,-0.4911,-0.3568,0.1875,-0.7946,0.5773,-0.1875,-0.3035,0.9341,-0.7946,-0.1875,0.5773,0.7946,-0.4911,0.3568,-0.1875,0.7946,0.5773,0.1875,0.3035,0.9341,0.7946,0.1875,0.5773,0.7946,0.6070,0.0,0.7946,0.1875,-0.5773};
const unsigned short _dodecahedron_lines[60] = {19,18,18,17,17,14,14,10,10,19,14,11,11,8,8,6,6,10,19,4,4,1,1,5,5,18,9,3,3,7,7,6,8,9,13,9,3,2,2,0,0,13,12,11,12,13,1,2,5,15,15,0,15,16,16,17,16,12,4,7};
const unsigned short _dodecahedron_triangle_faces[108] = {5,2,1,15,0,5,2,5,0,9,2,13,2,0,13,3,2,9,10,17,19,18,19,17,14,17,10,19,1,4,6,9,8,1,18,5,11,14,8,18,1,19,8,9,11,10,8,14,8,10,6,6,7,9,9,7,3,13,12,9,12,11,9,18,15,5,17,15,18,15,17,16,11,12,14,14,12,17,17,12,16,12,13,16,13,0,16,0,15,16,7,2,3,2,7,1,1,7,4,4,7,19,19,7,10,6,10,7};
const unsigned int _platonic_num_vertices[6] = {4,6,8,12,20,4};
const unsigned int _platonic_num_lines[6] = {6,12,12,30,30,6};
const unsigned int _platonic_num_faces[6] = {4,8,12,20,36,4};//{4,8,6,20,12,4};
const float* _platonic_point_arrays[6] = {_tetrahedron_points,_octahedron_points,_hexahedron_points,_icosahedron_points,_dodecahedron_points,_tetrahedron_dual_points};
const unsigned short* _platonic_line_array[6] = {_tetrahedron_lines,_octahedron_lines,_hexahedron_lines,_icosahedron_lines,_dodecahedron_lines,_tetrahedron_dual_lines};
const unsigned short* _platonic_face_array[6] = {_tetrahedron_faces,_octahedron_faces,_hexahedron_triangle_faces,_icosahedron_faces,_dodecahedron_triangle_faces,_tetrahedron_dual_faces};
const int _platonic_dual_index[6] = { 5,2,1,4,3,0 };
void drawPlatonicSolidFaces(char solidType){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _platonic_point_arrays[solidType]);
	glNormalPointer(GL_FLOAT, 0, _platonic_point_arrays[ solidType ]);
	glDrawElements(GL_TRIANGLES, 3*_platonic_num_faces[solidType], GL_UNSIGNED_SHORT, _platonic_face_array[solidType]);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
void drawPlatonicSolidLines(char solidType){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _platonic_point_arrays[solidType]);
	glNormalPointer(GL_FLOAT, 0, _platonic_point_arrays[ solidType ]);
	glDrawElements(GL_LINES, 2*_platonic_num_lines[solidType], GL_UNSIGNED_SHORT, _platonic_line_array[solidType]);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
void drawPlatonicSolidPoints(char solidType){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _platonic_point_arrays[solidType]);
	glNormalPointer(GL_FLOAT, 0, _platonic_point_arrays[ solidType ]);
	glDrawArrays(GL_POINTS, 0, _platonic_num_vertices[solidType]);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
void drawTetrahedron(float scale){
	glPushMatrix();
	glScalef(scale, scale, scale);
	switch(SHAPE_FILL){
		case 0: drawPlatonicSolidLines(0); break;
		default: drawPlatonicSolidFaces(0); break;
	}
	glPopMatrix();
}
void drawOctahedron(float scale){
	glPushMatrix();
	glScalef(scale, scale, scale);
	switch(SHAPE_FILL){
		case 0: drawPlatonicSolidLines(1); break;
		default: drawPlatonicSolidFaces(1); break;
	}
	glPopMatrix();
}
void drawHexahedron(float scale){
	glPushMatrix();
	glScalef(scale, scale, scale);
	switch(SHAPE_FILL){
		case 0: drawPlatonicSolidLines(2); break;
		default: drawPlatonicSolidFaces(2); break;
	}
	glPopMatrix();
}
void drawCube(float scale){ drawHexahedron(scale); }
void drawIcosahedron(float scale){
	glPushMatrix();
	glScalef(scale, scale, scale);
	switch(SHAPE_FILL){
		case 0: drawPlatonicSolidLines(3); break;
		default: drawPlatonicSolidFaces(3); break;
	}
	glPopMatrix();
}
void drawDodecahedron(float scale){
	glPushMatrix();
	glScalef(scale, scale, scale);
	switch(SHAPE_FILL){
		case 0: drawPlatonicSolidLines(4); break;
		default: drawPlatonicSolidFaces(4); break;
	}
	glPopMatrix();
}
unsigned char* getTextureData(const char * filename, int width, int height){
	FILE * file;
	file = fopen(filename, "rb");
	if (file == NULL) return 0;
	unsigned char *data = (unsigned char *)malloc(width * height * 3);
	// unsigned char *data = (unsigned char *)malloc(width * height * 4);
	fread(data, width * height * 3, 1, file);
	// fread(data, width * height * 4, 1, file);
	fclose(file);
	for(int i = 0; i < width * height; i++){
		int index = i*3;
		unsigned char B,R;
		B = data[index];
		R = data[index+2];
		data[index] = R;
		data[index+2] = B;
	}
	return data;
}
GLuint loadTextureBGR(const char * filename, int width, int height){
	GLuint texture;
	unsigned char *data = getTextureData(filename, width, height);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_BGR, GL_UNSIGNED_BYTE, data);
	free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}
GLuint loadTexture(const char * filename, int width, int height){
	GLuint texture;
	unsigned char *data = getTextureData(filename, width, height);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	// glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	// gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}
GLuint loadTextureSmooth(const char * filename, int width, int height){
	GLuint texture;
	unsigned char * data = getTextureData(filename, width, height);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}
void initPrimitives(){
	static unsigned char _geometry_initialized = 0;
	if (!_geometry_initialized) {
		// CIRCLE
		for(int i = 0; i < 64; i++){
			_unit_circle_outline_vertices[i*3+0] = -sinf(M_PI*2/64.0f*i);
			_unit_circle_outline_vertices[i*3+1] = cosf(M_PI*2/64.0f*i);
			_unit_circle_outline_vertices[i*3+2] = 0.0f;
			_unit_circle_outline_normals[i*3+0] = _unit_circle_outline_normals[i*3+1] = 0.0;
			_unit_circle_outline_normals[i*3+2] = 1.0;
			_unit_circle_outline_texCoord[i*3+0] = -sinf(M_PI*2/64.0f*i)*0.5 + 0.5;
			_unit_circle_outline_texCoord[i*3+1] = cosf(M_PI*2/64.0f*i)*0.5 + 0.5;
		}
		_unit_circle_fill_vertices[0] = 0.0f;
		_unit_circle_fill_vertices[1] = 0.0f;
		_unit_circle_fill_vertices[2] = 0.0f;
		_unit_circle_fill_normals[0] = _unit_circle_fill_normals[1] = 0.0f;
		_unit_circle_fill_normals[2] = 1.0f;
		_unit_circle_fill_texCoord[0] = 0.0f;
		_unit_circle_fill_texCoord[1] = 0.0f;
		for(int i = 1; i <= 65; i++){
			_unit_circle_fill_vertices[i*3+0] = -sinf(M_PI*2/64.0f*(i-1));
			_unit_circle_fill_vertices[i*3+1] = cosf(M_PI*2/64.0f*(i-1));
			_unit_circle_fill_vertices[i*3+2] = 0.0f;
			_unit_circle_fill_normals[i*3+0] = _unit_circle_fill_normals[i*3+1] = 0.0f;
			_unit_circle_fill_normals[i*3+2] = 1.0f;
			_unit_circle_fill_texCoord[i*3+0] = -sinf(M_PI*2/64.0f*(i-1))*0.5 + 0.5f;
			_unit_circle_fill_texCoord[i*3+1] = cosf(M_PI*2/64.0f*(i-1))*0.5 + 0.5f;
		}
		// SPHERE
		GLfloat m_Scale = 1;
		GLfloat *vPtr = _unit_sphere_vertices = (GLfloat*)malloc(sizeof(GLfloat) * 3 * ((_sphere_slices*2+2) * (_sphere_stacks)));
		GLfloat *nPtr = _unit_sphere_normals = (GLfloat*)malloc(sizeof(GLfloat) * 3 * ((_sphere_slices*2+2) * (_sphere_stacks)));
		GLfloat *tPtr = _unit_sphere_texture = (GLfloat*)malloc(sizeof(GLfloat) * 2 * ((_sphere_slices*2+2) * (_sphere_stacks)));
		for(unsigned int phiIdx = 0; phiIdx < _sphere_stacks; phiIdx++){
			// Latitude
			//starts at -pi/2 goes to pi/2
			float phi0 = M_PI * ((float)(phiIdx+0) * (1.0/(float)(_sphere_stacks)) - 0.5);  // the first circle
			float phi1 = M_PI * ((float)(phiIdx+1) * (1.0/(float)(_sphere_stacks)) - 0.5);  // second one
			float cosPhi0 = cos(phi0);
			float sinPhi0 = sin(phi0);
			float cosPhi1 = cos(phi1);
			float sinPhi1 = sin(phi1);
			for(unsigned int thetaIdx = 0; thetaIdx < _sphere_slices; thetaIdx++){
				//longitude
				float theta = 2.0*M_PI * ((float)thetaIdx) * (1.0/(float)(_sphere_slices - 1));
				float cosTheta = cos(theta+M_PI*.5);
				float sinTheta = sin(theta+M_PI*.5);
				vPtr[0] = m_Scale*cosPhi0 * cosTheta;
				vPtr[1] = m_Scale*(cosPhi0 * sinTheta);
				vPtr[2] = -m_Scale*sinPhi0;
				vPtr[3] = m_Scale*cosPhi1 * cosTheta;
				vPtr[4] = m_Scale*(cosPhi1 * sinTheta);
				vPtr[5] = -m_Scale*sinPhi1;
				nPtr[0] = cosPhi0 * cosTheta;
				nPtr[1] = cosPhi0 * sinTheta;
				nPtr[2] = -sinPhi0;
				nPtr[3] = cosPhi1 * cosTheta;
				nPtr[4] = cosPhi1 * sinTheta;
				nPtr[5] = -sinPhi1;
				GLfloat texX = (float)thetaIdx * (1.0f/(float)(_sphere_slices-1));
				tPtr[0] = texX;
				tPtr[1] = (float)(phiIdx + 0) * (1.0f/(float)(_sphere_stacks));
				tPtr[2] = texX;
				tPtr[3] = (float)(phiIdx + 1) * (1.0f/(float)(_sphere_stacks));
				vPtr += 2*3;
				nPtr += 2*3;
				tPtr += 2*2;
			}
		}
		_geometry_initialized = 1;
	}
}
/////////////////////////    HELPFUL ORIENTATION    //////////////////////////
void simpleLights(){
	GLfloat red[] =   {1.0f, 0.2f, 0.0f, 0.0f};
	GLfloat green[] = {0.3f, 0.9f, 0.3f, 0.0f};
	GLfloat blue[] =  {0.0f, 0.2f, 1.0f, 0.0f};
	GLfloat light_position0[] = { 0.0, 100.0, 0.0, 1.0};
	GLfloat light_position1[] = { 87.0, -50.0, 0.0, 1.0};
	GLfloat light_position2[] = { -87.0, -50.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, red);
	glLightfv(GL_LIGHT0, GL_SPECULAR, red);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, green);
	glLightfv(GL_LIGHT1, GL_SPECULAR, green);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, blue);
	glLightfv(GL_LIGHT2, GL_SPECULAR, blue);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHTING);
}
void simpleGrayLights(){
	GLfloat red[] =   {1.0f, 1.0f, 1.0f, 0.0f};
	GLfloat green[] = {1.0f, 1.0f, 1.0f, 0.0f};
	GLfloat blue[] =  {1.0f, 1.0f, 1.0f, 0.0f};
	GLfloat light_position0[] = { 0.0, 100.0, 40.0, 1.0};
	GLfloat light_position1[] = { 87.0, -50.0, -40.0, 1.0};
	GLfloat light_position2[] = { -87.0, -50.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, red);
	glLightfv(GL_LIGHT0, GL_SPECULAR, red);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, green);
	glLightfv(GL_LIGHT1, GL_SPECULAR, green);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, blue);
	glLightfv(GL_LIGHT2, GL_SPECULAR, blue);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHTING);
}
void headsUpDisplay(int x, int y, int z){
	static char monthStrings[][10] = { "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER" };
	switch(PERSPECTIVE){
		case FPP:   text("First Person Perspective", x, y, z); break;
		case POLAR: text("Polar Perspective", x, y, z); break;
		case ORTHO: text("Orthographic Perspective", x, y, z); break;
	}
	char line1String[50], line2String[50], line3String[50];
	switch(PERSPECTIVE){
		case ORTHO:
		sprintf(line1String, "X:%.1f, Y:%.1f, W:%.1f, H:%.1f", WINDOW[0], WINDOW[1], WINDOW[2], WINDOW[3] );
		float mWorldX = mouseX/(float)WIDTH * WINDOW[2] + WINDOW[0];
		float mWorldY = mouseY/(float)HEIGHT * WINDOW[3] + WINDOW[1];
		sprintf(line2String, "MOUSE WORLD (%.2f, %.2f)", mWorldX, mWorldY);
		break;
		case FPP: case POLAR:
		sprintf(line1String, "LOOK AZ:%.2f, ALT:%.2f, ZOOM:%.2f", HORIZON[0], HORIZON[1], HORIZON[2]);
		sprintf(line2String, "ORIGIN X:%.2f, Y:%.2f, Z:%.2f", ORIGIN[0], ORIGIN[1], ORIGIN[2]);		
		break;
	}
	char line4String[70];
	sprintf(line3String, "MOUSE SCREEN (%d, %d)", mouseX, mouseY );
	sprintf(line4String, "%d %s %d  %02d:%02d:%02d UTC", YEAR, monthStrings[(MONTH-1)%12], DAY, HOUR, MINUTE, SECOND);
	text(line1String, x, y+13*1, z);
	text(line2String, x, y+13*2, z);
	text(line3String, x, y+13*3, z);
	text(line4String, x, y+13*4, z);
}
void drawAxesLabels(float scale){
	text("+X", scale, 0, 0);  text("-X", -scale, 0, 0);
	text("+Y", 0, scale, 0);  text("-Y", 0, -scale, 0);
	text("+Z", 0, 0, scale);  text("-Z", 0, 0, -scale);
}
void drawAxesCoordinates(float scale){
	int scaleInt = scale;
	char string[50];
	sprintf(string, "(%d, 0, 0)", scaleInt);   text(string, scale, 0, 0);
	sprintf(string, "(0, %d, 0)", scaleInt);   text(string, 0, scale, 0);
	sprintf(string, "(0, 0, %d)", scaleInt);   text(string, 0, 0, scale);
	sprintf(string, "(%d, 0, 0)", -scaleInt);  text(string, -scale, 0, 0);
	sprintf(string, "(0, %d, 0)", -scaleInt);  text(string, 0, -scale, 0);
	sprintf(string, "(0, 0, %d)", -scaleInt);  text(string, 0, 0, -scale);
}
void drawCheckerboard(float walkX, float walkY, int numSquares){
	static GLfloat mat_white[] = { 1.0, 1.0, 1.0, 1.0 };
	static GLfloat mat_black[] = { 0.0, 0.0, 0.0, 1.0 };
	int XOffset = ceil(walkX);
	int YOffset = ceil(walkY);
	int evenOdd = (numSquares%2);
	if(evenOdd) 
		numSquares--;
	for(int i = -numSquares*.5; i < numSquares*.5; i++){
		for(int j = -numSquares*.5; j < numSquares*.5; j++){
			int b = abs(((i+j+XOffset+YOffset)%2));
			if(b) { glColor3f(1.0, 1.0, 1.0); glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_white); }
			else { glColor3f(0.0, 0.0, 0.0); glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_black); }
			drawUnitSquare(i-XOffset - evenOdd, j-YOffset - evenOdd, 0);
		}
	}
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_white);
}
// span: how many units to skip inbetween each axis
// repeats: how many rows/cols/stacks on either side of center
void drawAxesGrid(float walkX, float walkY, float walkZ, int span, int repeats){
	float XSpanMod = walkX - floor(walkX/span)*span;
	float YSpanMod = walkY - floor(walkY/span)*span;
	float ZSpanMod = walkZ - floor(walkZ/span)*span;
	for(int i = -repeats*span; i < repeats*span; i+=span){
		for(int j = -repeats*span; j < repeats*span; j+=span){
			for(int k = -repeats*span; k < repeats*span; k+=span){
				// distance approximation works just fine in this case
				float distance = fabs(i+XSpanMod-1) + fabs(j+YSpanMod-1) + abs(k);
				float brightness = 1.0 - distance/(repeats*span);
				GLfloat material[] = { 1.0, 1.0, 1.0, brightness };
				glColor4f(1.0, 1.0, 1.0, brightness);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, material);
				// glLineWidth(100.0/distance/distance);
				draw3DAxesLines(i + XSpanMod - walkX,
				                j + YSpanMod - walkY,
				                k + ZSpanMod - walkZ, 1.0);
			}
		}
	}
}
/////////////////////////        MATH         //////////////////////////
// ALGEBRA
#define D2R 0.01745329251994    // degrees to radians
#define R2D 57.295779513082321  // radians to degrees
float min(float one, float two){
	if(one > two) return two;
	return one;
}
float max(float one, float two){
	if(one < two) return two;
	return one;
}
float modulusContext(float complete, int modulus){
	double wholePart;
	double fracPart = modf(complete, &wholePart);
	return ( ((int)wholePart) % modulus ) + fracPart;
}
// MATRICES
unsigned char mat4Inverse(const float m[16], float inverse[16]){
	float inv[16], det;
	int i;
	inv[0] = m[5]*m[10]*m[15] - m[5]*m[11]*m[14] - m[9]*m[6]*m[15] + m[9]*m[7]*m[14] +m[13]*m[6]*m[11] - m[13]*m[7]*m[10];
	inv[4] = -m[4]*m[10]*m[15] + m[4]*m[11]*m[14] + m[8]*m[6]*m[15] - m[8]*m[7]*m[14] - m[12]*m[6]*m[11] + m[12]*m[7]*m[10];
	inv[8] = m[4]*m[9]*m[15] - m[4]*m[11]*m[13] - m[8]*m[5]*m[15] + m[8]*m[7]*m[13] + m[12]*m[5]*m[11] - m[12]*m[7]*m[9];
	inv[12] = -m[4]*m[9]*m[14] + m[4]*m[10]*m[13] + m[8]*m[5]*m[14] - m[8]*m[6]*m[13] - m[12]*m[5]*m[10] + m[12]*m[6]*m[9];
	inv[1] = -m[1]*m[10]*m[15] + m[1]*m[11]*m[14] + m[9]*m[2]*m[15] - m[9]*m[3]*m[14] - m[13]*m[2]*m[11] + m[13]*m[3]*m[10];
	inv[5] = m[0]*m[10]*m[15] - m[0]*m[11]*m[14] - m[8]*m[2]*m[15] + m[8]*m[3]*m[14] + m[12]*m[2]*m[11] - m[12]*m[3]*m[10];
	inv[9] = -m[0]*m[9]*m[15] + m[0]*m[11]*m[13] + m[8]*m[1]*m[15] - m[8]*m[3]*m[13] - m[12]*m[1]*m[11] + m[12]*m[3]*m[9];
	inv[13] = m[0]*m[9]*m[14] - m[0]*m[10]*m[13] - m[8]*m[1]*m[14] + m[8]*m[2]*m[13] + m[12]*m[1]*m[10] - m[12]*m[2]*m[9];
	inv[2] = m[1]*m[6]*m[15] - m[1]*m[7]*m[14] - m[5]*m[2]*m[15] + m[5]*m[3]*m[14] + m[13]*m[2]*m[7] - m[13]*m[3]*m[6];
	inv[6] = -m[0]*m[6]*m[15] + m[0]*m[7]*m[14] + m[4]*m[2]*m[15] - m[4]*m[3]*m[14] - m[12]*m[2]*m[7] + m[12]*m[3]*m[6];
	inv[10] = m[0]*m[5]*m[15] - m[0]*m[7]*m[13] - m[4]*m[1]*m[15] + m[4]*m[3]*m[13] + m[12]*m[1]*m[7] - m[12]*m[3]*m[5];
	inv[14] = -m[0]*m[5]*m[14] + m[0] *m[6]*m[13] + m[4]*m[1]*m[14] - m[4]*m[2]*m[13] - m[12]*m[1]*m[6] + m[12]*m[2]*m[5];
	inv[3] = -m[1]*m[6]*m[11] + m[1]*m[7]*m[10] + m[5]*m[2]*m[11] - m[5]*m[3]*m[10] - m[9]*m[2]*m[7] + m[9]*m[3]*m[6];
	inv[7] = m[0]*m[6]*m[11] - m[0]*m[7]*m[10] - m[4]*m[2]*m[11] + m[4]*m[3]*m[10] + m[8]*m[2]*m[7] - m[8]*m[3]*m[6];
	inv[11] = -m[0]*m[5]*m[11] + m[0]*m[7]*m[9] + m[4]*m[1]*m[11] - m[4]*m[3]*m[9] - m[8]*m[1]*m[7] + m[8]*m[3]*m[5];
	inv[15] = m[0]*m[5]*m[10] - m[0]*m[6]*m[9] - m[4]*m[1]*m[10] + m[4]*m[2]*m[9] + m[8]*m[1]*m[6] - m[8]*m[2]*m[5];
	det = m[0]*inv[0] + m[1]*inv[4] + m[2]*inv[8] + m[3]*inv[12];
	if (det == 0)
		return 0;
	det = 1.0 / det;
	for (i = 0; i < 16; i++)
		inverse[i] = inv[i]*det;
	return 1;
}
void mat4x4MultUnique(const float *a, const float *b, float *result){
	// this is counting on a or b != result   eg: cannot do mat4x4MultUnique(a, b, a);
	result[0] = a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12];
	result[1] = a[0] * b[1] + a[1] * b[5] + a[2] * b[9] + a[3] * b[13];
	result[2] = a[0] * b[2] + a[1] * b[6] + a[2] * b[10] + a[3] * b[14];
	result[3] = a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3] * b[15];
	result[4] = a[4] * b[0] + a[5] * b[4] + a[6] * b[8] + a[7] * b[12];
	result[5] = a[4] * b[1] + a[5] * b[5] + a[6] * b[9] + a[7] * b[13];
	result[6] = a[4] * b[2] + a[5] * b[6] + a[6] * b[10] + a[7] * b[14];
	result[7] = a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7] * b[15];
	result[8] = a[8] * b[0] + a[9] * b[4] + a[10] * b[8] + a[11] * b[12];
	result[9] = a[8] * b[1] + a[9] * b[5] + a[10] * b[9] + a[11] * b[13];
	result[10] = a[8] * b[2] + a[9] * b[6] + a[10] * b[10] + a[11] * b[14];
	result[11] = a[8] * b[3] + a[9] * b[7] + a[10] * b[11] + a[11] * b[15];
	result[12] = a[12] * b[0] + a[13] * b[4] + a[14] * b[8] + a[15] * b[12];
	result[13] = a[12] * b[1] + a[13] * b[5] + a[14] * b[9] + a[15] * b[13];
	result[14] = a[12] * b[2] + a[13] * b[6] + a[14] * b[10] + a[15] * b[14];
	result[15] = a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15];
}
void mat4x4Mult(const float *a, const float *b, float *result) {
	float c[16];
	mat4x4MultUnique(a, b, c);
	memcpy(result, c, sizeof(float)*16);
}
void mat3x3MultUnique(const float *a, const float *b, float *result){
	// this is counting on a or b != result   eg: cannot do mat3x3MultUnique(a, b, a);
	result[0] = a[0] * b[0] + a[1] * b[3] + a[2] * b[6];
	result[1] = a[0] * b[1] + a[1] * b[4] + a[2] * b[7];
	result[2] = a[0] * b[2] + a[1] * b[5] + a[2] * b[8];
	result[3] = a[3] * b[0] + a[4] * b[3] + a[5] * b[6];
	result[4] = a[3] * b[1] + a[4] * b[4] + a[5] * b[7];
	result[5] = a[3] * b[2] + a[4] * b[5] + a[5] * b[8];
	result[6] = a[6] * b[0] + a[7] * b[3] + a[8] * b[6];
	result[7] = a[6] * b[1] + a[7] * b[4] + a[8] * b[7];
	result[8] = a[6] * b[2] + a[7] * b[5] + a[8] * b[8];
}
void mat3x3Mult(const float *a, const float *b, float *result) {
	float c[9];
	mat3x3MultUnique(a, b, c);
	memcpy(result, c, sizeof(float)*9);
}
void mat3ToMat4(float *i, float *result){
	result[0] = i[0];   result[1] = i[1];   result[2] = i[2];   result[3] = 0.0f;
	result[4] = i[3];   result[5] = i[4];   result[6] = i[5];   result[7] = 0.0f;
	result[8] = i[6];   result[9] = i[7];   result[10] = i[8];  result[11] = 0.0f;
	result[12] = 0.0f;  result[13] = 0.0f;  result[14] = 0.0f;  result[15] = 1.0f;
}
void mat4Transpose(float *m) {
	float t[16];
	t[0] = m[0];   t[1] = m[4];   t[2] = m[8];   t[3] = m[12];
	t[4] = m[1];   t[5] = m[5];   t[6] = m[9];   t[7] = m[13];
	t[8] = m[2];   t[9] = m[6];   t[10] = m[10]; t[11] = m[14];
	t[12] = m[3];  t[13] = m[7];  t[14] = m[11]; t[15] = m[15];
	memcpy(m, t, sizeof(float)*16);
}
void mat3Transpose(float *m) {
	float t[9];
	t[0] = m[0];  t[1] = m[3];  t[2] = m[6];
	t[3] = m[1];  t[4] = m[4];  t[5] = m[7];
	t[6] = m[2];  t[7] = m[5];  t[8] = m[8];
	memcpy(m, t, sizeof(float)*9);
}
void makeMat3XRot(float *m, float angle){
	m[0] = 1;	m[1] = 0;			m[2] = 0;
	m[3] = 0;	m[4] = cos(angle);	m[5] = -sin(angle);
	m[6] = 0;	m[7] = sin(angle);	m[8] = cos(angle);
}
void makeMat3YRot(float *m, float angle){
	m[0] = cos(angle);	m[1] = 0;	m[2] = -sin(angle);
	m[3] = 0;			m[4] = 1;	m[5] = 0;
	m[6] = sin(angle);	m[7] = 0;	m[8] = cos(angle);
}
void makeMat3ZRot(float *m, float angle){
	m[0] = cos(angle);	m[1] = -sin(angle);	m[2] = 0;
	m[3] = sin(angle);	m[4] = cos(angle);	m[5] = 0;
	m[6] = 0;			m[7] = 0;			m[8] = 1;
}
void makeMat4XRot(float *m, float angle){
	m[0] = 1;	m[1] = 0;			m[2] = 0;			m[3] = 0;
	m[4] = 0;	m[5] = cos(angle);	m[6] = -sin(angle);	m[7] = 0;
	m[8] = 0;	m[9] = sin(angle);	m[10] = cos(angle);	m[11] = 0;
	m[12] = 0;	m[13] = 0;			m[14] = 0;			m[15] = 1;
}
void makeMat4YRot(float *m, float angle){
	m[0] = cos(angle);	m[1] = 0;	m[2] = -sin(angle);	m[3] = 0;
	m[4] = 0;			m[5] = 1;	m[6] = 0;			m[7] = 0;
	m[8] = sin(angle);	m[9] = 0;	m[10] = cos(angle);	m[11] = 0;
	m[12] = 0;			m[13] = 0;	m[14] = 0;			m[15] = 1;
}
void makeMat4ZRot(float *m, float angle){
	m[0] = cos(angle);	m[1] = -sin(angle);	m[2] = 0;	m[3] = 0;
	m[4] = sin(angle);	m[5] = cos(angle);	m[6] = 0;	m[7] = 0;
	m[8] = 0;			m[9] = 0;			m[10] = 1;	m[11] = 0;
	m[12] = 0;			m[13] = 0;			m[14] = 0;	m[15] = 1;
}
void setMat3FromMat4(float *m3, float *m4){
	m3[0] = m4[0]; m3[1] = m4[1]; m3[2] = m4[2];
	m3[3] = m4[4]; m3[4] = m4[5]; m3[5] = m4[6];
	m3[6] = m4[8]; m3[7] = m4[9]; m3[8] = m4[10];
}
void setMat4FromMat3(float *m4, float *m3){
	m4[0] = m3[0]; m4[1] = m3[1]; m4[2] = m3[2]; m4[3] = 0;
	m4[4] = m3[3]; m4[5] = m3[4]; m4[6] = m3[5]; m4[7] = 0;
	m4[8] = m3[6]; m4[9] = m3[7]; m4[10] = m3[8]; m4[11] = 0;
	m4[12] = 0; m4[13] = 0; m4[14] = 0; m4[15] = 1;
}
void setMat4Identity(float *m){
	m[0] = 1; m[1] = 0; m[2] = 0; m[3] = 0;
	m[4] = 0; m[5] = 1; m[6] = 0; m[7] = 0;
	m[8] = 0; m[9] = 0; m[10] = 1; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}
// MATRICES & VECTORS
void mat4Vec4Mult(const float m[16], const float v[4], float result[4]){
	result[0] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3] * v[3];
	result[1] = m[4] * v[0] + m[5] * v[1] + m[6] * v[2] + m[7] * v[3];
	result[2] = m[8] * v[0] + m[9] * v[1] + m[10] * v[2] + m[11] * v[3];
	result[3] = m[12] * v[0] + m[13] * v[1] + m[14] * v[2] + m[15] * v[3];
}
void mat3Vec3Mult(const float m[9], const float v[3], float result[3]){
	result[0] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2];
	result[1] = m[3] * v[0] + m[4] * v[1] + m[5] * v[2];
	result[2] = m[6] * v[0] + m[7] * v[1] + m[8] * v[2];
}
// VECTORS
void vec3Cross(const float u[3], const float v[3], float result[3]){
	result[0] = u[1]*v[2] - u[2]*v[1];
	result[1] = u[2]*v[0] - u[0]*v[2];
	result[2] = u[0]*v[1] - u[1]*v[0];
}
void vec3Normalize(float vec[3]){
	float m = sqrt( powf(vec[0],2) + powf(vec[1],2) + powf(vec[2],2) );
	vec[0] /= m;
	vec[1] /= m;
	vec[2] /= m;
}
#endif /* WORLD_FRAMEWORK */
