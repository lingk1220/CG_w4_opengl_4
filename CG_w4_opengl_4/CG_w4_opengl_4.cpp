#include <iostream>
#include <gl/glew.h> 
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <vector>
#define RECTINITSIZE 0.1
#define MAXRECTCOUNT 5
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

std::vector<struct rect> rectangles;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
void draw_rect(int index);
void rectangle_new(GLclampf* input_pos);
void clamp_pos(GLfloat* input_pos);
void Mouse(int button, int state, int x, int y);


int rectcount = 0;

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
	glutMouseFunc(Mouse);
	glutMainLoop();
}


GLvoid drawScene()
{
	glClearColor(darkgray[0], darkgray[1], darkgray[2], darkgray[3]);
	glClear(GL_COLOR_BUFFER_BIT);

	if (!rectangles.empty()) {
		for (int i = 0; i < rectangles.size(); i++) {
			draw_rect(i);
		}
	}

	glutSwapBuffers();
}


GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '1':
		std::cout << "1\n";
		break;
	case '2':
		std::cout << "2\n";
		break;
	case '3':
		std::cout << "3\n";
		break;
	case '4':
		std::cout << "4\n";
		break;
	case '5':
		std::cout << "5\n";
		break;

	case 's':
	case 'S':
		std::cout << "S\n";
		break;
	
	case 'm':
	case 'M':
		std::cout << "M\n";
		break;

	case 'r':
	case 'R':
		std::cout << "R\n";
		break;

	case 'q':
	case 'Q':
		std::cout << "Q\n";
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y) {
	GLfloat input_pos[2] = { x, y };
	clamp_pos(input_pos);
	if (state == GLUT_DOWN) {
		glutPostRedisplay();
	}
	else {
		if (rectcount < MAXRECTCOUNT) {
			rectcount++;
			rectangle_new(input_pos);
		}
	}

}

void clamp_pos(GLfloat* input_pos) {
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	int viewport_width = viewport[2];
	int viewport_height = viewport[3];
	input_pos[0] = (input_pos[0] / viewport_width) * 2 - 1.0f;
	input_pos[1] = -1 * ((input_pos[1] / viewport_height) * 2 - 1.0f);
}

void rectangle_new(GLclampf * input_pos) {
	GLclampf x = input_pos[0];
	GLclampf y = input_pos[1];
	struct rect rect_new(x - RECTINITSIZE, y - RECTINITSIZE, x + RECTINITSIZE, y + RECTINITSIZE);
	rectangles.push_back(rect_new);
}

void draw_rect(int index) {
	glColor3f(rectangles[index].r, rectangles[index].g, rectangles[index].b);
	glRectf(rectangles[index].x1, rectangles[index].y1, rectangles[index].x2, rectangles[index].y2);
}