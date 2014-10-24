#ifndef SHADER_HPP
#define SHADER_HPP

#include "Transform.hpp"
#include "NonCopyable.hpp"
#include <vector>

namespace eng
{
	class Texture;


	class Shader : private NonCopyable
	{
	public:

		Shader();

		~Shader();


		bool createFromCode(const char* vertexCode, const char* fragmentCode);
		bool createFromFile(const char* vertexFile, const char* fragmentFile);
		bool destroy();

		bool setUniform(const char* name, const Transform& transform);
	
		bool setUniform(const char* name, const float x, const float y);

		bool setUniform(const char* name, const float x, const float y, const float z);

		bool setUniform(const char* name, const float x, const float y, const float z, const float w);

		bool setUniform(const char* name, const Texture* texture);

		bool use();

		bool unUse();

		unsigned int getProgram();

		operator unsigned int();

		int getUniformLocation(const char* name);
		
		int getAttributeLocation(const char* name);

	private:

		bool readFile(const char* filename, std::vector<char>& buffer);

		unsigned int m_program;
};

}

#endif