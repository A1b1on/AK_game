#include "Main_Window.h"
#include <cstring>
#include <string>
using wmng::MainWindow;

//####################################### Constructos ####################################################

MainWindow::MainWindow() :
	MainWindow("Main Window", 880, 495, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL)
{
}

MainWindow::MainWindow(const char* title, const size_t& w, const size_t & h) :
	MainWindow(title, w, h, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL)
{	
}

MainWindow::MainWindow(const char* title, const size_t& w, const size_t& h, const size_t& x, const size_t& y) :
	MainWindow(title, w, h, x, y, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL)
{
}

MainWindow::MainWindow(const char* title, const size_t& w, const size_t& h, const size_t& x, const size_t& y, const Uint32& flags) :
	m_window(nullptr), m_glcontext(NULL),
	m_window_height(h), m_window_width(w),
	m_window_x_position(x), m_window_y_position(y),
	m_window_flags(flags)
{
	this->m_window_title = new char[ (strlen(title) + 1)];
	if (this->m_window_title)
		strcpy(this->m_window_title, title);
}

//###################################### Initizialization ################################################

bool MainWindow::InitSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::string _error = "Unable to init SDL, error: ";
		_error += SDL_GetError();
		throw std::runtime_error(_error.c_str());
		return 0;
	}
	return 1;
}

bool MainWindow::InitGL()  {
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	glewInit();
	return 1;
}

bool MainWindow::Window() {
	this->m_window = SDL_CreateWindow(this->m_window_title,
		this->m_window_x_position, this->m_window_y_position,
		this->m_window_width, this->m_window_height,
		this->m_window_flags);
	if (this->m_window == NULL) {
		std::string _error = "SDL window couldnt create: error: ";
		_error += SDL_GetError();
		throw std::runtime_error(_error.c_str());
		return 0;
	}
	return 1;
}

bool MainWindow::GLContext() {
	if (this->m_window == NULL) {
		throw std::runtime_error("GL context couldnt created");
		return 0;
	}	
	this->m_glcontext = SDL_GL_CreateContext(this->m_window);
	return 1;
}

//####################################### Return methods #################################################

size_t MainWindow::WindowHeight() const {
	return this->m_window_height;
}

size_t MainWindow::WindowWidth() const {
	return this->m_window_width;
}

size_t MainWindow::XPosition() const {
	return this->m_window_x_position;
}

size_t MainWindow::YPosition() const {
	return this->m_window_y_position;
}

const char* MainWindow::WindowTitle() const {
	return this->m_window_title;
}

//####################################### Rendering #################################################

void MainWindow::Display() {
	SDL_GL_SwapWindow(this->m_window);
}

void MainWindow::Render() {
	glFlush();
}

//####################################### GET #################################################

MainWindow* MainWindow::get()  {
	MainWindow* _window = new MainWindow();
	return _window;
}

MainWindow* MainWindow::get(const char* title, const size_t& w, const size_t& h)  {
	MainWindow* _window = new MainWindow(title, w, h);
	return _window;
}

MainWindow* MainWindow::get(const char* title, const size_t& w, const size_t& h, const size_t& x, const size_t& y) {
	MainWindow* _window = new MainWindow(title, w, h, x, y);
	return _window;
}

MainWindow* MainWindow::get(const char* title, const size_t& w, const size_t& h, const size_t& x, const size_t& y, const Uint32& flags) {
	MainWindow* _window = new MainWindow(title, w, h, x, y, flags);
	return _window;
}