#include <iostream>
#include <Windows.h>
#include <SDL.h>
#include <GL/GL.h>
#include <GL/GLU.h>


SDL_Window* window;

const int width = 640;
const int height = 480;	

void glhFrustumf2(float* matrix, float left, float right, float bottom, float top,
	float znear, float zfar)
{
	float temp, temp2, temp3, temp4;
	temp = 2.0 * znear;
	temp2 = right - left;
	temp3 = top - bottom;
	temp4 = zfar - znear;
	matrix[0] = temp / temp2;
	matrix[1] = 0.0;
	matrix[2] = 0.0;
	matrix[3] = 0.0;
	matrix[4] = 0.0;
	matrix[5] = temp / temp3;
	matrix[6] = 0.0;
	matrix[7] = 0.0;
	matrix[8] = (right + left) / temp2;
	matrix[9] = (top + bottom) / temp3;
	matrix[10] = (-zfar - znear) / temp4;
	matrix[11] = -1.0;
	matrix[12] = 0.0;
	matrix[13] = 0.0;
	matrix[14] = (-temp * zfar) / temp4;
	matrix[15] = 0.0;
}
void glhPerspectivef2(float* matrix, float fovyInDegrees, float aspectRatio,
	float znear, float zfar)
{
	float ymax, xmax;
	float temp, temp2, temp3, temp4;
	ymax = znear * tanf(fovyInDegrees * M_PI / 360.0);
	//ymin = -ymax;
	//xmin = -ymax * aspectRatio;
	xmax = ymax * aspectRatio;
	glhFrustumf2(matrix, -xmax, xmax, -ymax, ymax, znear, zfar);
}
void drawCube(float x, float y, float z);
void init() {

	// ������������� SDL

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Unable to init SDL, error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	// �������� ������� �����, ����������� �����

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);

	// ������� ���� � ���������� "Cube", �������� 640�480 � ������������� �� ������ ������.

	window = SDL_CreateWindow("Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	SDL_GLContext glcontext = SDL_GL_CreateContext(window); // ������� �������� OpenGL

	if (window == NULL) {	// ���� �� ���������� ������� ����, �� �������
		exit(1);
	}

	// ������������� OpenGL

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // ������������� ������� ���� �� ������
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST); // �������� ���� �������
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float modelview[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
	glhPerspectivef2(modelview,45.0f, (float)width / (float)height, 0.1f, 100.0f); // ����������� ���������� �����������
	glLoadMatrixf(modelview);
	glMatrixMode(GL_MODELVIEW); // ��������� � ���������� �����
}
int main(int argc, char* argv[]) {

	init(); // �������������

	bool running = true;

	float xrf = 0, yrf = 0, zrf = 0; // ���� ��������

	while (running) {

		SDL_Event event; // ������� SDL

		while (SDL_PollEvent(&event)) { // �������� ��������� �������
			switch (event.type) { // �������:
			case SDL_QUIT: // ���� ��������� ������� �������� ����, �� ��������� ������ ���������
				running = false;
				break;

			case SDL_KEYDOWN: // ���� ������ �������
				switch (event.key.keysym.sym) { // ������� �����
				case SDLK_ESCAPE: // ������� ESC
					running = false; // ��������� ������ ���������
					break;
				}
				break;
			}
		}

		// ���� ��������� �������� �������� ���� ��������, ��� ����� ������ ���

		xrf -= 0.5;
		yrf -= 0.5;
		zrf -= 0.5;

		drawCube(xrf, yrf, zrf); // ������ ��� ��� � �������� ������ ��������

		// ��������� �����

		glFlush();
		SDL_GL_SwapWindow(window);
	}

	SDL_Quit(); // ��������� ������ SDL � �������
	return 0;
}

void drawCube(float xrf, float yrf, float zrf) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -7.0f);	// �������� ������ ������

	glRotatef(xrf, 1.0f, 0.0f, 0.0f);	// �������� ���� �� X, Y, Z
	glRotatef(yrf, 0.0f, 1.0f, 0.0f);	// �������� ���� �� X, Y, Z
	glRotatef(zrf, 0.0f, 0.0f, 1.0f);	// �������� ���� �� X, Y, Z

	glBegin(GL_QUADS);		// ������ ���

	glColor3f(0.0f, 1.0f, 0.0f);		// ����� ������� (�������)
	glVertex3f(1.0f, 1.0f, -1.0f);		// ������� ������ ���� ��������
	glVertex3f(-1.0f, 1.0f, -1.0f);		// ������� �����
	glVertex3f(-1.0f, 1.0f, 1.0f);		// ������ �����
	glVertex3f(1.0f, 1.0f, 1.0f);		// ������ ������

	glColor3f(1.0f, 0.5f, 0.0f);		// ��������� ������� (������)
	glVertex3f(1.0f, -1.0f, 1.0f);	// ������� ������ ���� ��������
	glVertex3f(-1.0f, -1.0f, 1.0f);	// ������� �����
	glVertex3f(-1.0f, -1.0f, -1.0f);	// ������ �����
	glVertex3f(1.0f, -1.0f, -1.0f);	// ������ ������

	glColor3f(1.0f, 0.0f, 0.0f);		// ������� ������� (��������)
	glVertex3f(1.0f, 1.0f, 1.0f);		// ������� ������ ���� ��������
	glVertex3f(-1.0f, 1.0f, 1.0f);		// ������� �����
	glVertex3f(-1.0f, -1.0f, 1.0f);		// ������ �����
	glVertex3f(1.0f, -1.0f, 1.0f);		// ������ ������

	glColor3f(1.0f, 1.0f, 0.0f);			// ������ ������� (������)
	glVertex3f(1.0f, -1.0f, -1.0f);	// ������� ������ ���� ��������
	glVertex3f(-1.0f, -1.0f, -1.0f);	// ������� �����
	glVertex3f(-1.0f, 1.0f, -1.0f);	// ������ �����
	glVertex3f(1.0f, 1.0f, -1.0f);	// ������ ������

	glColor3f(0.0f, 0.0f, 1.0f);			// ����� ������� (�����)
	glVertex3f(-1.0f, 1.0f, 1.0f);	// ������� ������ ���� ��������
	glVertex3f(-1.0f, 1.0f, -1.0f);	// ������� �����
	glVertex3f(-1.0f, -1.0f, -1.0f);	// ������ �����
	glVertex3f(-1.0f, -1.0f, 1.0f);	// ������ ������

	glColor3f(1.0f, 0.0f, 1.0f);			// ���������� ������� (������)
	glVertex3f(1.0f, 1.0f, -1.0f);	// ������� ������ ���� ��������
	glVertex3f(1.0f, 1.0f, 1.0f);	// ������� �����
	glVertex3f(1.0f, -1.0f, 1.0f);	// ������ �����
	glVertex3f(1.0f, -1.0f, -1.0f);	// ������ ������

	glEnd();	// ��������� ��������

}