#include <iostream>
#include <gl/glew.h> 
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <vector>
#include <math.h>

#define RECTINITSIZE 0.1
#define MAXRECTCOUNT 5
GLclampf darkgray[4] = { 25.0f / 256, 25.0f / 256 , 25.0f / 256 , 0.0f };
GLfloat	dx[4] = { 1.0f, -1.0f, -1.0f, 1.0f };
GLfloat dy[4] = { 1.0f, 1.0f, -1.0f, -1.0f };

struct rect {
	GLfloat x1;
	GLfloat y1;
	GLfloat x2;
	GLfloat y2;

	GLclampf r;
	GLclampf g;
	GLclampf b;
	GLclampf a = 0;
	
	int t = rand() % 360;

	GLfloat sx = (GLfloat)cos(t) / 100.0f;
	GLfloat sy = (GLfloat)sin(t) / 100.0f;

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
std::vector<struct rect> rectangles_tmp;


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
void draw_rect(int index);
void rectangle_new(GLclampf* input_pos);
void clamp_pos(GLfloat* input_pos);
void Mouse(int button, int state, int x, int y);
void reset();

void diagnoal();
void zigzag();

void diagnoal_timer(int value);
void zigzag_timer(int value);
void zigzag_turn_timer(int value);
void size_change_timer(int value);
void color_change_timer(int value);

void rectangles_remember();
void rectangles_origin();
void rectangles_random_dir();
void rectangles_zigzag_dir();
void rectangles_zigzag_change();
void rectangles_change_size();
void rectangles_change_color();
int rectcount = 0;
int stop_func = 0;
int proc_activated = 0;

void main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));

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
		if (proc_activated) {
			stop_func = 1;
			break;
		}
		proc_activated = 1;
		rectangles_remember();
		rectangles_random_dir();
		glutTimerFunc(10, diagnoal_timer, 1);
		std::cout << "1\n";

		break;
	case '2':
		if (proc_activated) {
			stop_func = 1;
			break;
		}
		proc_activated = 1;
		rectangles_remember();
		rectangles_zigzag_dir();
		glutTimerFunc(10, zigzag_timer, 1);
		glutTimerFunc(500, zigzag_turn_timer, 1);
		std::cout << "2\n";
		break;
	case '3':
		if (proc_activated) {
			stop_func = 1;
			break;
		}
		proc_activated = 1;
		rectangles_remember();
		glutTimerFunc(10, size_change_timer, 1);
		std::cout << "3\n";
		break;
	case '4':
		if (proc_activated) {
			stop_func = 1;
			break;
		}
		proc_activated = 1;
		rectangles_remember();
		glutTimerFunc(10, color_change_timer, 1);
		std::cout << "4\n";
		break;
	case '5':
		std::cout << "5\n";
		break;

	case 's':
	case 'S':
		if(proc_activated) stop_func = 1;
		rectangles_origin();
		std::cout << "S\n";
		break;
	
	case 'm':
	case 'M':
		std::cout << "M\n";
		break;

	case 'r':
	case 'R':
		reset();
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

void diagnoal() {
	for (int i = 0; i < rectcount; i++) {
		rectangles[i].x1 += rectangles[i].sx;

		if (rectangles[i].x1 < -1.0f) {
			rectangles[i].x1 -= 1* rectangles[i].sx;
			rectangles[i].sx *= -1;
		}


		rectangles[i].x2 += rectangles[i].sx;

		if (rectangles[i].x2 > 1.0f) {
			rectangles[i].x2 -= 1 * rectangles[i].sx;
			rectangles[i].sx *= -1;
		}

		rectangles[i].y1 += rectangles[i].sy;
		
		if (rectangles[i].y1 < -1.0f) {
			rectangles[i].y1 -= 1 * rectangles[i].sy;
			rectangles[i].sy *= -1;
		}

		rectangles[i].y2 += rectangles[i].sy;

		if (rectangles[i].y2 > 1.0f) {
			rectangles[i].y2 -= 1 * rectangles[i].sy;
			rectangles[i].sy *= -1;
		}

	}

	std::cout << rectangles[0].x1 << std::endl;
}

void zigzag() {
	for (int i = 0; i < rectcount; i++) {
		rectangles[i].x1 += rectangles[i].sx;
		rectangles[i].x2 += rectangles[i].sx;
		rectangles[i].y1 += rectangles[i].sy;
		rectangles[i].y2 += rectangles[i].sy;
		std::cout << rectangles[i].sx << std::endl;


	}
}

void diagnoal_timer(int value){	
	if (!stop_func) {
		diagnoal();
		glutPostRedisplay();
		glutTimerFunc(10, diagnoal_timer, 1);
	}
	else {
		proc_activated = 0;
		stop_func = 0;
	}
}


void zigzag_timer(int value) {
	if (!stop_func) {
		zigzag();
		glutPostRedisplay();
		glutTimerFunc(10, zigzag_timer, 1);
	}
	else {
		proc_activated = 0;
		stop_func = 0;
	}
}

void zigzag_turn_timer(int value) {
	if (!stop_func) {
		rectangles_zigzag_change();
		glutTimerFunc(500, zigzag_turn_timer, 1);
	}
	else {
		proc_activated = 0;
		stop_func = 0;
	}
}

void size_change_timer(int value) {

	if (!stop_func) {
		rectangles_change_size();
		glutPostRedisplay();
		glutTimerFunc(500, size_change_timer, 1);
	}
	else {
		proc_activated = 0;
		stop_func = 0;
	}
}

void color_change_timer(int value) {

	if (!stop_func) {
		rectangles_change_color();
		glutPostRedisplay();
		glutTimerFunc(500, color_change_timer, 1);
	}
	else {
		proc_activated = 0;
		stop_func = 0;
	}
}
void rectangles_remember() {
	if (!rectangles_tmp.empty()) rectangles_tmp.clear();
	for (int i = 0; i < rectcount; i++) {
		rectangles_tmp.push_back(rectangles[i]);
	}
}

void rectangles_origin() {
	if (!rectangles.empty()) rectangles.clear();


	for (int i = 0; i < rectcount; i++) {
		rectangles.push_back(rectangles_tmp[i]);
		
	}

	if (!rectangles_tmp.empty()) rectangles_tmp.clear();

}

void reset() {
	rectangles.clear();
	rectcount = 0;
	stop_func = 0;
	proc_activated = 0;
}

void rectangles_random_dir() {
	for (int i = 0; i < rectcount; i++) {
		int t = rand() % 360;
		rectangles[i].sx = (GLfloat)cos(t) / 100.0f;
		rectangles[i].sy = (GLfloat)sin(t) / 100.0f;
	}
}

void rectangles_zigzag_dir() {
	for (int i = 0; i < rectcount; i++) {
		int d = rand() % 4;
		rectangles[i].sx = (GLfloat)dx[d] * 1.5 / 100.0f;
		rectangles[i].sy = (GLfloat)dy[d] * 0.6 / 100.0f;
	}
}

void rectangles_zigzag_change() {
	for (int i = 0; i < rectcount; i++) {
		rectangles[i].sx *= -1;
	}
}

void rectangles_change_size() {
	for (int i = 0; i < rectcount; i++) {
		GLfloat tx = (GLfloat)(rand() % 20 - 10) / 100;
		GLfloat ty = (GLfloat)(rand() % 20 - 10) / 100;

		rectangles[i].x1 -= tx;

		if (rectangles[i].x1 < -1.0f) {
			rectangles[i].x1 = -1.0f;
		}


		rectangles[i].x2 += tx;

		if (rectangles[i].x2 > 1.0f) {
			rectangles[i].x2 = 1.0f;
		}

		rectangles[i].y1 -= ty;

		if (rectangles[i].y1 < -1.0f) {
			rectangles[i].y1 = -1.0f;
		}

		rectangles[i].y2 += ty;

		if (rectangles[i].y2 > 1.0f) {
			rectangles[i].y2 = 1.0f;
		}

		if (rectangles[i].x2 - rectangles[i].x1 < 0.3f) {
			rectangles[i].x2 += 0.05f;
			rectangles[i].x1 -= 0.05f;
		}

		if (rectangles[i].y2 - rectangles[i].y1 < 0.3f) {
			rectangles[i].y2 += 0.05f;
			rectangles[i].y1 -= 0.05f;
		}
	}

}

void rectangles_change_color() {
	for (int i = 0; i < rectcount; i++) {

		GLfloat r = (GLfloat)(rand() % 256) / 256;
		GLfloat g = (GLfloat)(rand() % 256) / 256;
		GLfloat b = (GLfloat)(rand() % 256) / 256;

		rectangles[i].r = r;
		rectangles[i].g = g;
		rectangles[i].b = b;
	}
}