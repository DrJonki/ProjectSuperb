#include "Transform.hpp"

#include <cmath>


namespace eng
{
	Transform::Transform()
	{
		loadIdentity();
	}

	Transform::Transform(const float a1, const float a2, const float a3, const float a4,
						 const float b1, const float b2, const float b3, const float b4,
						 const float c1, const float c2, const float c3, const float c4,
						 const float d1, const float d2, const float d3, const float d4)
	{
		m_matrix[0]  = a1; m_matrix[1]  = a2; m_matrix[2]  = a3; m_matrix[3]  = a4;
		m_matrix[4]  = b1; m_matrix[5]  = b2; m_matrix[6]  = b3; m_matrix[7]  = b4;
		m_matrix[8]  = c1; m_matrix[9]  = c2; m_matrix[10] = c3; m_matrix[11] = c4;
		m_matrix[12] = d1; m_matrix[13] = d2; m_matrix[14] = d3; m_matrix[15] = d4;
	}

	Transform::~Transform()
	{}



	Transform& Transform::loadIdentity()
	{
		m_matrix[0]  = 1.f; m_matrix[1]  = 0.f; m_matrix[2]  = 0.f; m_matrix[3]  = 0.f;
		m_matrix[4]  = 0.f; m_matrix[5]  = 1.f; m_matrix[6]  = 0.f; m_matrix[7]  = 0.f;
		m_matrix[8]  = 0.f; m_matrix[9]  = 0.f; m_matrix[10] = 1.f; m_matrix[11] = 0.f;
		m_matrix[12] = 0.f; m_matrix[13] = 0.f; m_matrix[14] = 0.f; m_matrix[15] = 1.f;

		return *this;
	}

	const float* Transform::getMatrix() const
	{
		return m_matrix;
	}

	void Transform::invert()
	{
		float* m = m_matrix;
		float inv[16];
		float det;

		inv[0] = m[5]  * m[10] * m[15] - 
				 m[5]  * m[11] * m[14] - 
				 m[9]  * m[6]  * m[15] + 
				 m[9]  * m[7]  * m[14] +
				 m[13] * m[6]  * m[11] - 
				 m[13] * m[7]  * m[10];

		inv[4] = -m[4]  * m[10] * m[15] + 
				 m[4]  * m[11] * m[14] + 
				 m[8]  * m[6]  * m[15] - 
				 m[8]  * m[7]  * m[14] - 
				 m[12] * m[6]  * m[11] + 
				 m[12] * m[7]  * m[10];

		inv[8] = m[4]  * m[9] * m[15] - 
				 m[4]  * m[11] * m[13] - 
				 m[8]  * m[5] * m[15] + 
				 m[8]  * m[7] * m[13] + 
				 m[12] * m[5] * m[11] - 
				 m[12] * m[7] * m[9];

		inv[12] = -m[4]  * m[9] * m[14] + 
				  m[4]  * m[10] * m[13] +
				  m[8]  * m[5] * m[14] - 
				  m[8]  * m[6] * m[13] - 
				  m[12] * m[5] * m[10] + 
				  m[12] * m[6] * m[9];

	    inv[1] = -m[1]  * m[10] * m[15] + 
		         m[1]  * m[11] * m[14] + 
			     m[9]  * m[2] * m[15] - 
				 m[9]  * m[3] * m[14] - 
				 m[13] * m[2] * m[11] + 
				 m[13] * m[3] * m[10];

		inv[5] = m[0]  * m[10] * m[15] - 
				 m[0]  * m[11] * m[14] - 
				 m[8]  * m[2] * m[15] + 
				 m[8]  * m[3] * m[14] + 
				 m[12] * m[2] * m[11] - 
	             m[12] * m[3] * m[10];

		inv[9] = -m[0]  * m[9] * m[15] + 
				 m[0]  * m[11] * m[13] + 
				 m[8]  * m[1] * m[15] - 
				 m[8]  * m[3] * m[13] - 
				 m[12] * m[1] * m[11] + 
				 m[12] * m[3] * m[9];

		inv[13] = m[0]  * m[9] * m[14] - 
				  m[0]  * m[10] * m[13] - 
				  m[8]  * m[1] * m[14] + 
				  m[8]  * m[2] * m[13] + 
				  m[12] * m[1] * m[10] - 
				  m[12] * m[2] * m[9];

		inv[2] = m[1]  * m[6] * m[15] - 
				 m[1]  * m[7] * m[14] - 
				 m[5]  * m[2] * m[15] + 
				 m[5]  * m[3] * m[14] + 
				 m[13] * m[2] * m[7] - 
				 m[13] * m[3] * m[6];

		inv[6] = -m[0]  * m[6] * m[15] + 
				 m[0]  * m[7] * m[14] + 
				 m[4]  * m[2] * m[15] - 
				 m[4]  * m[3] * m[14] - 
                 m[12] * m[2] * m[7] + 
				 m[12] * m[3] * m[6];

		inv[10] = m[0]  * m[5] * m[15] - 
				 m[0]  * m[7] * m[13] - 
				 m[4]  * m[1] * m[15] + 
				 m[4]  * m[3] * m[13] + 
				 m[12] * m[1] * m[7] - 
				 m[12] * m[3] * m[5];

		inv[14] = -m[0]  * m[5] * m[14] + 
				  m[0]  * m[6] * m[13] + 
				  m[4]  * m[1] * m[14] - 
				  m[4]  * m[2] * m[13] - 
				  m[12] * m[1] * m[6] + 
				  m[12] * m[2] * m[5];

		inv[3] = -m[1] * m[6] * m[11] + 
				 m[1] * m[7] * m[10] + 
				 m[5] * m[2] * m[11] - 
				 m[5] * m[3] * m[10] - 
				 m[9] * m[2] * m[7] + 
				 m[9] * m[3] * m[6];

		inv[7] = m[0] * m[6] * m[11] - 
				 m[0] * m[7] * m[10] - 
				 m[4] * m[2] * m[11] + 
				 m[4] * m[3] * m[10] + 
				 m[8] * m[2] * m[7] - 
				 m[8] * m[3] * m[6];

		inv[11] = -m[0] * m[5] * m[11] + 
				  m[0] * m[7] * m[9] + 
				  m[4] * m[1] * m[11] - 
				  m[4] * m[3] * m[9] - 
				  m[8] * m[1] * m[7] + 
				  m[8] * m[3] * m[5];

		inv[15] = m[0] * m[5] * m[10] - 
				  m[0] * m[6] * m[9] - 
				  m[4] * m[1] * m[10] + 
				  m[4] * m[2] * m[9] + 
				  m[8] * m[1] * m[6] - 
				  m[8] * m[2] * m[5];

		det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];


		if (det == 0)
			return;

		det = 1.0 / det;

		for (int i = 0; i < 16; i++)
			m_matrix[i] = inv[i] * det;
	}

	Transform& Transform::scale(const float x, const float y, const float z)
	{
		Transform scale(x, 0.f, 0.f, 0.f,
						0.f, y, 0.f, 0.f,
						0.f, 0.f, z, 0.f,
						0.f, 0.f, 0.f, 1.f);

		return multiply(scale);
	}

	Transform& Transform::translate(const float x, const float y, const float z)
	{
		Transform translation(1.f, 0.f, 0.f, x,
							  0.f, 1.f, 0.f, y,
							  0.f, 0.f, 1.f, z,
							  0.f, 0.f, 0.f, 1.f);

		return multiply(translation);
	}

	Transform& Transform::rotate(const float degrees, const RotAxis& axis)
	{
		float ra = degrees * 3.141592654f / 180.f;
		Transform rotation;
		
		using namespace std;

		if (axis == X)
		{
			rotation = Transform(1.f, 0.f, 0.f, 0.f,
								 0.f, cosf(ra), sinf(ra), 0.f,
								 0.f, -sinf(ra), cosf(ra), 0.f,
								 0.f, 0.f, 0.f, 1.f);
		}
		else if (axis == Y)
		{
			rotation = Transform(cosf(ra), 0.f, -sinf(ra), 0.f,
								 0.f, 1.f, 0.f, 0.f,
								 sinf(ra), 0.f, cosf(ra), 0.f,
								 0.f, 0.f, 0.f, 1.f);
		}
		else if (axis == Z)
		{
			rotation = Transform(cosf(ra), sinf(ra), 0.f, 0.f,
								 -sinf(ra), cosf(ra), 0.f, 0.f,
								 0.f, 0.f, 1.f, 0.f,
								 0.f, 0.f, 0.f, 1.f);
		}

		return multiply(rotation);
	}

	Transform& Transform::rotate(const float x, const float y, const float z)
	{
		if (x != 0.f)
			rotate(x, X);
		if (y != 0.f)
			rotate(y, Y);
		if (z != 0.f)
			rotate(z, Z);

		return *this;
	}

	// Private
	Transform& Transform::multiply(const Transform& transform)
	{
		const float* a = m_matrix;
		const float* b = transform.m_matrix;

        *this = Transform(a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12],
                            a[0] * b[1] + a[1] * b[5] + a[2] * b[9] + a[3] * b[13],
                              a[0] * b[2] + a[1] * b[6] + a[2] * b[10] + a[3] * b[14],
                                a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3] * b[15],
                          a[4] * b[0] + a[5] * b[4] + a[6] * b[8] + a[7] * b[12],
                            a[4] * b[1] + a[5] * b[5] + a[6] * b[9] + a[7] * b[13],
                              a[4] * b[2] + a[5] * b[6] + a[6] * b[10] + a[7] * b[14],
                                a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7] * b[15],
                          a[8] * b[0] + a[9] * b[4] + a[10] * b[8] + a[11] * b[12],
                            a[8] * b[1] + a[9] * b[5] + a[10] * b[9] + a[11] * b[13],
                              a[8] * b[2] + a[9] * b[6] + a[10] * b[10] + a[11] * b[14],
                                a[8] * b[3] + a[9] * b[7] + a[10] * b[11] + a[11] * b[15],
                          a[12] * b[0] + a[13] * b[4] + a[14] * b[8] + a[15] * b[12],
                            a[12] * b[1] + a[13] * b[5] + a[14] * b[9] + a[15] * b[13],
                              a[12] * b[2] + a[13] * b[6] + a[14] * b[10] + a[15] * b[14],
                                a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15]);

		return *this;
	}
}