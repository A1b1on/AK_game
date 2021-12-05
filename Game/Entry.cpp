#include <iostream>
#include "Window_manager/Main_Window.h"

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

void init(int w, int h) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float modelview[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
	glhPerspectivef2(modelview,45.0f, (float)w / (float)h, 0.1f, 100.0f); // настраиваем трехмерную перспективу
	glLoadMatrixf(modelview);
	glMatrixMode(GL_MODELVIEW); // переходим в трехмерный режим
}

int main(int argc, char* argv[]) {
	wmng::MainWindow* _Main_window = new wmng::MainWindow();
	try
	{
		_Main_window->Init_SDL();
		_Main_window->Init_GL();
		_Main_window->Window();
		_Main_window->GL_context();
		init(_Main_window->window_width(), _Main_window->window_height());
	}
	catch (const std::exception const& _e)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Start Error", _e.what(), NULL);
		exit(-1);
	}

	bool running = true;


	while (running) {

		_Main_window->Render();
		_Main_window->Display();
		
	
	}
	SDL_Quit(); // завершаем работу SDL и выходим
	return 0;
}

