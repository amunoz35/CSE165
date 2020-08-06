#ifndef MUSH_H
#define MUSH_H
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <fstream>


#define MUSHROOM_SIZE 0.075//size of mushroom in canvas
#define MUSH_IMAGE_WIDTH 400 //Size/width of mushroom 
#define MUSH_IMAGE_HEIGHT 400 //Size/height of mushroom 
#define FIRE_IMAGE_WIDTH 1024 //Size/width of fireball 
#define FIRE_IMAGE_HEIGHT 1024 //Size/height of fireball
#define FIRE_IMAGES_COL 6 //number of frames in a column
#define FIRE_IMAGES 36 //Total number of fireball frames
#define ANIMATION_TIME 500 //Sets the time of animation in milliseconds

using namespace std;
class pos2D {
public:
	float x, y;
	pos2D();
	pos2D(float xx, float yy);
};
class Mush {
private:
	bool destroyed;
	bool notdestroyed;
	pos2D position;
	GLuint texMush, texFire;
	double actualTime;
	int currentFrame;

public:
	Mush();
	void loadTexture();
	void setPosition(pos2D val);
	void display();
	bool intersect(pos2D val);
	bool isDestroyed();
	void startDestroying();
	void animate();
};
#endif 


