// CS 445/545 Prog 5 for Colby McClure

// Requrired libraries for the program
#include <GL/glew.h>
#include <iostream>
#include <GL/freeglut.h> 
#include "OpenGL445Setup-jan24.h"
using namespace std; 

/*****************************************************************************************

Author: Colby McClure
Program: CS 445 Program 5 
Date: 4/4/2024
Architecture Statement: Fairly straightforward program this time around. To start off,
I have a timer function handler, 'rotateUAH' that is in charge of rotating the UAH logo.
The rotation variable is incremented by 4 each time the handler is called, and if the
rotation reaches 360, it is reset to 0, thus completing a full rotation. This timer 
function handler does not get triggered by anything else, just the glut main loop.
As for how I went about drawing my UAH logo, I used the glutSolidCube and glutWireCube 
functions to draw the letters of the logo, all in my 'drawUAH' function. I also used 
the glutSolidSphere function to draw the sphere inside the 'A'. When drawing the 
letters. Rather than draw them separately, I decided to draw them all in one go. I 
did this by translating the modelview matrix to the correct position, drawing the 
letter, and then translating the matrix to the next position. I did this primarily 
to make it easier to rotate everything, since all the letters are supposed to rotate at 
the same rate and speed. To figure out how to rotate about the spindle, I went with the
3-step solution. First, I translated the matrix to the origin, then rotated the matrix by
the correct axis, and then translated the matrix back to the correct position. This 
allowed me to rotate the UAH logo about the spindle. This strategy allowed me to spin the
UAH logo by the tip of the spindle, located in the 'drawSpindle' function. I chose to call
the timer function handler every 15ms because that was the closest I could get to 2 seconds 
per full rotation. As for lighting and materials, I created the light and initialized all 
material properties for each object in the 'drawUAH' function. I used the same material 
properties for the 'U' and 'H' portions of the logo, and then used different material 
properties for the 'A' and the sphere inside the 'A'.The values chosen for the material 
properties were based on the colors of the UAH logo and what I think their shininess 
should be. My light is a white light that is positioned at the origin. Lastly, I am aware
of the issue of one side being lit versus the other side being dark. I know that
GL_DEPTH in the glutInitDisplayMode function would fix this, but I was unable to get it to
work and show my objects. Due to time constraints, that is going to remain how it is. 

*****************************************************************************************/

// To compile and link the code: g++ mcclurePgm5.cpp -o mcclurePgm5.exe -Wall -lGL -lGLU -lglut -lGLEW 
// In case WSL can't run executable: export MESA_GL_VERSION_OVERRIDE=4.5

// Global variable for the rotation of the UAH logo
int rotate = 0;

// Initialize the light properties along with the material properties for each object
GLfloat light_position[] = {0.0, 0.0, 0.0, 1.0};
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_ambient[] = {0.25, 0.25, 0.25, 0.25};
GLfloat light_diffuse[] = {0.75, 0.75, 0.75, 1.0};

GLfloat uh_specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat uh_ambient[] = {0.75, 0.75, 0.75, 1.0};
GLfloat uh_diffuse[] = {0.75, 0.75, 0.75, 1.0};
GLfloat uh_shiny[] = {60.0};

GLfloat a_specular[] = {1.0, 1.0, 1.0, 0.8};
GLfloat a_ambient[] = {0.0, 0.0, 1.0, 1.0};
GLfloat a_diffuse[] = {0.0, 0.0, 1.0, 1.0};
GLfloat a_shininess[] = {60.0};

GLfloat ball_specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat ball_ambient[] = {0.8, 0.4, 0.1, 1.0};
GLfloat ball_diffuse[] = {0.8, 0.4, 0.1, 1.0};
GLfloat ball_shininess[] = {30.0}; 

// This timer function handler increment the rotation variable, thus rotating the UAH logo
void rotateUAH(int value) {

	// If the rotation is 360, reset it to 0, otherwise increment it by 4
	if(rotate == 360) {
		rotate = 0;
	} else {
		rotate += 4;
	}

	// Refresh the display and call the timer handler again
	glutPostRedisplay();
	glutTimerFunc(15, rotateUAH, 0);
}

/**************************************************************************************/

// This function is for drawing the spindle of the UAH logo (hardcoded position)
void drawSpindle() {
	
	glLoadIdentity(); 
	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_TRIANGLES);
	glVertex3f(0, 0, -400);
	glVertex3f(-25, 75, -400);
	glVertex3f(25, 75, -400);
	glEnd();
}

/**************************************************************************************/

// This function is for drawing the UAH logo and applying the lighting effects
void drawUAH() {

	// Enable lighting and initialize all material properties for each object
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	// Set matrix to modelview and load identity
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Using the 3-step solution to rotate the UAH logo by the correct axis
	glTranslatef(0, 0, -400); 
	glRotatef(rotate, 0, 1, 0);
	glTranslatef(0, 0, 400);

	glMaterialfv(GL_FRONT, GL_SPECULAR, uh_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, uh_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, uh_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, uh_shiny);

	// 'U' portion 
	glTranslatef(-350, -25, -400);
	glutSolidCube(50); 
	glTranslatef(0, -50, 0);
	glutSolidCube(50);
	glTranslatef(0, -50, 0);
	glutSolidCube(50);
	glTranslatef(0, -50, 0);
	glutSolidCube(50);

	glTranslatef(50, 0, 0);
	glutSolidCube(50);
	glTranslatef(50, 0, 0);
	glutSolidCube(50);
	glTranslatef(50, 0, 0);
	glutSolidCube(50);

	glTranslatef(0, 50, 0);
	glutSolidCube(50);
	glTranslatef(0, 50, 0);
	glutSolidCube(50);
	glTranslatef(0, 50, 0);
	glutSolidCube(50);

	// Set color of the 'A' portion of the UAH logo
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, a_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, a_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, a_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, a_shininess);

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

	// Set color of the sphere inside the 'A' portion of the UAH logo
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ball_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ball_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ball_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, ball_shininess);

	// Sphere inside the A
	glTranslatef(25, 50, 0);
	glutSolidSphere(25, 50, 50);

	// Set color of the 'H' portion of the UAH logo
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, uh_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, uh_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, uh_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, uh_shiny);

	// 'H' portion
	glTranslatef(200, -100, 0); 
	glutSolidCube(50);
	glTranslatef(0, 50, 0);
	glutSolidCube(50);
	glTranslatef(0, 50, 0);
	glutSolidCube(50);
	glTranslatef(0, 50, 0);
	glutSolidCube(50);

	glTranslatef(50, -100, 0);
	glutSolidCube(50);
	glTranslatef(50, 0, 0);
	glutSolidCube(50);
	glTranslatef(50, 0, 0);
	glutSolidCube(50);

	glTranslatef(0, -50, 0);
	glutSolidCube(50);
	glTranslatef(0, 100, 0);
	glutSolidCube(50);
	glTranslatef(0, 50, 0);
	glutSolidCube(50);

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}

/**************************************************************************************/

// This is my display event handler 
void display_func(void)
{
	// Set the clear color to black and clear the color buffer
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set the shade model to flat and enable depth testing 
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	// Call the draw functions
	drawUAH();
	drawSpindle();

	// Swap the buffers
    glutSwapBuffers();
}

/**************************************************************************************/

// Set the canvas size to be 800 x 800
#define canvas_Width 800
#define canvas_Height 800

// Name the canvas 
char canvas_Name[] = "Colby McClure UAH Logo";

// This is my driver function 
int main(int argc, char ** argv) {

	// Initiate glut
	glutInit(&argc, argv);
	my_setup(canvas_Width, canvas_Height, canvas_Name);

	// Start the keyboard, display, and idle function handlers 
	glutDisplayFunc(display_func);
	glutTimerFunc(15, rotateUAH, 0);
	glutMainLoop();
	return 0;
}