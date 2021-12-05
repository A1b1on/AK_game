#include "Main_Window.h"
#include <cstring>
#include <string>
using wmng::MainWindow;

//####################################### Constructos ####################################################

MainWindow::MainWindow() :
	MainWindow("Main Window", 880, 495, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL)
{
}

MainWindow::MainWindow(const char* title, size_t w, size_t h) :
	MainWindow(title, w, h, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL)
{	
}

MainWindow::MainWindow(const char* title, size_t w, size_t h, size_t x, size_t y) :
	MainWindow(title, w, h, x, y, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL)
{
}

MainWindow::MainWindow(const char* title, size_t w, size_t h, size_t x, size_t y, Uint32 flags) :
	_window(nullptr), _glcontext(NULL),
	_window_height(h), _window_width(w),
	_window_x_position(x), _window_y_position(y),
	_window_flags(flags)
{
	this->_window_title = (char*)malloc(sizeof(char) * (strlen(title) + 1));
	if (this->_window_title)
		strcpy(this->_window_title, title);
}

//###################################### Initizialization ################################################

bool MainWindow::Init_SDL() 
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::string _error = "Unable to init SDL, error: ";
		_error += SDL_GetError();
		throw std::runtime_error(_error.c_str());
		return 0;
	}
	return 1;
}

bool MainWindow::Init_GL() 
{
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);

	return 1;
}

bool MainWindow::Window()
{
	this->_window = SDL_CreateWindow(this->_window_title,
		this->_window_x_position, this->_window_y_position,
		this->_window_width, this->_window_height,
		this->_window_flags);
	if (this->_window == NULL) {
		std::string _error = "SDL window couldnt create: error: ";
		_error += SDL_GetError();
		throw std::runtime_error(_error.c_str());
		return 0;
	}
	return 1;
}

bool MainWindow::GL_context() {
	if (this->_window == NULL) {
		throw std::runtime_error("GL context couldnt created");
		return 0;
	}	
	this->_glcontext = SDL_GL_CreateContext(this->_window);
	return 1;
}

//####################################### Return methods #################################################

size_t MainWindow::window_height() const 
{
	return this->_window_height;
}

size_t MainWindow::window_width() const
{
	return this->_window_width;
}

size_t MainWindow::x_position() const
{
	return this->_window_x_position;
}

size_t MainWindow::y_position() const
{
	return this->_window_y_position;
}

const char* MainWindow::window_title() const
{
	return this->_window_title;
}

//####################################### Rendering #################################################

void MainWindow::Display()
{
	SDL_GL_SwapWindow(this->_window);
}
//todo: remove this
void drawCube(float xrf, float yrf, float zrf) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -7.0f);	// Сдвинуть вглубь экрана

	glRotatef(xrf, 1.0f, 0.0f, 0.0f);	// Вращение куба по X, Y, Z
	glRotatef(yrf, 0.0f, 1.0f, 0.0f);	// Вращение куба по X, Y, Z
	glRotatef(zrf, 0.0f, 0.0f, 1.0f);	// Вращение куба по X, Y, Z

	glBegin(GL_QUADS);		// Рисуем куб

	glColor3f(0.0f, 1.0f, 0.0f);		// Синяя сторона (Верхняя)
	glVertex3f(1.0f, 1.0f, -1.0f);		// Верхний правый угол квадрата
	glVertex3f(-1.0f, 1.0f, -1.0f);		// Верхний левый
	glVertex3f(-1.0f, 1.0f, 1.0f);		// Нижний левый
	glVertex3f(1.0f, 1.0f, 1.0f);		// Нижний правый

	glColor3f(1.0f, 0.5f, 0.0f);		// Оранжевая сторона (Нижняя)
	glVertex3f(1.0f, -1.0f, 1.0f);	// Верхний правый угол квадрата
	glVertex3f(-1.0f, -1.0f, 1.0f);	// Верхний левый
	glVertex3f(-1.0f, -1.0f, -1.0f);	// Нижний левый
	glVertex3f(1.0f, -1.0f, -1.0f);	// Нижний правый

	glColor3f(1.0f, 0.0f, 0.0f);		// Красная сторона (Передняя)
	glVertex3f(1.0f, 1.0f, 1.0f);		// Верхний правый угол квадрата
	glVertex3f(-1.0f, 1.0f, 1.0f);		// Верхний левый
	glVertex3f(-1.0f, -1.0f, 1.0f);		// Нижний левый
	glVertex3f(1.0f, -1.0f, 1.0f);		// Нижний правый

	glColor3f(1.0f, 1.0f, 0.0f);			// Желтая сторона (Задняя)
	glVertex3f(1.0f, -1.0f, -1.0f);	// Верхний правый угол квадрата
	glVertex3f(-1.0f, -1.0f, -1.0f);	// Верхний левый
	glVertex3f(-1.0f, 1.0f, -1.0f);	// Нижний левый
	glVertex3f(1.0f, 1.0f, -1.0f);	// Нижний правый

	glColor3f(0.0f, 0.0f, 1.0f);			// Синяя сторона (Левая)
	glVertex3f(-1.0f, 1.0f, 1.0f);	// Верхний правый угол квадрата
	glVertex3f(-1.0f, 1.0f, -1.0f);	// Верхний левый
	glVertex3f(-1.0f, -1.0f, -1.0f);	// Нижний левый
	glVertex3f(-1.0f, -1.0f, 1.0f);	// Нижний правый

	glColor3f(1.0f, 0.0f, 1.0f);			// Фиолетовая сторона (Правая)
	glVertex3f(1.0f, 1.0f, -1.0f);	// Верхний правый угол квадрата
	glVertex3f(1.0f, 1.0f, 1.0f);	// Верхний левый
	glVertex3f(1.0f, -1.0f, 1.0f);	// Нижний левый
	glVertex3f(1.0f, -1.0f, -1.0f);	// Нижний правый

	glEnd();	// Закончили квадраты

}

void MainWindow::Render()
{
	this->x -= 0.5;
	this->y -= 0.5;
	this->z -= 0.5;
	drawCube(this->x, this->y, this->z);
	glFlush();
}