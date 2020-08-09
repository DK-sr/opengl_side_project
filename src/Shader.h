#pragma once
#include <string>

class Shader {
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	//Set uniforms
	void SetUniform4f(const std::string& name, float v0, float v1, float f2, float f3);
private:
	unsigned int GetUniformLocation(const std::string& name);

	std::string filepath_;
	unsigned int renderer_id_;
	//caching for uniforms
};