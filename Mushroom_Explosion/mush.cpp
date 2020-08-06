#include "mush.h"
//default constructor
Mush::Mush() {//Initialize the stated of the mushroom objects
	notdestroyed = false;
	destroyed = false;
}
//function to load textures
//converted files into "raw" to circumvent bitmap calls
void Mush::loadTexture() {
	{
		ifstream mushfile("mushroom.raw", ios::in | ios::binary);
		//Texture is size 400 by 400
		unsigned int size = MUSH_IMAGE_WIDTH * MUSH_IMAGE_HEIGHT * 3;
		char *data = new char[size];
		mushfile.read(data, size);

		glGenTextures(1, &texMush);
		glBindTexture(GL_TEXTURE_2D, texMush);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, MUSH_IMAGE_WIDTH, MUSH_IMAGE_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glBindTexture(GL_TEXTURE_2D, 0);
		delete[] data;
	}
	//read fireball
	{
		ifstream fireFile("fireball.raw", ios::in | ios::binary);
		//Texture is size 400 by 400
		unsigned int size = FIRE_IMAGE_WIDTH * FIRE_IMAGE_HEIGHT * 3;
		char *data = new char[size];
		fireFile.read(data, size);

		glGenTextures(1, &texFire);
		glBindTexture(GL_TEXTURE_2D, texFire);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, FIRE_IMAGE_WIDTH, FIRE_IMAGE_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glBindTexture(GL_TEXTURE_2D, 0);
		delete[] data;
	}
}
//set position of mushroom
void Mush::setPosition(pos2D val) {
	position.x = val.x;
	position.y = val.y;
}
//function to display the mushroom
void Mush::display() {
	glEnable(GL_TEXTURE_2D);
	if (!destroyed) {
		if (notdestroyed) {
			//display fire animation
			glBindTexture(GL_TEXTURE_2D, texFire);
			//calculate position in texture of the beginning of the frame
			float x = float(currentFrame % FIRE_IMAGES_COL) / FIRE_IMAGES_COL;
			float y = float(currentFrame / FIRE_IMAGES_COL) / FIRE_IMAGES_COL;
			//size of the frame
			float dt = 1.0 / FIRE_IMAGES_COL;
			glBegin(GL_QUADS);
			glTexCoord2d(x, y + dt);
			glVertex2f(position.x - MUSHROOM_SIZE, position.y - MUSHROOM_SIZE);
			glTexCoord2d(x + dt, y + dt);
			glVertex2f(position.x + MUSHROOM_SIZE, position.y - MUSHROOM_SIZE);
			glTexCoord2d(x + dt, y);
			glVertex2f(position.x + MUSHROOM_SIZE, position.y + MUSHROOM_SIZE);
			glTexCoord2d(x, y);
			glVertex2f(position.x - MUSHROOM_SIZE, position.y + MUSHROOM_SIZE);
			glEnd();
		}
		else {
			//displays the mushroom
			glBindTexture(GL_TEXTURE_2D, texMush);

			glBegin(GL_QUADS);
			glTexCoord2d(0, 1);
			glVertex2f(position.x - MUSHROOM_SIZE, position.y - MUSHROOM_SIZE);
			glTexCoord2d(1, 1);
			glVertex2f(position.x + MUSHROOM_SIZE, position.y - MUSHROOM_SIZE);
			glTexCoord2d(1, 0);
			glVertex2f(position.x + MUSHROOM_SIZE, position.y + MUSHROOM_SIZE);
			glTexCoord2d(0, 0);
			glVertex2f(position.x - MUSHROOM_SIZE, position.y + MUSHROOM_SIZE);
			glEnd();
		}
	}
}
//Checks if a point is within the mushroom
bool Mush::intersect(pos2D val) {
	return (position.x - MUSHROOM_SIZE < val.x && val.x < position.x + MUSHROOM_SIZE) && (position.y - MUSHROOM_SIZE < val.y && val.y < position.y + MUSHROOM_SIZE);
}
//check if mushroom is destroyed
bool Mush::isDestroyed() {
	return destroyed || notdestroyed;
}

//function to set the mushroom to notdestroyed mode
void Mush::startnotdestroyed() {
	notdestroyed = true;
	actualTime = glutGet(GLUT_ELAPSED_TIME);
	currentFrame = 0;
}

//function that animates the destruction
void Mush::animate() {
	//only animate if notdestroyed
	if (notdestroyed) {
		//get current time and get how much has passed since start of animation
		double current = glutGet(GLUT_ELAPSED_TIME);
		double dt = current - actualTime;
		//get frame from elapsed time
		currentFrame = int(FIRE_IMAGES * dt / ANIMATION_TIME);
		//Checks the amount of frames past and stops the animation if done
		if (FIRE_IMAGES <= currentFrame) {
			destroyed = true;
			notdestroyed = false;
		}
	}
}

pos2D::pos2D() {
	x = 0;
	y = 0;
}
pos2D::pos2D(float xx, float yy) {
	x = xx;
	y = yy;
}