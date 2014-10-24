#include "Projection.hpp"
#include <cmath>


namespace eng
{
	const Transform& Projection::getOrthoMatrix(const float centerX,
												const float centerY,
												const float sizeX,
												const float sizeY)
	{
		static Transform oMatrix;

		const float l = centerX - sizeX / 2;
		const float r = centerX + sizeX / 2;
		const float b = centerY - sizeY / 2;
		const float t = centerY + sizeY / 2;
		const float n = -1.f;
		const float f = 1.f;

		oMatrix = Transform(2 / (r - l), 0.f,		  0.f,			-((r + l) / (r - l)),
							0.f,		 2 / (t - b), 0.f,			-((t + b) / (t - b)),
							0.f,		 0.f,		  -2 / (f - n), -((f + n) / (f - n)),
							0.f,		 0.f,		  0.f,			1.f);

		return oMatrix;
	}


	const Transform& Projection::getPerspectiveMatrix(const float fovX,
													  const float aspectRatio,
													  const float zNear,
													  const float zFar)
	{
		static Transform pMatrix;

		const float pi = 3.14159265359f;

		const float xmax = zNear * std::tan(fovX * pi / 360.f);
		const float xmin = -xmax;
		const float ymax = xmax / aspectRatio;
		const float ymin = xmin / aspectRatio;

		pMatrix = Transform((2.f * zNear) / (xmax - xmin), 0.f,							  (xmax + xmin) / (xmax - xmin),	0.f,
							0.f,						   (2.f * zNear) / (ymax - ymin), (ymax + ymin) / (ymax - ymin),	0.f,
							0.f,						   0.f,							  -(zFar + zNear) / (zFar - zNear), -(2.f * zFar * zNear) / (zFar - zNear),
							0.f,						   0.f,							  -1.f,								0.f);

		return pMatrix;
	}  
}