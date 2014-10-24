#ifndef VERTEX_HPP
#define VERTEX_HPP


namespace eng
{
	class Vertex
	{
	public:

		Vertex()
			: x(0.f),
			  y(0.f),
			  z(0.f),
			    u(0.f),
			    v(0.f),
				  r(1.f),
				  g(1.f),
				  b(1.f),
				  a(1.f)
		{}

		Vertex(const float _x, const float _y, const float _z,
			   const float _u = 0.f, const float _v = 0.f,
			   const float _r = 1.f, const float _g = 1.f, const float _b = 1.f, const float _a = 1.f)
			: x(_x),
			  y(_y),
			  z(_z),
			    u(_u),
			    v(_v),
				  r(_r),
				  g(_g),
				  b(_b),
				  a(_a)
		{}

		float x, y, z;
		float u, v;
		float r, g, b, a;
	};

}

#endif