#include "Shader.hpp"
#include "Texture.hpp"

#include <Win32toAndroid.h>
#include <fstream>
#include <vector>
#include <iostream>



namespace eng
{

	Shader::Shader()
		: m_program(0)
	{}

	Shader::~Shader()
	{
		destroy();
	}



	bool Shader::createFromCode(const char* vertexCode, const char* fragmentCode)
	{
		if (m_program)
			destroy();

		m_program = glCreateProgram();

		if (vertexCode)
		{
			unsigned int shader = glCreateShader(GL_VERTEX_SHADER);

			glShaderSource(shader, 1, &vertexCode, NULL);
			glCompileShader(shader);

			int success;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				if (m_program)
				{
					glDeleteShader(shader);
					destroy();
				}

				//std::cout << "Failed to load vertex shader" << std::endl;
				return false;
			}

			glAttachShader(m_program, shader);
			glDeleteShader(shader);
		}

		if (fragmentCode)
		{
			unsigned int shader = glCreateShader(GL_FRAGMENT_SHADER);

			glShaderSource(shader, 1, &fragmentCode, NULL);
			glCompileShader(shader);

			int success;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		
			if (!success)
			{
				if (m_program)
				{
					glDeleteShader(shader);
					destroy();
				}

				//std::cout << "Failed to load fragment shader" << std::endl;
				return false;
			}

			glAttachShader(m_program, shader);
			glDeleteShader(shader);
		}

		glLinkProgram(m_program);
		int success;
		glGetProgramiv(m_program, GL_LINK_STATUS, &success);
		if (!success)
		{
			destroy();
			//std::cout << "Failed to link shader" << std::endl;

			return false;
		}

		return true;
	}

	bool Shader::createFromFile(const char* vertexFile, const char* fragmentFile)
	{
		std::vector<char> vcode;
		std::vector<char> fcode;

		if (vertexFile)
		{
			readFile(vertexFile, vcode);
		}
		if (fragmentFile)
		{
			readFile(fragmentFile, fcode);
		}

		return createFromCode(&vcode[0], &fcode[0]);
	}

	bool Shader::setUniform(const char* name, const Transform& transform)
	{
		use();

		if (m_program)
		{
			int location = getUniformLocation(name);

			if (location == -1) return false;
			
			else
			{
				glUniformMatrix4fv(location, 1, GL_FALSE, transform.getMatrix());
			}

			return true;
		}

		return false;
	}

	bool Shader::setUniform(const char* name, const float x, const float y)
	{
		use();

		if (m_program)
		{
			int location = getUniformLocation(name);

			if (location == -1) return false;
			
			else
			{
				glUniform2f(location, x, y);
			}

			return true;
		}

		return false;
	}

	bool Shader::setUniform(const char* name, const float x, const float y, const float z)
	{
		use();

		if (m_program)
		{
			int location = getUniformLocation(name);

			if (location == -1) return false;
			
			else
			{
				glUniform3f(location, x, y, z);
			}

			return true;
		}

		return false;
	}

	bool Shader::setUniform(const char* name, const float x, const float y, const float z, const float w)
	{
		use();

		if (m_program)
		{
			int location = getUniformLocation(name);

			if (location == -1) return false;
			
			else
			{
				glUniform4f(location, x, y, z, w);
			}

			return true;
		}

		return false;
	}

	bool Shader::setUniform(const char* name, const Texture* texture)
	{
		use();

		if (m_program)
		{
			int location = getUniformLocation(name);

			if (location == -1) return false;
			
			else
			{
				if (texture && texture->getTextureId())
					glUniform1i(location, static_cast<int>(texture->getTextureId()));
				else
					glUniform1i(location, 0);
			}

			return true;
		}

		return false;
	}

	bool Shader::use()
	{
		if (m_program)
			glUseProgram(m_program);
		else
			return false;

		return true;
	}

	bool Shader::unUse()
	{
		if (m_program)
		{
			glUseProgram(0);
			return true;
		}

		return false;
	}

	bool Shader::destroy()
	{
		if (m_program)
		{
			glDeleteProgram(m_program);
			return true;
		}

		return false;
	}
	
	unsigned int Shader::getProgram()
	{
		return m_program;
	}

	Shader::operator unsigned int()
	{
		return m_program;
	}

	bool Shader::readFile(const char* filename, std::vector<char>& buffer)
	{
		std::ifstream file;
		file.open(filename);

		if (file.good() && file.peek() != static_cast<int>(file.eof()))
		{
			buffer = std::vector<char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			buffer.push_back('\0');
			return true;
		}

		return false;
	}

	int Shader::getUniformLocation(const char* name)
	{
		int location = glGetUniformLocation(m_program, name);

		if (location == -1)
		{
			//std::cout << "Shader uniform location fail" << std::endl;
		}
		
		return location;
	}	

	int Shader::getAttributeLocation(const char* name)
	{
		int location = glGetAttribLocation(m_program, name);

		if (location == -1)
		{
			//std::cout << "Shader attribute location fail" << std::endl;
		}
		
		return location;
	}
}