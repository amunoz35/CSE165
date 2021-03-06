//Collaborator: Marcus
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>       
#include <cmath>
#include "mush.h"

#define MUSH_NUM 2//sets the amount of mushrooms

int Width = 800, Height = 600;
Mushroom mushArr[MUSH_NUM];

void Resize(int w, int h) {
	Width = w;
	Height = h;
	
	glMatrixMode(GL_PROJECTION);// Use the Projection Matrix	
	glLoadIdentity();// Sets matrix to identity and resets	
	glViewport(0, 0, Width, Height);
	gluOrtho2D(0, 1, 0, 1);// Sets to orthogonal matrix
	glMatrixMode(GL_MODELVIEW);// Resets to the model
}
void Mouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//Begins the "click"
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		//a full "click" has been done
		for (int i = 0; i < MUSH_NUM; ++i) {
			//Checks if the click intersected with a mushroom
			if (!mushArr[i].isDestroyed() && mushArr[i].intersect(pos2D(float(x)/ Width, 1.0f - float(y)/ Height))) {
				mushArr[i].startDestroying();//manage only one destruction at a time
				break; 
			}
		}
	}
}
//exit application with escape
void Key(unsigned char key, int x, int y){
	switch (key) {
	case 27:
		exit(0);
	}
}

void Draw() {
	//draw scene
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//draw every mushroom
	for (int i = 0; i < MUSH_NUM; ++i) {
		mushArr[i].display();
	}
	glutSwapBuffers();
}

void Idle() {
	glutPostRedisplay();
	//animate explosion of mushroom
	for (int i = 0; i < MUSH_NUM; ++i) {
		mushArr[i].animate();
	}
}

void Init() {
	srand(time(NULL));
	//init mushroom at random positions; pulled from stackoverflow
	for (int i = 0; i < MUSH_NUM;++i) {
		mushArr[i].setPosition(pos2D(rand() % 100 / 100.0f, rand() % 100 / 100.0f));
		mushArr[i].loadTexture();
	}
}

int main(int argc, char **argv) {
	//init opengl
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);//General display 
	glutInitWindowSize(Width, Height);//sets window size
	glutCreateWindow("Mushroom Exploder 5000");//makes window named "Mushroom Exploder 5000"
	//init variables
	Init();
	//function callbacks
	glutKeyboardFunc(Key);
	glutMouseFunc(Mouse);
	glutDisplayFunc(Draw);
	glutReshapeFunc(Resize);
	glutIdleFunc(Idle);
	glutMainLoop();//start application
	return 0;
}
