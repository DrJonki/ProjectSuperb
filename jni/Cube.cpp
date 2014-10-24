#include <Cube.hpp>

namespace eng
{
	Cube::Cube(const float posX,
			   const float posY,
			   const float posZ,
			   const float sizeX,
			   const float sizeY,
			   const float sizeZ)
	{
		std::vector<Vertex> vertices;
		vertices.reserve(36);

		const float x = sizeX;
		const float y = sizeY;
		const float z = sizeZ;

		// Front
		vertices.push_back(Vertex(0.f, 0.f, 0.f, 0.f, 0.f));
		vertices.push_back(Vertex(0.f, y, 0.f, 0.f, 1.f));
		vertices.push_back(Vertex(x, 0.f, 0.f, 1.f, 0.f));
		vertices.push_back(Vertex(0.f, y, 0.f, 0.f, 1.f));
		vertices.push_back(Vertex(x, y, 0.f, 1.f, 1.f));
		vertices.push_back(Vertex(x, 0.f, 0.f, 1.f, 0.f));

		// Left
		vertices.push_back(Vertex(0.f, 0.f, z, 0.f, 0.f));
		vertices.push_back(Vertex(0.f, y, z, 0.f, 1.f));
		vertices.push_back(Vertex(0.f, 0.f, 0.f, 1.f, 0.f));
		vertices.push_back(Vertex(0.f, y, z, 0.f, 1.f));
		vertices.push_back(Vertex(0.f, y, 0.f, 1.f, 1.f));
		vertices.push_back(Vertex(0.f, 0.f, 0.f, 1.f, 0.f));

		// Rear
		vertices.push_back(Vertex(x, 0.f, z, 0.f, 0.f));
		vertices.push_back(Vertex(x, y, z, 0.f, 1.f));
		vertices.push_back(Vertex(0.f, 0.f, z, 1.f, 0.f));
		vertices.push_back(Vertex(x, y, z, 0.f, 1.f));
		vertices.push_back(Vertex(0.f, y, z, 1.f, 1.f));
		vertices.push_back(Vertex(0.f, 0.f, z, 1.f, 0.f));

		// Right
		vertices.push_back(Vertex(x, 0.f, 0.f, 0.f, 0.f));
		vertices.push_back(Vertex(x, y, 0.f, 0.f, 1.f));
		vertices.push_back(Vertex(x, 0.f, z, 1.f, 0.f));
		vertices.push_back(Vertex(x, y, 0.f, 0.f, 1.f));
		vertices.push_back(Vertex(x, y, z, 1.f, 1.f));
		vertices.push_back(Vertex(x, 0.f, z, 1.f, 0.f));

		// Top
		vertices.push_back(Vertex(0.f, y, 0.f, 0.f, 0.f));
		vertices.push_back(Vertex(0.f, y, z, 0.f, 1.f));
		vertices.push_back(Vertex(x, y, 0.f, 1.f, 0.f));
		vertices.push_back(Vertex(0.f, y, z, 0.f, 1.f));
		vertices.push_back(Vertex(x, y, z, 1.f, 1.f));
		vertices.push_back(Vertex(x, y, 0.f, 1.f, 0.f));

		// Bottom
		vertices.push_back(Vertex(0.f, 0.f, z, 0.f, 0.f));
		vertices.push_back(Vertex(0.f, 0.f, 0.f, 0.f, 1.f));
		vertices.push_back(Vertex(x, 0.f, z, 1.f, 0.f));
		vertices.push_back(Vertex(0.f, 0.f, 0.f, 0.f, 1.f));
		vertices.push_back(Vertex(x, 0.f, 0.f, 1.f, 1.f));
		vertices.push_back(Vertex(x, 0.f, z, 1.f, 0.f));


		m_position.x = posX;
		m_position.y = posY;
		m_position.z = posZ;

		
		prepare(vertices, triangles);
	}
}