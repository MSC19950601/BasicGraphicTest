#include"openglDependencies\glew\glew.h"
#include"openglDependencies\freeglut\freeglut.h"
#include<cmath>

const int n = 1e6;
const GLfloat a = 0.5f;
const GLfloat b = 0.3f;
const GLfloat Pi = 4 * tan(1);

void drawEclipseDirect() {
	glBegin(GL_POINTS);
	for (int i = 0;i < n;i++)
		glVertex2f(a*cos(2 * Pi / n*i), b*sin(2 * Pi / n*i));
	glEnd();
}

void putPixel(int x1, int y1, int x2, int y2) {
	glBegin(GL_POINTS);
	glVertex3f(x1 + x2, y1 + y2, 0);
	glEnd();
}

void drawEclipse(int x0, int y0, int a, int b) {
	int x, y;
	float d1, d2;
	x = 0;y = b;
	d1 = b*b + a*a*(-b + 0.25);
	putPixel(x0, y0, x, y);
	putPixel(x0, y0, -x, -y);
	putPixel(x0, y0, -x, y);
	putPixel(x0, y0, x, -y);
	while (b*b*(x + 1) < a*a*(y - 0.5)) {
		if (d1 < 0) {
			d1 += b*b*(2 * x + 3);
			x++;
		}
		else {
			d1 += b*b*(2 * x + 3) + a*a*(-2 * y + 2);
			x++;
			y--;
		}
		putPixel(x0, y0, x, y);
		putPixel(x0, y0, -x, -y);
		putPixel(x0, y0, -x, y);
		putPixel(x0, y0, x, -y);
	}
	d2 = b*b*(x + 0.5)*(x + 0.5) + a*a*(y - 1)*(y - 1) - a*a*b*b;//b*b*(2*x+2)+a*a*(-2*y+3)
	while (y > 0) {
		if (d2 <= 0) {
			d2 += b*b*(2 * x + 2) + a*a*(-2 * y + 3);
			x++;y--;
		}
		else {
			d2 += a*a*(-2 * y + 3);y--;
		}
		putPixel(x0, y0, x, y);
		putPixel(x0, y0, -x, -y);
		putPixel(x0, y0, -x, y);
		putPixel(x0, y0, x, -y);
	}
}

void Initial() {
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);//background color
		glColor3f(1.0, 0.0, 0.0);//line color											//glLoadIdentity(); 
		glMatrixMode(GL_PROJECTION);
		gluOrtho2D(0.0, 900.0, 0.0, 800.0);
		glMatrixMode(GL_MODELVIEW);
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 500, 500);
	//drawEclipseDirect();
	drawEclipse(250, 250, 200, 100);
	glFlush();
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Eclipse");
	Initial();
	glutDisplayFunc(Display);
	glutMainLoop();
	return 0;
}