#pragma once

#include <api.h>
#include <bgfx/bgfx.h>

namespace Gabr
{
	class GABR_API Shader
	{
	public:
		// Constructor
		Shader(const char* vertexShaderFile, const char* fragmentShaderFile);
		
		// Destructor
		~Shader();
		

		// Get shader program handle
		bgfx::ProgramHandle GetHandle() { return mShaderProgramHandle; }

	private:
		// Shader program handle
		bgfx::ProgramHandle mShaderProgramHandle;

		// Vertex shader handle
		bgfx::ShaderHandle	mVertexShader;
		
		// Fragment shader handle
		bgfx::ShaderHandle	mFragmentShader;


		// Create shader by file
		bgfx::ShaderHandle CreateShader(const char* filename);
	};
}