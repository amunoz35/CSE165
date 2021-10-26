//Collaborator: Cristian Reynoso
#ifndef App_hpp
#define App_hpp
#include <deque>
#include "GlutApp.h"
#include <math.h>

class Rect{//mostly recycled from rect lab
public:
	float x, y, width, height;
	bool containsC;
	bool taken;
	int shapeValue; //checks the value of the shape
public:
	Rect(){
		x = 0.0f;
		y = 0.0f;
		width = 0.0f;
		height = 0.0f;
		containsC = false;
		taken = false;
		shapeValue = 0;
	}
	Rect(float xx, float yy, float w, float h) {
		x = xx;
		y = yy;
		width = w;
		height = h;
	}
	float getY() const{
		return y;
	}
	float getX() const{
		return x;
	}
	float getWidth() const{
		return width;
	}
	float getHeight() const{
		return height;
	}
	void setshapeValue(int shape){
		shapeValue = shape;
	}
	int getShape() const{
		return shapeValue;
	}
	bool getContainsC() const{
		return containsC;
	}
	void setContainsC(bool cont){
		containsC = cont;
	}
	void setTaken(bool take){
		taken = take;
	}
	bool getTaken(){
		return taken;
	}
	void setX(float xx){
		x = xx;
	}
	void setY(float yy){
		y = yy;
	}
	bool contains(float x, float y){ //checks whether a square was clicked
		if (x >= this->x && this->x + this->width >= x) {
			if (y <= this->y && y >= this->y - this->height) {
				containsC = true;
			}
		}
		else
			containsC = false;
	}
	void draw() { //makes cell squares used
		glColor3d(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2f(getX(), getY());
		glVertex2f(getX() + getWidth(), getY());
		glVertex2f(getX() + getWidth(), getY() - getHeight());
		glVertex2f(getX(), getY() - getHeight());
		glEnd();
	}
};

class App : public GlutApp {
	float mx;
	float my;
public:
	App(const char* label, int x, int y, int w, int h);

	void draw();
	void keyPress(unsigned char key);
	void mouseDown(float x, float y);
	void mouseDrag(float x, float y);
};


class Grid{
public:
	float x;
	float y; 
	float width;
	float height;
public:

	Grid(){//initialize values to float without typecasting
		x = 0.0f;
		y = 0.0f;
		width = 0.0f;
		height = 0.0f;
	}
	Grid(float xx, float yy, float w, float h) {//sets local variables equal to the "global variables"
		x = xx;
		y = yy;
		width = w;
		height = h;
	}
	//getters for 
	float getY() const{
		return y;
	}
	float getX() const{
		return x;
	}
	float getW() const{
		return width;
	}
	float getH() const{
		return height;
	}
	void draw() { 
		glColor3d(1.0, 1.0, 1.0);
		glBegin(GL_POLYGON);

		glVertex2f(getX(), getY());
		glVertex2f(getX() + getW(), getY());
		glVertex2f(getX() + getW(), getY() - getH());
		glVertex2f(getX(), getY() - getH());
		glEnd();
	}
};
class Shape{
public:
	float x, y, radius;
	int resolution;
	bool filled;//stops this object from getting overwritten
	int shapeValue; //0 is NULL, 1 = O, 2 = X
public:
	Shape(){
		x = 0.0f;
		y = 0.0f;
		filled = false;
	}
	Shape(float xx, float yy) {
		x = xx;
		y = yy;
	}
	void setXY(float xx, float yy){
		x = xx;
		y = yy;
		resolution = 150;
		radius = 0.20;
		shapeValue = 0;
		if (xx != 0 && yy != 0)
			filled = true; //mark filled as true
	}
	float getY() const{
		return y;
	}
	float getX() const{
		return x;
	}
	float getRadius() const{
		return radius;
	}
	float getCenterX() const{ //centers the drawing for x value
		if (x < -0.310)
			return (-0.66);
		else if (x > 0.310)
			return (0.66);
		else
			return 0;
	}
	float getCenterY() const{ //centers the drawing for y value
		if (y < -0.310)
			return (-0.66);
		else if (y > 0.310)
			return (0.66);
		else
			return 0;
	}
	void setshapeValue(int shape){ // sets the shape if 1 circle if 2 x
		shapeValue = shape;
	}
	int getShape() const{
		return shapeValue;
	}
	bool isFilled(){
		return filled;
	}
	void setFilled(bool fill){
		filled = fill;
	}
	void draw(){//draws a circle if 1 and draws an X if 2
		if (shapeValue == 1) {//sets shapeValue to create an O
			glColor3d(1.0, 0.0, 0.0);
			glPointSize(15);
			glBegin(GL_POINTS);
			for (int i = -resolution; i < resolution; i++) {
				float angle = (i) * (360 / resolution);
				float degree = (angle * 3.1415 / 180);
				float circleX = getCenterX() + getRadius() * cos(degree);
				float circleY = getCenterY() + getRadius() * sin(degree);
				glVertex2f(circleX, circleY);
			}
			filled = true;
			glEnd();
		}
		else if (shapeValue == 2) {//shapeValue will create an X
			float tempy = y - 0.066;
			float tempx = x + 0.066;
			glBegin(GL_POLYGON);  
			glVertex2f(tempx + 0.10, tempy);
			glVertex2f(tempx, tempy);
			glVertex2f(tempx + 0.40, tempy - 0.50);
			glVertex2f(tempx + 0.50, tempy - 0.50);
			glEnd();

			glBegin(GL_POLYGON); 
			glVertex2f(tempx + 0.10, tempy - 0.50);
			glVertex2f(tempx, tempy - 0.50);
			glVertex2f(tempx + 0.40, tempy);
			glVertex2f(tempx + 0.50, tempy);
			glEnd();
		}
	}
};

#endif
