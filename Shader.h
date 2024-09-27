#pragma once

#include <glad/glad.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

class Shader
{
private:
	unsigned int ID;
	bool isUsing = false;

public:
	void Init(const char* vShaderLoc, const char* fShaderLoc)
	{
		std::string vFileString, fFileString;

		std::ifstream vFile(vShaderLoc);
		std::ifstream fFile(fShaderLoc);

		try
		{
			std::stringstream vSS;
			std::stringstream fSS;

			vSS << vFile.rdbuf();
			fSS << fFile.rdbuf();

			vFileString = vSS.str();
			fFileString = fSS.str();

			vFile.close();
			fFile.close();
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}

		const char* vShaderSource = vFileString.c_str();
		const char* fShaderSource = fFileString.c_str();

		unsigned int vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderSource, nullptr);
		glCompileShader(vertex);
		CheckShaderError(vertex, "Vertex");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderSource, nullptr);
		glCompileShader(fragment);
		CheckShaderError(fragment, "Fragment");

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void Use()
	{
		if (!isUsing)
		{
			glUseProgram(ID);
			isUsing = true;
		}
	}

	void Unuse()
	{
		if (isUsing)
		{
			glUseProgram(0);
			isUsing = false;
		}
	}

	void SetMat4(const std::string& name, glm::mat4& v)
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(v));
	}

	void SetVec3(const std::string& name, glm::vec3& v)
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(v));
	}

	void SetVec2(const std::string& name, glm::vec2& v)
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(v));
	}

	void SetFloat(const std::string& name, float v)
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), v);
	}

	void SetInt(const std::string& name, int v)
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), v);
	}

	void CheckShaderError(unsigned int shaderId, const char* typeShader)
	{
		int success;
		char infoLog[512];
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
			std::cout << typeShader << " ERROR: " << infoLog << std::endl;
		}
	}
};

