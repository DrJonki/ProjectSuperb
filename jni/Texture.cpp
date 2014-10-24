#include "Texture.hpp"
#include <Win32toAndroid.h>
#include <FileReader.h>
#include <stdlib.h>



namespace eng
{
	Texture::Texture()
		: m_texture(0),
		  m_smooth(false),
		  m_repeated(false)
	{

	}

	Texture::~Texture()
	{
		destroy();
	}


	void Texture::loadFromFile(const char* filename, const bool smooth, const bool repeated)
	{
		GLubyte* pixels;
	
		FileReader *FR = new FileReader(filename);
	
		unsigned char*buffer = (unsigned char*)malloc(sizeof(unsigned char)*4);

		FR->FileSeek(12,0);
		FR->ReadBytes(4,buffer);
		int sizex= buffer[0]+buffer[1]*256;
		int sizey= buffer[2]+buffer[3]*256;
		free(buffer);
	
		buffer = (unsigned char*)malloc(sizeof(unsigned char)*1);
		FR->FileSeek(16,0);
		FR->ReadBytes(1,buffer);
		int bpp = buffer[0];
		free(buffer);
	
		int datasize = sizex*sizey*bpp/8;
		pixels = (unsigned char*)malloc(sizeof(unsigned char)*datasize);
		unsigned char *Buffer = (unsigned char*)malloc(sizeof(unsigned char)*datasize);
	
		FR->FileSeek(18,0);
		FR->ReadBytes(datasize,Buffer);	
		for(int i = 0;i<datasize;i+=4)
		{
			pixels[i+0] = Buffer[i+2];
			pixels[i+1] = Buffer[i+1];
			pixels[i+2] = Buffer[i+0];
			pixels[i+3] = Buffer[i+3];
		}
		delete FR;

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenTextures(1,&m_texture);
		glActiveTexture(GL_TEXTURE0);


		glBindTexture(GL_TEXTURE_2D, m_texture);


		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sizex, sizey, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, pixels);
 
		// Set the filtering mode
		m_smooth = smooth;
		m_repeated = repeated;
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_smooth ? GL_LINEAR : GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_smooth ? GL_LINEAR : GL_NEAREST);
		
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_repeated ? GL_REPEAT : GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_repeated ? GL_REPEAT : GL_CLAMP_TO_EDGE);
	}

	void Texture::destroy()
	{
		if (m_texture)
			glDeleteTextures(1, &m_texture);
	}


	const unsigned int Texture::getTextureId() const
	{
		return m_texture;
	}

	Texture::operator unsigned int()
	{
		return m_texture;
	}
}