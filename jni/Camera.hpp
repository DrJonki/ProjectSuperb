#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Transform.hpp"
#include "Vector3.hpp"


namespace eng
{

	class Camera
	{

		friend class RenderTarget;

	public:

		enum Mode
		{
			two_dimensional,
			three_dimensional
		};


		Camera();


		void setViewMatrix(const Transform& matrix);


		void setProjectionMatrix(const Transform& matrix);


		void setCameraMode(const Mode mode);


		void rotate(const float x, const float y, const float z);

		void move(const float x, const float y, const float z);


		
		Transform m_viewTransform;
		Transform m_projectionTransform;



		Mode m_cameraMode;
	};
}

#endif