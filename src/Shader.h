#pragma once
#include <string>
#include <unordered_map>

struct ShaderProgramSource {
	std::string vertex_source;
	std::string fragment_source;
};

class Shader {
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//Set uniforms
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CreateShader(const std::string& vertex_shader, const std::string& fragment_shader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	int GetUniformLocation(const std::string& name);

	std::string filepath_;
	unsigned int renderer_id_;
	std::unordered_map<std::string, int> uniform_lcoation_cache_;
	//caching for uniforms
};