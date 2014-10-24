#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <Vector3.hpp>


namespace eng
{
	class Transform
	{
	public:
	
		enum RotAxis
		{
			X,
			Y,
			Z
		};

	public:

		Transform();

		Transform(const float a1, const float a2, const float a3, const float a4,
				  const float b1, const float b2, const float b3, const float b4,
				  const float c1, const float c2, const float c3, const float c4,
				  const float d1, const float d2, const float d3, const float d4);

		~Transform();

		Transform& loadIdentity();

		const float* getMatrix() const;

		void invert();


		Transform& multiply(const Transform& transform);

		Transform& scale(const float x, const float y, const float z);

		Transform& translate(const float x, const float y, const float z);

		Transform& rotate(const float degrees, const RotAxis& axis);

		Transform& rotate(const float x, const float y, const float z);

	private:

		float m_matrix[16];
	};


	inline Transform operator *(const Transform& left, const Transform& right)
	{
		Transform transform = left;

		transform.multiply(right);

		return transform;
	}

	inline gpm::Vector3F operator*(const Transform& left, const gpm::Vector3F& right)
	{
		const float* m = left.getMatrix();
		const gpm::Vector3F v = right;

		return gpm::Vector3F(m[0] * v.x + m[1] * v.y + m[2] * v.z,
							 m[4] * v.x + m[5] * v.y + m[6] * v.z,
							 m[8] * v.x + m[9] * v.y + m[10] * v.z);
	}
}

#endif