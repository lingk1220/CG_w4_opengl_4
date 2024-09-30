#include <iostream>
#include <gl/glew.h> 
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

GLclampf darkgray[4] = { 25.0f / 256, 25.0f / 256 , 25.0f / 256 , 0.0f };

struct rect {
	GLfloat x1;
	GLfloat y1;
	GLfloat x2;
	GLfloat y2;

	GLclampf r;
	GLclampf g;
	GLclampf b;
	GLclampf a = 0;


	rect() {

	}

	rect(GLfloat ix1, GLfloat iy1, GLfloat ix2, GLfloat iy2) {
		x1 = ix1;
		x2 = ix2;
		y1 = iy1;
		y2 = iy2;

		r = (float)(rand() % 256) / 256;
		g = (float)(rand() % 256) / 256;
		b = (float)(rand() % 256) / 256;
	}
}rect;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);

void main(int argc, char** argv)
{


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("CG_4w_opengl_4");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		exit(EXIT_FAILURE);
	}
	else
		glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
}


GLvoid drawScene()
{
	glClearColor(darkgray[0], darkgray[1], darkgray[2], darkgray[3]);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}


GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}