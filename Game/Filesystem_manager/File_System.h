#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

namespace fmng {
	
	class FileManager {
		
		char*		m_vertex_shader_file_path	= nullptr;
		char*		m_fragment_shader_file_path = nullptr;
		char*		m_vertex_shader_code		= nullptr;
		char*		m_fragment_shader_code		= nullptr;
		
		FileManager();
		FileManager(const char* _vertex_shader_path, const char* _fragment_shader_path);
		FileManager(FileManager&) = delete;
		void operator=(FileManager&) {}
	public:
		
		const char* VertexShaderCode();
		const char* FragmentShaderCode();

		void SetShaderPath(const char* _vertex_shader_path, const char* _fragment_shader_path);
		bool GenerateShaderCode();
		bool ClearPath();

		static FileManager* get();
		static FileManager* get(const char* _vertex_shader_path, const char* _fragment_shader_path);
	};

}