#include "RenderTarget.hpp"
#include "GObject.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include <Win32toAndroid.h>


namespace eng
{
	RenderTarget::RenderTarget()
		: m_camera(nullptr),
		  m_defaultCamera()
	{

	}

	void RenderTarget::init()
	{
		static const char gVertexShader[] = 
		"attribute vec3 a_vPosition;				\n"
		"attribute vec2 a_vTexCoords;				\n"
		"attribute vec4 a_vColor;					\n"

		"uniform mat4 u_MVmatrix;					\n"
		"uniform mat4 u_Pmatrix;					\n"

		"varying vec2 var_TexCoords;				\n"
		"varying vec4 var_Color;					\n"

		"void main()								\n"
		"{											\n"
		"	gl_Position = vec4(a_vPosition, 1.0);	\n"
		"	gl_Position *= u_MVmatrix;				\n"
		"	gl_Position *= u_Pmatrix;				\n"

		"	var_TexCoords = a_vTexCoords;			\n"
		"	var_Color = a_vColor;					\n"
		"}";
 
		static const char gFragmentShader[] = 
		"precision mediump float;					\n"

		"uniform sampler2D u_Texture;				\n"

		"varying vec2 var_TexCoords;				\n"
		"varying vec4 var_Color;					\n"

		"void main()								\n"
		"{											\n"
		"	gl_FragColor = texture2D(u_Texture, var_TexCoords);\n"
		"	gl_FragColor *= var_Color;				\n"
		"}";

		m_transformShader.createFromCode(gVertexShader, gFragmentShader);
	}


	void RenderTarget::clear(const float r, const float g, const float b, const float a)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(r, g, b, a);
		
		#ifndef ANDROID_FRAMEWORK
			glClearDepth(1); 
		#else 
			glClearDepthf(1); 
		#endif 
	}


	void RenderTarget::draw(GObject& drawable)
	{
		drawable.draw(*this);
	}


	void RenderTarget::draw(const unsigned int vbo,
							const unsigned int vertexAmount,
							const int type,
							const eng::Transform& vTransform,
							const Texture* texture)
	{
		m_transformShader.use();
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		Transform modelview;
		Transform projection;

		// Calculate the final transformation matrix
		if (!m_camera)
		{
			projection = m_defaultCamera.m_projectionTransform * vTransform;
		}
		else
		{
			if (m_camera->m_cameraMode == eng::Camera::two_dimensional)
				projection = m_camera->m_projectionTransform * vTransform;
			else
			{
				modelview = m_camera->m_viewTransform * vTransform;
				projection = m_camera->m_projectionTransform;
			}
		}

		// Set the depth buffer
		if (m_camera->m_cameraMode == eng::Camera::two_dimensional)
		{
			glDisable(GL_DEPTH_TEST);
		}
		else
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
		}

		// Set the blend functions
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Set face culling
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);

		// Set the texture
		if (texture && texture->getTextureId())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture->getTextureId());
			m_transformShader.setUniform("u_Texture", 0);
		}
		else
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
			m_transformShader.setUniform("u_Texture", 0);
		}

		// Set the shader uniforms and attributes
		m_transformShader.setUniform("u_MVmatrix", modelview);
		m_transformShader.setUniform("u_Pmatrix", projection);

		static int aPosition = m_transformShader.getAttributeLocation("a_vPosition");
		static int aUv = m_transformShader.getAttributeLocation("a_vTexCoords");
		static int aColor = m_transformShader.getAttributeLocation("a_vColor");
		
		// Position attribute
		glEnableVertexAttribArray(aPosition);
		glVertexAttribPointer(aPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		
		// Tex coords attribute
		glEnableVertexAttribArray(aUv);
		glVertexAttribPointer(aUv, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3));

		// Color attribute
		glEnableVertexAttribArray(aColor);
		glVertexAttribPointer(aColor, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 5));

		
		glDrawArrays(type, 0, vertexAmount);


		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDisableVertexAttribArray(aPosition);
		glDisableVertexAttribArray(aUv);
		glDisableVertexAttribArray(aColor);
	}

	void RenderTarget::setCamera(Camera* const camera)
	{
		m_camera = camera;
	}
}