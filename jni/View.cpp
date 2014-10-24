#include "View.hpp"
#include <cmath>


namespace eng
{
	const Transform& View::get3DViewMatrix(const gpm::Vector3F& position,
										   const gpm::Vector3F& lookAt,
										   const gpm::Vector3F& up)
	{
		static Transform vMatrix;

		gpm::Vector3F zAxis = position - lookAt;
		zAxis.normalize();

		gpm::Vector3F xAxis = up.getCrossProduct(zAxis);
		xAxis.normalize();

		gpm::Vector3F yAxis = zAxis.getCrossProduct(xAxis);


		vMatrix = Transform(xAxis.x,			 yAxis.x,			  zAxis.x,			   position.x,
							xAxis.y,			 yAxis.y,			  zAxis.y,			   position.y,
							xAxis.z,			 yAxis.z,			  zAxis.z,			   position.z,
							0.f,				 0.f,				  0.f,				   1.f);

		vMatrix.invert();

		return vMatrix;
	}
}