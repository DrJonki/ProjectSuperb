#ifndef VIEW_HPP
#define VIEW_HPP

#include "Transform.hpp"
#include "Vector3.hpp"


namespace eng
{
	class View
	{
	public:

		static const Transform& get3DViewMatrix(const gpm::Vector3F& position,
												const gpm::Vector3F& lookAt,
												const gpm::Vector3F& up);
	};
}

#endif