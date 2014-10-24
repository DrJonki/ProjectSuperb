#ifndef NONCOPYABLE_HPP
#define NONCOPYABLE_HPP


namespace eng
{
	class NonCopyable
	{
	protected:

		NonCopyable(){};

	private:

		NonCopyable(const NonCopyable&);

		NonCopyable& operator =(const NonCopyable&);

	};
}

#endif