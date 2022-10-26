#include "utils.h"

auto shader_utils = ShaderUtils::Program{};

std::string readFile(const char* filePath) 
{
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);
	std::string line = "";
	while(!fileStream.eof())
	{
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

bool loadShaderProgram(const bool erase_if_program_registered = true)
{
    const std::string basicVertexShaderSource = readFile("../Shaders/vert.glsl");
    const std::string basicFragmentShaderSource = readFile("../Shaders/frag.glsl");

    if (!shader_utils.registerShader(ShaderUtils::Type::VERTEX_SHADER_TYPE, basicVertexShaderSource.c_str()))
    {
        error("failed to register the vertex shader...");
        return false;
    }

    if (!shader_utils.registerShader(ShaderUtils::Type::FRAGMENT_SHADER_TYPE, basicFragmentShaderSource.c_str()))
    {
        error("failed to register the fragment shader...");
        return false;
    }

    if (!shader_utils.registerProgram(erase_if_program_registered))
    {
        error("failed to register the program...");
        return false;
    }
    return true;
}