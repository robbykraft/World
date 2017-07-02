// example 1
//
// shapes and fill() and noFill()

#include "../world.h"

void setup(){
	OPTIONS ^= SET_SHOW_GROUND | SET_SHOW_GRID | SET_KEYBOARD_MOVE;
	horizon[2] = 3.3;
	horizon[1] = 15;
	polarPerspective();
}
void update(){ }
void draw3D(){ 
	glPushMatrix();
		glTranslatef(-50, -50, -0.5);
		glScalef(100, 100, 100);
		glColor3f(0.6, 0.1, 0.3);
		drawUnitPlaneWireframe(100);
	glPopMatrix();

	float size1 = cosf(elapsed*0.5)*0.12 + 0.88;
	float size2 = -cosf(elapsed*0.5)*0.12 + 0.88;
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.5);
		glRotatef(elapsed*20, 1, 0, 0);
		glRotatef(elapsed*44, 0, 1, 0);
		glColor3f(0.0, 0.0, 0.0);
		glPushMatrix();
			glScalef(size1, size1, size1);
			drawDodecahedron();
		glPopMatrix();
		glPushMatrix();
			glScalef(size2, size2, size2);
			drawIcosahedron();
		glPopMatrix();
		noFill();
		glScalef(1.005, 1.005, 1.005);
		glColor3f(0.3, 0.5, 0.9);
		glPushMatrix();
			glScalef(size1, size1, size1);
			drawDodecahedron();
		glPopMatrix();
		glPushMatrix();
			glScalef(size2, size2, size2);
			drawIcosahedron();
		glPopMatrix();
		fill();
	glPopMatrix();
}
void draw2D(){ }
void keyDown(unsigned int key){ }
void keyUp(unsigned int key){ }
void mouseDown(unsigned int button){ }
void mouseUp(unsigned int button){ }
void mouseMoved(int x, int y){ }