#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
	//constructor reads and builds the shader
	Shader(const char *vertexPath, const char *fragmentPath);
	//use/activate the shader
	void use();
	//utility uniform functions
	void setBool(const std::string &name, bool value);
	void setInt(const std::string &name, int value);
	void setFloat(const std::string &name, float value);
	void setMat4(const std::string &name, glm::mat4 &matrix);
	void setVec3(const std::string &name, glm::vec3 &vector);
private:
	//the program id
	unsigned int ID;
};

#endif
