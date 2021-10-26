//Collaborator: Cristian Reynoso
#include "App.h"
#include <stdlib.h>
#include <deque>

static std::deque<Grid> myGrid;
static std::deque<Rect> coords; //filled with mouse interactable squares
static std::deque<Shape> placeHold(9); //makes 9 objects that will store either an X or O
int count; // keeps tracks of whether its going to be an X or O
bool AI = false;//initialize ai to false, unless spacebar is pressed/ toggled
bool win = false;//used in one instance to check win condition if met
bool print = false;//used to print out win statement if true


//white squares that hold clickable registered areas
Rect topLeft(-0.97, 0.97, 0.637, 0.637);
Rect topMiddle(-0.303, 0.97, 0.637, 0.637);
Rect topRight(0.363, 0.97, 0.607, 0.637);
Rect middleLeft(-0.97, 0.303, 0.637, 0.637);
Rect middleMiddle(-0.303, 0.303, 0.637, 0.637);
Rect middleRight(0.363, 0.303, 0.607, 0.637);
Rect bottomLeft(-0.97, -0.363, 0.637, 0.607);
Rect bottomMiddle(-0.303, -0.363, 0.637, 0.607);
Rect bottomRight(0.363, -0.363, 0.607, 0.607);

Grid myTopGrid(-1.0, 1.0, 2, 0.03);
Grid myLeftGrid(-1.0, 1.0, 0.03, 2);
Grid myBottomGrid(-1.0, -0.97, 2, 0.03);
Grid myRightGrid(0.97, 1, 0.03, 2);
Grid myTopHorizontalGrid(-1, 0.333, 2, 0.03);
Grid myBottomHorizontalGrid(-1, -0.333, 2, 0.03);
Grid myRightVerticalGrid(0.333, 1, 0.03, 2);
Grid myLeftVerticalGrid(-0.333, 1, 0.03, 2);
App::App(const char* label, int x, int y, int w, int h) : GlutApp(label, x, y, w, h) {
	// Initialize state variables
	mx = 0.0;
	my = 0.0;
	count = 0; 
	//use push back in order to 
	coords.push_back(topLeft);
	coords.push_back(topMiddle);
	coords.push_back(topRight);
	coords.push_back(middleLeft);
	coords.push_back(middleMiddle);
	coords.push_back(middleRight);
	coords.push_back(bottomLeft);
	coords.push_back(bottomMiddle);
	coords.push_back(bottomRight);
}
int turnNum(){//used to make random moves for the AI
	return rand() % 9; 
}
void wipeGame(){ //essentially restarts game
	for (int i = 0; i < placeHold.size(); i++) {
		coords.at(i).setContainsC(false);
		coords.at(i).setTaken(false);
		coords.at(i).setshapeValue(0);
		placeHold.at(i).setFilled(false);
		placeHold.at(i).setshapeValue(false);
		placeHold.at(i).setXY(0, 0);
		count = 0;
	}
}
int checkWinner(){//checks if theres is an alignment that creates a win
	if (coords.at(0).getShape() != 0 && coords.at(0).getShape() == coords.at(1).getShape() && coords.at(0).getShape() == coords.at(2).getShape())
		return coords.at(0).getShape();
	else if (coords.at(3).getShape() != 0 && coords.at(3).getShape() == coords.at(4).getShape() && coords.at(3).getShape() == coords.at(5).getShape())
		return coords.at(3).getShape();
	else if (coords.at(6).getShape() != 0 && coords.at(6).getShape() == coords.at(7).getShape() && coords.at(6).getShape() == coords.at(8).getShape())
		return coords.at(6).getShape();
	else if (coords.at(0).getShape() != 0 && coords.at(0).getShape() == coords.at(3).getShape() && coords.at(0).getShape() == coords.at(6).getShape())
		return coords.at(0).getShape();
	else if (coords.at(1).getShape() != 0 && coords.at(1).getShape() == coords.at(4).getShape() && coords.at(1).getShape() == coords.at(7).getShape())
		return coords.at(1).getShape();
	else if (coords.at(2).getShape() != 0 && coords.at(2).getShape() == coords.at(5).getShape() && coords.at(2).getShape() == coords.at(8).getShape())
		return coords.at(2).getShape();
	else if (coords.at(0).getShape() != 0 && coords.at(0).getShape() == coords.at(4).getShape() && coords.at(0).getShape() == coords.at(8).getShape())
		return coords.at(0).getShape();
	else if (coords.at(6).getShape() != 0 && coords.at(6).getShape() == coords.at(4).getShape() && coords.at(6).getShape() == coords.at(2).getShape())
		return coords.at(6).getShape();
	else
		return 0;
}
void App::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);//Background default to black
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Set Color to white
	glColor3d(1.0, 1.0, 1.0);
	for (int i = 0; i < placeHold.size(); i++) { //creates the shapes circle or x
		placeHold.at(i).draw();
	}
	int result = checkWinner();//result set to temp variable
	if(result == 1 || result == 2 || result == 9){
		win = true;
		if(print == false){
			if (result == 1) {
				std::cout << "O HAS WON!" << std::endl;
			}
			else if (result == 2) {
				std::cout << "X HAS WON!" << std::endl;
			}
			else if (count == 9) {
				std::cout << "It is a tie!" << std::endl;
			}
			print = true;
		}
	}
	//draws the cells
	topLeft.draw();
	topMiddle.draw();
	topRight.draw();
	middleLeft.draw();
	middleMiddle.draw();
	middleRight.draw();
	bottomLeft.draw();
	bottomMiddle.draw();
	bottomRight.draw();
	// Draw the tic tac toe grid
	myTopGrid.draw();
	myLeftGrid.draw();
	myBottomGrid.draw();
	myRightGrid.draw();
	myTopHorizontalGrid.draw();
	myBottomHorizontalGrid.draw();
	myLeftVerticalGrid.draw();
	myRightVerticalGrid.draw();

	glFlush();
	glutSwapBuffers();
}

void App::mouseDown(float x, float y) {
	mx = x;
	my = y;
	if(win == false)
	{
		for (int i = 0; i < coords.size(); i++) {//check if a cell contains the click coordinates
			coords.at(i).contains(mx, my);
			//std::cout << "getcontains gettaken: " <<coords.at(i).getContainsC() << coords.at(i).getTaken() << std::endl;
			if (AI == true && count % 2 == 1) {//handles that the AI does not choose a cell that is already taken
				for (int A = 0; count % 2 == 1; A++) {
					int random = turnNum(); //calls a random number from AI
					if (coords.at(random).getTaken() == false && count % 2 == 1) { //checks if the cell is taken
						coords.at(random).setContainsC(true);//artificially makes contains true to pass the if statement below
						i = random;
						break;
					}
				}
			}
			if (coords.at(i).getContainsC() == true && coords.at(i).getTaken() == false) {// makes sure it contains the cords but also makes sure the square isnt already taken
				for (int j = 0; j < placeHold.size(); j++) {
					if (placeHold.at(j).isFilled() == false) {//makes sure the same object isnt overwritten
						placeHold.at(j).setXY(coords.at(i).getX(), coords.at(i).getY());
						if (count % 2 == 0) { //makes the drawing a circle
							placeHold.at(j).setshapeValue(1);
							coords.at(i).setshapeValue(1);
							if (AI == true) {
								std::cout << "Click to continue." << std::endl;
							}
						}
						else {//makes the draw object an x
							placeHold.at(j).setshapeValue(2);
							coords.at(i).setshapeValue(2);
						}
						coords.at(i).setTaken(true);//sets taken to true so the same square wont produce more objects
						count++;
						break;
					}
				}
				break;
			}
		}
	}
	// Redraw the scene
	redraw();
}

void App::mouseDrag(float x, float y) {
	// Update app state
	mx = x;
	my = y;

	// Redraw the scene
	redraw();
}

void App::keyPress(unsigned char key) {
	if (key == 27) {
		// Exit the app when Esc key is pressed
		exit(0);
	}
	else if (key == 32) {//decimal value for Spacebar: swaps game modes
		if (AI == false) {
			AI = true;
			std::cout << "Against AI mode" << std::endl;
			wipeGame();
		}
		else if (AI == true) {
			AI = false;
			std::cout << "Player against player mode" << std::endl;
			wipeGame();
		}
	}
	redraw();
}
