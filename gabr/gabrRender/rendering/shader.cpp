#include "shader.h"
#include <log/logger.h>

namespace Gabr
{
	// Constructor
	Shader::Shader(const char* vertexShaderFile, const char* fragmentShaderFile)
	{
		mVertexShader = CreateShader(vertexShaderFile);
		mFragmentShader = CreateShader(fragmentShaderFile);

		mShaderProgramHandle = bgfx::createProgram(mVertexShader, mFragmentShader, true);
	}

	// Destructor
	Shader::~Shader()
	{
		bgfx::destroy(mShaderProgramHandle);
	}

	// Create shader by file
	bgfx::ShaderHandle Shader::CreateShader(const char* filename)
	{
		std::ifstream file(filename, std::ios::binary);
		if (!file)
		{
			Logger::Get().Log(LogSeverity::ERR, "Unable to open file " + std::string(filename));
		}
		file.seekg(0, std::ios::end);
		std::streamsize fileSize = file.tellg();
		file.seekg(0, std::ios::beg);

		std::vector<char> fileBuffer(fileSize);
		file.read(fileBuffer.data(), fileSize);
		bgfx::ShaderHandle shader = bgfx::createShader(bgfx::copy(fileBuffer.data(), fileSize));
		if (!bgfx::isValid(shader))
		{
			Logger::Get().Log(LogSeverity::ERR, "Unable to create shader" + std::string(filename));
		}
		file.close();
		return shader;
	}
}