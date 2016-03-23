#include<cmath>
#include"openglDependencies\glew\glew.h"
#include"openglDependencies\freeglut\freeglut.h"

void dda_line(int x0, int y0, int xn, int yn){
	GLfloat dx = xn - x0;
	GLfloat dy = yn - y0;

	GLint steps = 0;
	GLfloat deltaX = 0;
	GLfloat deltaY = 0;
	GLfloat x = x0;
	GLfloat y = y0;

	if (abs(dx) > abs(dy)) {
		steps = abs(dx);
	}
	else {
		steps = abs(dy);
	}
	deltaX = (GLfloat)dx / (GLfloat)steps;
	deltaY = (GLfloat)dy / (GLfloat)steps;
	glBegin(GL_POINTS);
	for (GLint i = 1; i <= steps;i++) {
		
		glVertex2i(x, y);
		x += deltaX;
		y += deltaY;
	}
	glEnd();
}

void MidBresenhamLine(int x0, int y0, int xn, int yn){
	GLint a = yn - y0;
	GLint b = -(xn - x0);
	GLint c = xn*y0 - yn*x0;

	GLint deltaA = 0;
	GLint deltaB = 0;
	if (a != 0) {
		deltaA = a / abs(a);
	}
	if (b != 0) {
		deltaB = -b / abs(b);
	}
	GLfloat x = x0;
	GLfloat y = y0;

	if (abs(a) < abs(b)) {
		GLint steps = abs(b);
		for (GLint i = 0;i < steps;i++) {
			if ((a*(x + 1) + b*(y + 0.5) + c) > 0){
				y += deltaA;
			}
			x += deltaB;
			glBegin(GL_POINTS);
			glVertex2i(x, y);
			glEnd();
		}
	}
	else {
		GLint steps = abs(a);
		for (GLint i = 0;i < steps;i++) {
			if ((a*(x + 1) + b*(y + 0.5) + c) > 0) {
				x += deltaB;
			}
			y += deltaA;
			glBegin(GL_POINTS);
			glVertex2i(x, y);
			glEnd();
		}
	}
}

void BresenhamLine(int x0, int y0, int xn, int yn){
	GLint dx = xn - x0;
	GLint dy = yn - y0;

	GLint steps = 0;
	GLfloat slope = 0.0f;
	GLfloat x = x0;
	GLfloat y = y0;

	GLint deltaX = 0;
	GLint deltaY = 0;

	GLfloat e = -0.5f;

	if (dx != 0) {
		deltaX = dx / abs(dx);
		slope = (GLfloat)dy / (GLfloat)dx;
	}
	else
		slope = 65535;
	if (dy != 0)
		deltaY = dy / abs(dy);

	if (abs(slope) <= 1) {
		steps = abs(dx);
		glBegin(GL_POINTS);
		for (GLint i = 1; i <= steps;i++) {
			x += deltaX;
			e += slope;
			if (e > 0) {
				y += deltaY;
				e -= slope / abs(slope);
			}
			glVertex2i(x, y);
		}
		glEnd();
	}
	else {
		steps = abs(dy);
		slope = 1 / slope;
		glBegin(GL_POINTS);
		for (GLint i = 1;i <= steps;i++) {
			y += deltaY;
			e += slope;
			if (e > 0) {
				x += deltaX;
				e -= slope / abs(slope);
			}
			glVertex2i(x, y);
		}
		glEnd();
	}
}

void Initial(){
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);//background color
	glColor3f(1.0, 0.0, 0.0);//line color											//glLoadIdentity(); 
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 900.0, 0.0, 800.0);
	glMatrixMode(GL_MODELVIEW);  
}


void Display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 500, 500);
	dda_line(25,23,1800,2000);				//DDA
	MidBresenhamLine(31,20,1800,2000);		//middel Bresenham
	BresenhamLine(10,28,1800,2000);			//Bresenham
	glFlush();
}

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
	glutInitWindowSize(500, 500);       
	glutInitWindowPosition(400, 300);       
	glutCreateWindow("draw line");                 
	glutDisplayFunc(Display);          
	Initial();                               
	glutMainLoop();                    
	return 0;
}