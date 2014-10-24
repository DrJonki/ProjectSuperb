#ifndef GOBJECT_HPP
#define GOBJECT_HPP

#include "Transform.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Vector3.hpp"
#include "Vertex.hpp"
#include "Texture.hpp"
#include <vector>
#include <Win32toAndroid.h>

namespace eng
{
	class RenderTarget;

	enum PrimitiveType
	{
		points = GL_POINTS,
		lines = GL_LINES,
		line_strip = GL_LINE_STRIP,
		line_loop = GL_LINE_LOOP,
		triangles = GL_TRIANGLES,
		triangle_strip = GL_TRIANGLE_STRIP,
		triangle_fan = GL_TRIANGLE_FAN,
		null = GL_FALSE
	};


	class GObject
	{
	public:

		GObject();

		virtual ~GObject();


		void prepare(const std::vector<Vertex>& vertices, const PrimitiveType& ptype);

		void destroy();

		virtual void draw(const RenderTarget& target);

		void bindTexture(Texture* const texture);

		const Transform& getTransform();

		void setPosition(const float x, const float y, const float z = 0.f);

		void setScale(const float x, const float y, const float z = 1.f);

		void setRotation(const float x, const float y, const float z);

		void setOrigin(const float x, const float y, const float z = 0.f);

		void move(const float x, const float y, const float z = 0.f);

		void scale(const float x, const float y, const float z = 0.f);

		void rotate(const float x, const float y, const float z);

		void setColor(const float r, const float g, const float b, const float a);

		void resetTransform();

	private:

		void updateTransform();

		void updateData();

		unsigned int m_vbo;

		Texture* m_texture;
		
		PrimitiveType m_type;
		
		std::vector<Vertex> m_vertices;

		Transform m_transform;

		bool m_transformChanged;
		bool m_dataChanged;

	protected:
		
		gpm::Vector3F m_origin;
		gpm::Vector3F m_position;
		gpm::Vector3F m_scale;
		gpm::Vector3F m_rotation;
	};
}

#endif