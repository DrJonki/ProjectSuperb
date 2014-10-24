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

#ifndef SINGLETON_HPP
#define SINGLETON_HPP

/////////////////////////////////////////////////////////////////////////////////////////////////

// Headers
#include "NonCopyable.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////


namespace gpu
{
	
	/////////////////////////////////////////////////////////////////////////////////////////////////
	///
	/// A template base class for maintaining a single instance of some other class.
	///
	/////////////////////////////////////////////////////////////////////////////////////////////////
	template<class C>
	class Singleton : private eng::NonCopyable
	{
	public:

		/// Get the instance.
		///
		/// Returns a reference to the local static instance of the templated class.
		///
		/// \return A reference to the singletoned class.
		static C& getInstance()
		{
			static C instance;

			return instance;
		}

	}; // class Singleton

} // namespace gpu

#endif