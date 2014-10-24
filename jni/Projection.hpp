#ifndef PROJECTION_HPP
#define PROJECTION_HPP

#include "Transform.hpp"


namespace eng
{
	class Projection
	{
	public:

		static const Transform& getOrthoMatrix(const float centerX,
											   const float centerY,
											   const float sizeX,
											   const float sizeY);


		static const Transform& getPerspectiveMatrix(const float fovX,
													 const float aspectRatio,
													 const float zNear = 1.f,
													 const float zFar = 1000.f);

	};
}

#endif