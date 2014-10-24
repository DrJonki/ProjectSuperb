#ifndef RENDERTARGET_HPP
#define RENDERTARGET_HPP

#include "Camera.hpp"
#include "Shader.hpp"
#include "Singleton.hpp"
#include "Vertex.hpp"

#define rTarget eng::RenderTarget::getInstance()


namespace eng
{
	class GObject;
	class Transform;
	class Texture;

	class RenderTarget : public gpu::Singleton<eng::RenderTarget>
	{

		friend class gpu::Singleton<RenderTarget>;

	public:

		RenderTarget();


		void init();

		void clear(const float r = 0.f, const float g = 0.f, const float b = 0.f, const float a = 1.f);

		void draw(GObject& drawable);
		
		void draw(const unsigned int vbo,
				  const unsigned int vertexAmount,
				  const int type,
				  const eng::Transform& vTransform,
				  const eng::Texture* texture);

		void setCamera(Camera* const camera);


	private:

		Shader m_transformShader;

		Camera m_defaultCamera;
		Camera* m_camera;

	};
}

#endif