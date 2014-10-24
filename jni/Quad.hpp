#ifndef QUAD_HPP
#define QUAD_HPP

#include "GObject.hpp"


namespace eng
{
	class Quad : public GObject
	{
	public:

		Quad(const float posX,
			 const float posY,
			 const float sizeX,
			 const float sizeY,
			 const float posZ = 0.f,
			 const float sizeZ = 0.f);
	};
}

#endif