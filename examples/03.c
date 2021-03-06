// example 3
//
// demonstrates the correlation between
// the 2 coordinates spaces:
// - draw3D (in polar perspective mode)
// - draw2D (WIDTH x HEIGHT)

#include "../world.h"

int zoom = 0;
char* texts[4] = {"", "1/2 ", "1/4 ", "1/8 "};

void setup() {
	polarPerspective();
	noFill();
	HORIZON[0] = 180;
	HORIZON[1] = 0;
	HORIZON[2] = sqrt(2);
	SETTINGS = SET_MOUSE_LOOK | SET_SHOW_GRID;// | SET_KEYBOARD_FUNCTIONS;
}
void update() { }
void draw3D() {
	glColor3f(1.0, 1.0, 1.0);
	drawAxesLabels(1);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	draw3DAxesLines(0,0,0,1);
	glColor4f(0.33, 0.66, 1.0, 0.66);
	drawUnitOriginSphereWireframe(6);
}
void draw2D() {
	float minD = min(WIDTH, HEIGHT);
	float maxD = max(WIDTH, HEIGHT);

	glColor4f(1.0, 1.0, 1.0, 1.0);
	headsUpDisplay(0, HEIGHT-25, 0);
	text("spacebar to change zoom", WIDTH-23*8, 10, 0);

	char zoomString[50];
	sprintf(zoomString, "when camera is distance %.2f from origin", HORIZON[2]);
	text(zoomString, 0, 10, 0);

	char equationString[50];
	sprintf(equationString, "  (sqrt(1+4^%d) = %.2f)", zoom, HORIZON[2]);
	text(equationString, 0, 25, 0);

	char fillString[50];
	sprintf(fillString, "unit sphere fills %sscreen", texts[zoom]);   
	text(fillString, 0, 40, 0);

	glColor4f(0.0, 1.0, 0.0, 1.0);
	drawCircle(WIDTH*0.5, HEIGHT*0.5, 0, minD*powf(0.5,zoom+1) );
	glColor4f(1.0, 1.0, 1.0, 0.5);
	drawCircle(WIDTH*0.5, HEIGHT*0.5, 0, minD*0.5);
	drawCircle(WIDTH*0.5, HEIGHT*0.5, 0, minD*0.25);
	drawCircle(WIDTH*0.5, HEIGHT*0.5, 0, minD*0.125);
	drawCircle(WIDTH*0.5, HEIGHT*0.5, 0, minD*0.0625);
	glColor4f(1.0, 1.0, 1.0, 0.5);
	drawLine(0, 0, 0, WIDTH, HEIGHT, 0);
	drawLine(0, HEIGHT, 0, WIDTH, 0, 0);
}
void keyDown(unsigned int key) {
	switch(key){
		case ESCAPE_KEY: exit(0); break;
		case 'F': case 'f': toggleFullscreen(); break;
		case ' ':
			zoom = (zoom+1)%4;
			HORIZON[2] = sqrt( 1 + powf(4,zoom));
			break;
	}
}
void keyUp(unsigned int key) { }
void mouseDown(unsigned int button) { }
void mouseUp(unsigned int button) { }
void mouseMoved(int x, int y) { }