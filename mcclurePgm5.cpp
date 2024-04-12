// CS 445/545 Prog 5 for Colby McClure

// Requrired libraries for the program
#include <GL/glew.h>
#include <iostream>
#include <GL/freeglut.h> 
#include "OpenGL445Setup-jan24.h"
#include <cmath> 
#include <ctime>
using namespace std; 

/*****************************************************************************************

Author: Colby McClure
Program: CS 445 Program 5 
Date: 4/4/2024
Architecture Statement: 
*****************************************************************************************/

// To compile and link the code: g++ mcclurePgm5.cpp -o mcclurePgm5.exe -Wall -lGL -lGLU -lglut -lGLEW 
// In case WSL can't run executable: export MESA_GL_VERSION_OVERRIDE=4.5

// Global variables for the program

// This is my display function handler for the program

void UAH() {

	glColor3f(0.75, 0.75, 0.75); 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// 'U' portion 
	glTranslatef(-350, 0, -400);
	glutWireCube(50); 
	glTranslatef(0, -50, 0);
	glutWireCube(50);
	glTranslatef(0, -50, 0);
	glutWireCube(50);
	glTranslatef(0, -50, 0);
	glutWireCube(50);

	glTranslatef(50, 0, 0);
	glutWireCube(50);
	glTranslatef(50, 0, 0);
	glutWireCube(50);
	glTranslatef(50, 0, 0);
	glutWireCube(50);

	glTranslatef(0, 50, 0);
	glutWireCube(50);
	glTranslatef(0, 50, 0);
	glutWireCube(50);
	glTranslatef(0, 50, 0);
	glutWireCube(50);

	// 'A' portion

	glColor3f(0.0, 0.0, 1.0);
	glTranslatef(100, -150, 0);
	glutWireCube(50);
	glTranslatef(25, 50, 0);
	glutWireCube(50);
	glTranslatef(25, 50, 0);
	glutWireCube(50);
	glTranslatef(25, 50, 0);
	glutWireCube(50);

	glTranslatef(50, 0, 0);
	glutWireCube(50);
	glTranslatef(25, -50, 0);
	glutWireCube(50);
	glTranslatef(25, -50, 0);
	glutWireCube(50);
	glTranslatef(25, -50, 0);
	glutWireCube(50);
	
	glTranslatef(-75, 50, 0);
	glutWireCube(50);
	glTranslatef(-50, 0, 0);
	glutWireCube(50);
	

}

void display_func(void)
{
	// Set the clear color to black and clear the color buffer
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	UAH(); 

	// Swap the buffers
    glutSwapBuffers();
}

/**************************************************************************************/

// Set the canvas size to be 800 x 800
#define canvas_Width 800
#define canvas_Height 800

// Name the canvas 
char canvas_Name[] = "Colby McClure Fishtank";

// This is my driver function 
int main(int argc, char ** argv) {

	// Seed the random number generator so that its truly random each program run
	srand(static_cast<unsigned int>(std::time(nullptr)));

	// Initiate glut
	glutInit(&argc, argv);
	my_setup(canvas_Width, canvas_Height, canvas_Name);

	// Start the keyboard, display, and idle function handlers 
	glutDisplayFunc(display_func);
	glutMainLoop();
	return 0;
}