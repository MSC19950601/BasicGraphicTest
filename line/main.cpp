//#include<gl\GL.h>
//#include<gl\GLU.h>
//#include"openglDependencies\freeglut\glut.h"
#include<cmath>
#include"openglDependencies\glew\glew.h"
#include"openglDependencies\freeglut\freeglut.h"

//DDA�㷨
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
//�е�Bresenham�㷨
void MidBresenhamLine(int x0, int y0, int x1, int y1)
{
	int dx, dy, d, upIncre, downIncre, x, y;
	if (x0 > x1)
	{
		x = x1; x1 = x0; x0 = x;
		y = y1; y1 = y0; y0 = y;
	}
	x = x0; y = y0;
	dx = x1 - x0; dy = y1 - y0;
	d = dx - 2 * dy;
	upIncre = 2 * dx - 2 * dy; downIncre = -2 * dy;
	while (x <= x1) {
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
		x++;
		if (d < 0)
		{
			y++;
			d += upIncre;
		}
		else
			d += downIncre;
	}
}
//Bresenham�㷨
void BresenhamLine(int x0, int y0, int x1, int y1){
	int x, y, dx, dy, e;
	dx = x1 - x0;
	dy = y1 - y0;
	e = -dx; x = x0; y = y0;
	while (x <= x1) {
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
		x++;
		e = e + 2 * dy;
		if (e > 0) {
			y++;
			e = e - 2 * dx;
		}
	}
}

void Initial(){
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);      //���ô��ڱ�����ɫΪ��ɫ
	//glutSetColor(1, 1.0f, 1.0f, 0.5f);
	glColor3f(1.0, 0.0, 0.0);					//������ɫ											//glLoadIdentity(); 
	glMatrixMode(GL_PROJECTION);     //����ͶӰ����
	gluOrtho2D(0.0, 900.0, 0.0, 800.0);
	//glMatrixMode(GL_MODELVIEW);  
}


void Display(){
	glClear(GL_COLOR_BUFFER_BIT);   //�õ�ǰ����ɫ��䴰��
	glViewport(0, 0, 500, 500);		//ָ��������ʾ����
	dda_line(250,230,1800,2000);				//DDA�㷨
	//MidBresenhamLine(310,200,1800,2000);		//�е�Bresenham�㷨
	//BresenhamLine(250,230,1800,2000);			//Bresenham�㷨
	//glBresCircle(650, 550, 100);
	glFlush();                         //�������е�OpenGL����
}

int main(int argc, char* argv[]){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  //��ʼ�����ڵ���ʾģʽ
	glutInitWindowSize(500, 500);                  //���ô��ڵĳߴ�
	glutInitWindowPosition(400, 300);               //���ô��ڵ�λ��
	glutCreateWindow("ֱ��");                    //����һ����Ϊ���εĴ���
	glutDisplayFunc(Display);                     //���õ�ǰ���ڵ���ʾ�ص�����
	Initial();                                    //��ɴ��ڳ�ʼ��
	glutMainLoop();                             //������GLUT�¼�����ѭ��
	return 0;
}