#include "GObject.hpp"
#include "RenderTarget.hpp"


namespace eng
{
	GObject::GObject()
		: m_texture(nullptr),
		  m_vbo(0),
		  m_origin(0.f, 0.f, 0.f),
		  m_scale(1.f, 1.f, 1.f),
		  m_rotation(0.f, 0.f, 0.f),
		  m_position(0.f, 0.f, 0.f),
		  m_type(null),
		  m_transformChanged(true),
		  m_dataChanged(true)
	{
		
	}

	GObject::~GObject()
	{
		destroy();
	}


	void GObject::prepare(const std::vector<Vertex>& vertices, const PrimitiveType& type)
	{
		m_vertices = vertices;
		m_type = type;

		glGenBuffers(1, &m_vbo);

		updateData();
		updateTransform();
	}

	void GObject::destroy()
	{
		if (m_vbo)
			glDeleteBuffers(1, &m_vbo);
	}

	void GObject::draw(const RenderTarget& target)
	{
		updateData();
		updateTransform();

		const int type = m_type;

		rTarget.draw(m_vbo, m_vertices.size(), type, m_transform, m_texture);
	}

	void GObject::bindTexture(Texture* const texture)
	{
		m_texture = texture;
	}

	const Transform& GObject::getTransform()
	{
		updateTransform();

		return m_transform;
	}


	void GObject::setPosition(const float x, const float y, const float z)
	{
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;

		m_transformChanged = true;
	}

	void GObject::setScale(const float x, const float y, const float z)
	{
		m_scale.x = x;
		m_scale.y = y;
		m_scale.z = z;

		m_transformChanged = true;
	}

	void GObject::setRotation(const float x, const float y, const float z)
	{
		m_rotation.x = x;
		m_rotation.y = y;
		m_rotation.z = z;

		m_transformChanged = true;
	}

	void GObject::setOrigin(const float x, const float y, const float z)
	{
		m_origin.x = x;
		m_origin.y = y;
		m_origin.z = z;

		m_transformChanged = true;
	}

	void GObject::move(const float x, const float y, const float z)
	{
		m_position.x += x;
		m_position.y += y;
		m_position.z += z;

		m_transformChanged = true;
	}

	void GObject::scale(const float x, const float y, const float z)
	{
		m_scale.x *= x;
		m_scale.y *= y;
		m_scale.z *= z;

		m_transformChanged = true;
	}

	void GObject::rotate(const float x, const float y, const float z)
	{
		m_rotation.x += x;
		m_rotation.y += y;
		m_rotation.z += z;

		m_transformChanged = true;
	}

	void GObject::setColor(const float r, const float g, const float b, const float a)
	{
		unsigned int size = m_vertices.size();

		for (unsigned int i = 0; i < size; i++)
		{
			m_vertices[i].r = r;
			m_vertices[i].g = g;
			m_vertices[i].b = b;
			m_vertices[i].a = a;
		}

		m_dataChanged = true;
	}

	void GObject::resetTransform()
	{
		m_rotation.x = 0;
		m_rotation.y = 0;
		m_rotation.z = 0;

		m_scale.x = 1;
		m_scale.y = 1;
		m_scale.z = 1;
		
		m_rotation.x = 0;
		m_rotation.y = 0;
		m_rotation.z = 0;
		
		m_origin.x = 0;
		m_origin.y = 0;
		m_origin.z = 0;


		m_transformChanged = true;
	}


	void GObject::updateTransform()
	{
		if (m_transformChanged)
		{
			m_transform.loadIdentity();

			m_transform.translate(m_position.x, m_position.y, m_position.z);
			m_transform.rotate(m_rotation.x, m_rotation.y, m_rotation.z);
			m_transform.scale(m_scale.x, m_scale.y, m_scale.z);
			m_transform.translate(-m_origin.x, -m_origin.y, -m_origin.z);


			m_transformChanged = false;
		}
	}

	void GObject::updateData()
	{
		if (m_dataChanged)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_DYNAMIC_DRAW);

			m_dataChanged = false;
		}
	}
}