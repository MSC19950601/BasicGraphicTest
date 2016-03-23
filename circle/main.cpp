#include"openglDependencies\glew\glew.h"
#include"openglDependencies\freeglut\freeglut.h"
#include<cmath>

const int n = 1e6;
const GLfloat R = 0.5f;
const GLfloat Pi = 4 * tan(1);

void Display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	for (int i = 0;i < n;i++)
		glVertex2f(R*cos(2 * Pi / n*i), R*sin(2 * Pi / n*i));
	glEnd();
	glFlush();
}

int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("circle");
	glutDisplayFunc(Display);
	glutMainLoop();
	return 0;
}