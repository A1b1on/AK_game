#include <Windows.h>
#include <glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

namespace rmng {
	
	class RenderManager {
		RenderManager() {}
		RenderManager(RenderManager&) = delete;
		void operator=(RenderManager&) {}
	public:
		GLuint m_vertex_shader = 0;
		GLuint m_fragment_shader = 0;
		GLuint m_shader_program = 0;

		GLuint m_VAO = 0;
		GLuint m_VBO = 0;

		bool CompileShaders(const char* _vertex_shader_code, const char*  _fragment_shader_code);
		bool CompileObjects();
		void DeleteObjects();
		static RenderManager* get();
	};

}