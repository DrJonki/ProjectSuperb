#ifndef CUBE_HPP
#define CUBE_HPP

#include <GObject.hpp>


namespace eng
{
	class Cube : public GObject
	{
	public:

		Cube(const float posX,
			 const float posY,
			 const float posZ,
			 const float sizeX,
			 const float sizeY,
			 const float sizeZ);

	};
}

#endif