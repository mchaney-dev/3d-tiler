#ifndef SHADER_H
#define SHADER_H

#include <string>

class Shader {
	private:
		void checkCompileErrors(unsigned int shader, std::string type);

	public:
		unsigned int ID;
		Shader(const char* vPath, const char* fPath);
		void use();
		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string &name, int value) const;
		void setFloat(const std::string &name, float value) const;
		int getUniformLocation(const std::string &name) const;
};

#endif
