#ifndef MY_EXCEPTION_H
#define MY_EXCEPTION_H

#include <exception>
#include <iostream>

namespace std
{

	namespace mystd
	{
		class exception:
			public std::exception
		{
			const char *_what;
		public:
			exception(const char *what):
				_what(what)
			{
			}
			
			virtual const char *what() const throw()
			{
				return _what;
			}
		};
	}
	
}

#endif
