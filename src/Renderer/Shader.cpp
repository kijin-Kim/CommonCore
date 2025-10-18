#include "Shader.h"

#include <filesystem>

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexCode = LoadShaderSource(vertexPath);
	std::string fragmentCode = LoadShaderSource(fragmentPath);

	unsigned int vertex = CompileShader(GL_VERTEX_SHADER, vertexCode);
	unsigned int fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentCode);

	id_ = glCreateProgram();
	glAttachShader(id_, vertex);
	glAttachShader(id_, fragment);
	glLinkProgram(id_);
	CheckCompileErrors(id_, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

std::string Shader::LoadShaderSource(const std::string& path)
{
	std::filesystem::path filepath = ASSET_DIR_PATH;
	filepath /= path;
	std::ifstream file(filepath);
	if (file.is_open())
	{
		std::stringstream buffer;
		buffer << file.rdbuf();
		return buffer.str();
	}

	std::cerr << "[Shader Error] Could not open file: " << filepath << std::endl;
	return "";
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	if (type == GL_VERTEX_SHADER)
		CheckCompileErrors(shader, "VERTEX");
	else
		CheckCompileErrors(shader, "FRAGMENT");

	return shader;
}

void Shader::Use() const
{
	glUseProgram(id_);
}

void Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(id_, name.c_str()), static_cast<int>(value));
}

void Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(id_, name.c_str()), 1, &value[0]);
}

void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(id_, name.c_str()), 1, &value[0]);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::CheckCompileErrors(unsigned int shader, const std::string& type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
			std::cerr << "[Shader Compile Error] (" << type << "):\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
			std::cerr << "[Shader Link Error] (" << type << "):\n" << infoLog << std::endl;
		}
	}
}