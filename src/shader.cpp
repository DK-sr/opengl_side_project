#include "Shader.h"

Shader::Shader(const std::string& filepath)
	: filepath_(filepath), renderer_id_(0)
{
}

Shader::~Shader()
{
}

void Shader::Bind() const
{
}

void Shader::UnBind() const
{
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float f2, float f3)
{
}

unsigned int Shader::GetUniformLocation(const std::string& name)
{
	return 0;
}
