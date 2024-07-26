#include "Shader.h"

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vPath, const char* fPath) {
	std::string vCode;
	std::string fCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	unsigned int vertex, fragment;

	try {
		vShaderFile.open(vPath);
		fShaderFile.open(fPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file contents into stream and convert to string
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vCode = vShaderStream.str();
		fCode = fShaderStream.str();
	} catch (std::ifstream::failure& e) {
		std::cerr << "Shader file not successfully read: " << e.what() << std::endl;
	}
	const char* vShaderCode = vCode.c_str();
	const char* fShaderCode = fCode.c_str();

	// compile shaders
	// vertex
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "Vertex");
	// fragment
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "Fragment");

	// create shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "Program");
	
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

// public methods
void Shader::use() {
	glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setInt(const std::string &name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

int Shader::getUniformLocation(const std::string &name) const {
	return glGetUniformLocation(ID, name.c_str());
}

// private methods
void Shader::checkCompileErrors(unsigned int shader, std::string type) {
	int success;
	char infoLog[1024];
	if (type != "Program") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "Shader compilation error of type: " << type << "\n" << infoLog << std::endl;
		}
	} else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "Program linking error of type: " << type << "\n" << infoLog << std::endl;
		}
	}
}
