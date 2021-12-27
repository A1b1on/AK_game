#include "File_System.h"
#include <fstream>
using fmng::FileManager;

//####################################### Constructos ####################################################

FileManager::FileManager() {
#ifndef STANDART_SHADER
	this->SetShaderPath("vs.glsl", "fs.glsl");
#endif 
}

FileManager::FileManager(const char* _vertex_shader_path, const char* _fragment_shader_path) {
	this->SetShaderPath(_vertex_shader_path, _fragment_shader_path);
}

//################################### SETTERS & GETTERS #################################################

void FileManager::SetShaderPath(const char* _vertex_shader_path, const char* _fragment_shader_path) {
	this->m_vertex_shader_file_path = new char[ strlen(_vertex_shader_path) + 1 ];
	if (this->m_vertex_shader_file_path)
		strcpy(this->m_vertex_shader_file_path, _vertex_shader_path);

	this->m_fragment_shader_file_path = new char[strlen(_fragment_shader_path) + 1];;
	if (this->m_fragment_shader_file_path)
		strcpy(this->m_fragment_shader_file_path, _fragment_shader_path);
}

const char* FileManager::VertexShaderCode() {
	return this->m_vertex_shader_code;
}

const char* FileManager::FragmentShaderCode() {
	return  this->m_fragment_shader_code;
}

//####################################### Instructions with shader #########################################

bool FileManager::GenerateShaderCode()  {
	size_t size;
	
	std::ifstream file(this->m_vertex_shader_file_path);
	file.seekg(0, std::ios::end);
	size = file.tellg();
	this->m_vertex_shader_code = new char[size];
	file.seekg(0);
	file.read(this->m_vertex_shader_code, size);
	file.close();

	file.open(this->m_fragment_shader_file_path);
	file.seekg(0, std::ios::end);
    size = file.tellg();
	this->m_fragment_shader_code = new char[size];
	file.seekg(0);
	file.read(this->m_fragment_shader_code, size);
	file.close();

	this->ClearPath();
	return 1;
}

bool FileManager::ClearPath() {
	if(this->m_vertex_shader_code)
		delete[] this->m_vertex_shader_file_path;
	if(this->m_fragment_shader_code)
		delete[] this->m_fragment_shader_file_path;
	return 1;
}

//####################################### GET #################################################

FileManager* FileManager::get() {
	FileManager* obj = new FileManager();
	return obj;
}

FileManager* FileManager::get(const char* _vertex_shader_path, const char* _fragment_shader_path) {
	FileManager* obj = new FileManager(_vertex_shader_path, _fragment_shader_path);
	return obj;
}