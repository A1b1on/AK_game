#include <windows.h>
#include <SDL.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <stdexcept>

namespace wmng {

	class MainWindow {
		SDL_GLContext	_glcontext;
		SDL_Window*		_window;
		size_t			_window_height;
		size_t			_window_width;
		size_t			_window_x_position;
		size_t			_window_y_position;
		char*			_window_title;
		Uint32			_window_flags;
		//todo: remove after start
		float x = 0, y = 0, z = 0;
	public:
		MainWindow();
		MainWindow(const char* title, size_t w, size_t h);
		MainWindow(const char* title, size_t w, size_t h, size_t x, size_t y);
		MainWindow(const char* title, size_t w, size_t h, size_t x, size_t y, Uint32 flags);

		bool Init_SDL();
		bool Init_GL();
		bool Window();
		bool GL_context();

		size_t window_height() const;
		size_t window_width() const;
		size_t x_position() const;
		size_t y_position() const;
		const char* window_title() const;
	
		void Display();
		void Render();
	};

}