#include <windows.h>
#include <SDL.h>
#include <glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <stdexcept>

namespace wmng {

	class MainWindow {
		MainWindow();
		MainWindow(const char* title, const size_t& w, const size_t& h);
		MainWindow(const char* title, const size_t& w, const size_t& h, const size_t& x, const size_t& y);
		MainWindow(const char* title, const size_t& w, const size_t& h, const size_t& x, const size_t& y, const Uint32& flags);
		MainWindow(MainWindow&) = delete;
		void operator=(MainWindow&) {}

		SDL_GLContext	m_glcontext;
		SDL_Window*		m_window;
		size_t			m_window_height;
		size_t			m_window_width;
		size_t			m_window_x_position;
		size_t			m_window_y_position;
		char*			m_window_title;
		Uint32			m_window_flags;
		//todo: remove after start
		float x = 0, y = 0, z = 0;
	public:

		~MainWindow() { delete[] this->m_window_title; }

		bool InitSDL();
		bool InitGL();
		bool Window();
		bool GLContext();

		size_t WindowHeight() const;
		size_t WindowWidth() const;
		size_t XPosition() const;
		size_t YPosition() const;
		const char* WindowTitle() const;
	
		void Display();
		void Render();

		static MainWindow* get();
		static MainWindow* get(const char* title, const size_t& w, const size_t& h);
		static MainWindow* get(const char* title, const size_t& w, const size_t& h, const size_t& x, const size_t& y);
		static MainWindow* get(const char* title, const size_t& w, const size_t& h, const size_t& x, const size_t& y, const Uint32& flasgs);

	};

}