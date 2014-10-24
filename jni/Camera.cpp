#include "Camera.hpp"
#include "Projection.hpp"
#include "View.hpp"
#include "Vector3.hpp"
#include <cmath>


namespace eng
{
	Camera::Camera()
		: m_cameraMode(two_dimensional),
		  m_projectionTransform(eng::Projection::getOrthoMatrix(0, 0, 2, 2)),
		  m_viewTransform(eng::View::get3DViewMatrix(gpm::Vector3F(), gpm::Vector3F(0.f, 0.f, 1.f), gpm::Vector3F(0.f, 1.f, 0.f)))
	{
		m_viewTransform.loadIdentity();
	}


	void Camera::setViewMatrix(const Transform& matrix)
	{
		m_viewTransform = matrix;
	}


	void Camera::setProjectionMatrix(const Transform& matrix)
	{
		m_projectionTransform = matrix;
	}


	void Camera::setCameraMode(const Mode mode)
	{
		m_cameraMode = mode;
	}


	void Camera::rotate(const float x, const float y, const float z)
	{
		m_viewTransform.translate(400.f, 400.f, 0.f);
		m_viewTransform.rotate(x, y, z);
		m_viewTransform.translate(-400.f, -400.f, 0.f);
	}


	void Camera::move(const float x, const float y, const float z)
	{
		m_viewTransform.translate(x, y, z);
	}
}