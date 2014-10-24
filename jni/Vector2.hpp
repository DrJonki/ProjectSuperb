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

#ifndef VECTOR2_HPP
#define VECTOR2_HPP

/////////////////////////////////////////////////////////////////////////////////////////////////


namespace gpm
{

	template<typename T>
	class Vector2
	{
	public:

		/// Default constructor.
		///
		/// Sets the values of all the member variables to 0.
		Vector2();

		/// Overloaded constructor for intialization.
		///
		/// Sets the values of the components according to the arguments.
		Vector2(const T _x, const T _y);

		/// Overloaded constructor for initialization from another Vector2 of any type.
		///
		/// Copies the values from the given vector into this one.
		template<typename O>
		Vector2(Vector2<O>& vector);

		/// Destructor.
		~Vector2();


		/// Addition operation.
		///
		/// \return Reference to this vector, allowing chaining functions.
		Vector2& add(Vector2& vector);


		/// Subtraction operation.
		///
		/// \return Reference to this vector, allowing chaining functions.
		Vector2& subtract(Vector2& vector);


		/// Scaling operation.
		///
		/// \return Reference to this vector, allowing chaining functions.
		Vector2& scale(const T scalar);


		/// Division operation.
		///
		/// \return Reference to this vector, allowing chaining functions.
		Vector2& divide(const T divisor);


		/// Get the normalized vector.
		///
		/// \return Vector whose magnitude is 1.
		const Vector2 getNormal() const;


		/// Normalize the internal vector.
		///
		/// This causes the loss of the current values and replaces
		/// them with the normal of the vector.
		///
		/// \return Reference to this vector, allowing chaining functions.
		Vector2& normalize();


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
		const Vector2 getWithMagnitude(const T magnitude) const;


		/// Transform this vector to the given magnitude.
		/// This function will replace the existing vector with the new one.
		///
		/// \return Reference to this vector, allowing chaining functions.
		Vector2& setMagnitude(const T magnitude);


		/// Get the vector component product.
		/// No changes are made to the internal values.
		///
		/// \return Vector with the calculations applied.
		const Vector2 getComponentProduct(Vector2& vector) const;


		/// Transform this vector into its component product.
		/// This function will replace the existing vector with the new one.
		///
		/// \return Reference to this vector, allowing chaining functions.
		Vector2& setComponentProduct(Vector2& vector);


		/// Get the vector scalar product. This is the same as dot product.
		///
		/// \return Scalar product of the vector.
		const T getScalarProduct(Vector2& vector) const;


	public:

		/// The x component.
		T x;

		/// The y component.
		T y;

	}; // class Vector2


	// Operators

	// ADDITION
	// + (addition)
	template<typename T>
	const Vector2<T> operator +(Vector2<T>& left, Vector2<T>& right);
	// += (addition)
	template<typename T>
	Vector2<T>& operator +=(Vector2<T>& left, Vector2<T>& right);


	// SUBTRACTION
	// - (opposite vector)
	template<typename T>
	const Vector2<T> operator -(Vector2<T>& right);
	// - (subtraction)
	template<typename T>
	const Vector2<T> operator -(Vector2<T>& left, Vector2<T>& right);
	// -= (subtraction)
	template<typename T>
	Vector2<T>& operator -=(Vector2<T>& left, Vector2<T>& right);


	// MULTIPLICATION
	// * (multiplication)
	template<typename T>
	const Vector2<T> operator *(const T left, Vector2<T>& right);
	// * (multiplication)
	template<typename T>
	const Vector2<T> operator *(Vector2<T>& left, const T right);
	// *= (multiplication - scale)
	template<typename T>
	Vector2<T>& operator *=(Vector2<T>& left, const T right);
	// * (multiplication - scalar product)
	template<typename T>
	const T operator *(Vector2<T>& left, Vector2<T>& right);


	// DIVISION
	// / (division)
	template<typename T>
	const Vector2<T> operator /(Vector2<T>& left, const T right);
	// /= (division)
	template<typename T>
	Vector2<T>& operator /=(Vector2<T>& left, const T right);


	// EQUALITY
	// ==
	template<typename T>
	const bool operator ==(Vector2<T>& left, Vector2<T>& right);


	// INEQUALITY
	// !=
	template<typename T>
	const bool operator !=(Vector2<T>& left, Vector2<T>& right);


	// Include implementation file.
	#include "Vector2.inl"
	

	// Typedefs of most common data types.
	typedef Vector2<int> Vector2I;
	typedef Vector2<float> Vector2F;
	typedef Vector2<unsigned int> Vector2UI;
	typedef Vector2<double> Vector2D;

} // namespace gpm

#endif