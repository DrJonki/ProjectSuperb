#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "NonCopyable.hpp"


namespace eng
{
	class Texture : private NonCopyable
	{
	public:

		Texture();

		~Texture();


		void loadFromFile(const char* filename, const bool smooth = false, const bool repeated = false);

		void destroy();

		const unsigned int getTextureId() const;

		operator unsigned int();

	private:

		unsigned int m_texture;
		bool m_smooth;
		bool m_repeated;
	};
}

#endif