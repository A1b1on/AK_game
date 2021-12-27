#include <iostream>
#include "Window_manager/Main_Window.h"
#include "Filesystem_manager/File_System.h"
#include "Render_manager/Render_Manager.h"

int main(int argc, char* argv[]) {
	auto main_window = wmng::MainWindow::get();
	auto file_system = fmng::FileManager::get();
	auto render_manager = rmng::RenderManager::get();
	try
	{
		main_window->InitSDL();
		main_window->InitGL();
		main_window->Window();
		main_window->GLContext();

		file_system->GenerateShaderCode();
		render_manager->CompileShaders(file_system->VertexShaderCode(), file_system->FragmentShaderCode());
		render_manager->CompileObjects();
	} catch (const std::exception const& _e)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Start Error", _e.what(), NULL);
		exit(-1);
	} catch (const char* _e) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Start Error", _e, NULL);
		exit(-1);
	}

	bool running = true;

	while (running) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Рисуем наш первый треугольник
		glUseProgram(render_manager->m_shader_program);
		glBindVertexArray(render_manager->m_VAO); 
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		main_window->Display();
	
	}
	render_manager->DeleteObjects();
	SDL_Quit();
	return 0;
}

