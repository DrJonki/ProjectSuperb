#include "Quad.hpp"


namespace eng
{
	Quad::Quad(const float posX,
			   const float posY,
			   const float sizeX,
			   const float sizeY,
			   const float posZ,
			   const float sizeZ)
	{
		std::vector<Vertex> vertices;
		vertices.reserve(6);

		// 1st triangle
		vertices.push_back(Vertex(0.f,	 0.f,	0.f, 0.f, 0.f));
		vertices.push_back(Vertex(0.f,	 sizeY, 0.f, 0.f, 1.f));
		vertices.push_back(Vertex(sizeX, 0.f,	0.f, 1.f, 0.f));

		// 2nd
		vertices.push_back(Vertex(vertices[1]));
		vertices.push_back(Vertex(sizeX, sizeX,	0.f, 1.f, 1.f));
		vertices.push_back(Vertex(vertices[2]));


		m_position.x = posX;
		m_position.y = posY;
		m_position.z = posZ;


		prepare(vertices, triangles);
	}
}