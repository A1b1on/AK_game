#include "Render_Manager.h"
#include <string>

using rmng::RenderManager;

float vertices[] = {
	   -0.5f, -0.5f, 0.0f, // левая вершина
		0.5f, -0.5f, 0.0f, // правая вершина
		0.0f,  0.5f, 0.0f  // верхняя вершина   
};

//##################################### COMPILING #################################################

bool RenderManager::CompileShaders(const char*  _vertex_shader_code, const char*  _fragment_shader_code) {
	int success;
	char info_log[512];
	
	const char* vs_code = _vertex_shader_code;
	const char* fs_code = _fragment_shader_code;
	glewInit();
	this->m_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->m_vertex_shader, 1, &vs_code, NULL);
	glCompileShader(this->m_vertex_shader);

	glGetShaderiv(this->m_vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(this->m_vertex_shader, 512, NULL, info_log);
		throw info_log;
		return 0;
	}

	this->m_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->m_fragment_shader, 1, &fs_code, NULL);
	glCompileShader(this->m_fragment_shader);

	glGetShaderiv(this->m_fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(this->m_fragment_shader, 512, NULL, info_log);
		throw info_log;
		return 0;
	}
	
	this->m_shader_program = glCreateProgram();
	glAttachShader(this->m_shader_program, this->m_vertex_shader);
	glAttachShader(this->m_shader_program, this->m_fragment_shader);
	glLinkProgram(this->m_shader_program);

	glGetProgramiv(this->m_shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->m_shader_program, 512, NULL, info_log);
		throw info_log;
		return 0;
	}

	glDeleteShader(this->m_vertex_shader);
	glDeleteShader(this->m_fragment_shader);
	return 1;
}

bool RenderManager::CompileObjects() {
	glGenVertexArrays(1, &this->m_VAO);
	glGenBuffers(1, &this->m_VBO);

	glBindVertexArray(this->m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return 1;
}

void RenderManager::DeleteObjects() {
	glDeleteVertexArrays(1, &this->m_VAO);
	glDeleteBuffers(1, &this->m_VBO);
}

//####################################### GET #################################################

RenderManager* RenderManager::get() {
	RenderManager* obj = new RenderManager();
	return obj;
}