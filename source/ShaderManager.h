/* Author: BAIRAC MIHAI */

#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <string>
#include <vector>

class GlobalConfig;

/*
 Manager for shader programs
 Can load: verte, geoemtry, tesselation, compute and fragment shaders
 Working with transform fedback is also possible!
*/

class ShaderManager
{
public:
	enum class UNIFORM_TYPE
	{
		UT_FLOAT_VEC_2 = 0,
		UT_FLOAT_VEC_3,
		UT_FLOAT_VEC_4,
		UT_FLOAT_MAT_2,
		UT_FLOAT_MAT_3,
		UT_FLOAT_MAT_4,
		UT_COUNT
	};

	//// Methods ////
	ShaderManager(void);
	ShaderManager(const std::string& i_Name);
	~ShaderManager(void);

	void Initialize(const std::string& i_Name);

	void BuildRenderingProgram(const std::string& i_VertexFileName, const std::string& i_FragmentFileName, const GlobalConfig& i_Config);
	void BuildRenderingProgram(const std::string& i_VertexFileName, const std::string& i_GeometryFileName, const std::string& i_FragmentFileName, const GlobalConfig& i_Config);
	void BuildComputeProgram(const std::string& i_ComputeFileName, const GlobalConfig& i_Config);

	void UseProgram(void) const;
	void UnUseProgram(void) const;

	unsigned int GetProgramID(void) const;
	int GetAttributeLocation(const char* i_pAttributeName) const;
	int GetUniformLocation(const char* i_pUniformName) const;

	void SetUniform(int i_UniformLocation, int i_UniformValue) const;
	void SetUniform(int i_UniformLocation, float i_UniformValue) const;
	void SetUniform(int i_UniformLocation, int i_ValueCount, const float* i_pUniformValue, ShaderManager::UNIFORM_TYPE i_UniformType) const;

	void SetupFragmentOutputStreams(unsigned short i_LayerCount, unsigned short i_Stride) const;

private:
	//// Methods ////
	bool CreateRenderingProgram(const std::string& i_VertexFileName, const std::string& i_FragmentFileName, const GlobalConfig& i_Config);
	bool CreateRenderingProgram(const std::string& i_VertexFileName, const std::string& i_GeometryFileName, const std::string& i_FragmentFileName, const GlobalConfig& i_Config);
	bool CreateComputeProgram(const std::string& i_ComputeFileName, const GlobalConfig& i_Config);

	bool CreateShader(const std::string& i_ShaderFileName, unsigned int i_ShaderType, const GlobalConfig& i_Config);
	bool LinkProgram(void);

	void Destroy(void);

	//// Variables ////
	std::string m_Name;

	unsigned int m_ShaderProgramID;
	unsigned int m_VertexShaderID;
	unsigned int m_GeometryShaderID; // since OpenGL 3.2, better in 4.1
	unsigned int m_FragmentShaderID;
	unsigned int m_ComputeShaderID; // since OpenGL 4.3

	bool m_UseStrictVerification;
};

#endif /* SHADER_MANAGER_H */
