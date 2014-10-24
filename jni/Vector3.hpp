/////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Gene Pool C++ Library
 * Copyright (c) 2013 Joona Tiinanen
 *
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * This software is intended for private use only. Using this software
 * without authorization is strictly prohibited.
 *
 *
 * For any questions, contact joona_tiinanen@hotmail.com.
 *
*/
/////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef VECTOR3_HPP
#define VECTOR3_HPP

/////////////////////////////////////////////////////////////////////////////////////////////////

#include <cmath>

namespace gpm
{

	template<typename T>
	class Vector3
	{
	public:

		/// Default constructor.
		///
		/// Sets the values of all the member variables to 0.
		Vector3();

		/// Overloaded constructor for intialization.
		///
		/// Sets the values of the components according to the arguments.
		Vector3(const T _x, const T _y, const T _z);

		/// Overloaded constructor for initialization from another Vector3 of any type.
		///
		/// Copies the values from the given vector into this one.
		template<typename O>
		Vector3(Vector3<O>& vector);

		/// Destructor.
		~Vector3();


		/// Addition operation.
		///
		/// \return Reference to this vector, allowing chaining functions.
		Vector3& add(Vector3& vector);


		/// Subtraction operation.
		///
		/// \return Reference to this vector, allowing chaining functions.
		Vector3& subtract(Vector3& vector);


		/// Scaling operation.
		///
		/// \return Reference to this vector, allowing chaining functions.
		Vector3& scale(const T scalar);


		/// Division operation.
		///
		/// \return Reference to this vector, allowing chaining functions.
		Vector3& divide(const T divisor);


		/// Get the normalized vector.
		///
		/// \return Vector whose magnitude is 1.
		const Vector3 getNormal() const;


		/// Normalize the internal vector.
		///
		/// This causes the loss of the current values and replaces
		/// them with the normal of the vector.
		///
		/// \return Reference to this vector, allowing chaining functions.
		Vector3& normalize();


		/// Get the magnitude of the vector.
		///
		/// \return Magnitude of the vector.
		const T getMagnitude() const;


		/// Get the squared magnitude of the vector.
		///
		/// Used mainly for optimization reasons, as the rooting operation
		/// doesn't have to be performed here.
		///
		/// \return Magnitude^2 of the vector.
		const T getMagnitudeSq() const;


		/// Get the vector with the given magnitude applied.
		/// No changes are made to the internal values.
		///
		/// \return Vector2 with the given magnitude.
		const Vector3 getWithMagnitude(const T magnitude) const;


		/// Transform the vector to the given magnitude.
		/// This function will replace the existing vector with the new one.
		///
		/// \return Reference to this vector, allowing chaining functions.
		Vector3& setMagnitude(const T magnitude);


		/// Get the vector component product.
		/// No changes are made to the internal values.
		///
		/// \return Vector with the calculations applied.
		const Vector3 getComponentProduct(Vector3& vector) const;


		/// Transform this vector into its component product.
		/// This function will replace the existing vector with the new one.
		///
		/// \return Reference to this vector, allowing chaining functions.
		Vector3& setComponentProduct(Vector3& vector);


		/// Get the vector scalar product. This is the same as dot product.
		///
		/// \return Scalar product of the vector.
		const T getScalarProduct(const Vector3& vector) const;


		/// Get the vector cross product.
		/// No changes are made to the internal values.
		///
		/// \return Vector with the calculations applied.
		const Vector3 getCrossProduct(const Vector3& vector) const;


		/// Transform this vector into its component product.
		/// This function will replace the existing vector with the new one.
		///
		/// \return Reference to this vector, allowing chaining functions.
		Vector3& setCrossProduct(Vector3& vector);


	public:

		/// The x component.
		T x;

		/// The y component.
		T y;

		/// The z component.
		T z;

	}; // class Vector3


	// Operators

	// ADDITION
	// + (addition)
	template<typename T>
	const Vector3<T> operator +(Vector3<T>& left, Vector3<T>& right);
	// += (addition)
	template<typename T>
	Vector3<T>& operator +=(Vector3<T>& left, Vector3<T>& right);


	// SUBTRACTION
	// - (opposite vector)
	template<typename T>
	const Vector3<T> operator -(Vector3<T>& right);
	// - (subtraction)
	template<typename T>
	const Vector3<T> operator -(const Vector3<T>& left, const Vector3<T>& right);
	// -= (subtraction)
	template<typename T>
	Vector3<T>& operator -=(Vector3<T>& left, Vector3<T>& right);


	// MULTIPLICATION
	// * (multiplication)
	template<typename T>
	const Vector3<T> operator *(const T left, Vector3<T>& right);
	// * (multiplication)
	template<typename T>
	const Vector3<T> operator *(Vector3<T>& left, const T right);
	// *= (multiplication - scale)
	template<typename T>
	Vector3<T>& operator *=(Vector3<T>& left, const T right);
	// * (multiplication - scalar product)
	template<typename T>
	const T operator *(const Vector3<T>& left, const Vector3<T>& right);


	// DIVISION
	// / (division)
	template<typename T>
	const Vector3<T> operator /(Vector3<T>& left, const T right);
	// /= (division)
	template<typename T>
	Vector3<T>& operator /=(Vector3<T>& left, const T right);


	// MODULUS
	// % (modulus - cross product)
	template<typename T>
	const Vector3<T> operator %(Vector3<T>& left, Vector3<T>& right);
	// %= (modulus - cross product)
	template<typename T>
	Vector3<T>& operator %=(Vector3<T>& left, Vector3<T>& right);


	// EQUALITY
	// ==
	template<typename T>
	const bool operator ==(Vector3<T>& left, Vector3<T>& right);


	// INEQUALITY
	// !=
	template<typename T>
	const bool operator !=(Vector3<T>& left, Vector3<T>& right);



	// Non-member functions.

	/// Transform three vectors into their orthonormal basis.
	/// All internal values are replaced with new ones.
	///
	/// \return Void
	template<typename T>
	void setOrthonormalBasis(Vector3<T>& a, Vector3<T>& b, Vector3<T>& c);


	// Include implementation file.
	#include "Vector3.inl"


	// Typedefs of most common data types.
	typedef Vector3<int> Vector3I;
	typedef Vector3<float> Vector3F;
	typedef Vector3<unsigned int> Vector3UI;
	typedef Vector3<double> Vector3D;

} // namespace gpm

#endif