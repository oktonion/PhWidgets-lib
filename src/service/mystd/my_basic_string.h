#ifndef MY_BASIC_STRING_H
#define MY_BASIC_STRING_H

#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <cstdio>

namespace std
{

	template <typename T>
	T stoi(const char *s, int base = 10)
	{
		T num = 0;
		bool negative = false;
		static const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
		
		while(isspace(*s)) s++;
			
		if(*s == '-') {negative = true; s++;}
		else if(*s == '+') s++;
		
		if(*s == '0')
			{
				s++;
				if(*s == 'x' || *s == 'X')
					{
						if(base == 0) base = 16;
						else if(base != 16) return 0;
						s++;
					}
				else if(isdigit(*s))
					{
						if(base == 0) base = 8;
					}
				else if(*s == 0) return 0;
			}
		else if(*s == 0) return 0;
		else if(base == 0) base = 10;
		
		for(int digit; *s; s++)
			{
				const char *where = strchr(digits, tolower(*s));
				
				if(where == 0) break;
				digit = where - digits;
				if(digit >= base) break;
				
				num = num * base + digit;
			}
		
		if(negative) return -num;
		
		return num;
	}
	
	template <typename T>
	T stoi(const std::string &s, int base = 10)
	{
		return stoi<T>(s.c_str(), base);
	}
	
	int stoi(const std::string &s, int base = 10)
	{
		return stoi<int>(s.c_str(), base);
	}
	
	double stod(const std::string &s)
	{
		return strtod(s.c_str(), 0);
	}
	
	float stof(const std::string &s)
	{
		return strtof(s.c_str(), 0);
	}
	
	unsigned long stoul(const std::string &s, int base = 10)
	{
		return stoi<unsigned long>(s.c_str(), base);
	}
	
	std::string to_string(int value, int radix = 10)
	{
		static char buf[10] = {0};
		itoa(value, buf, radix);
		
		return buf;
	}
	
	std::string to_string(bool value)
	{
		if(value)
			return "true";
		return "false";
	}

	std::string to_string(double value)
	{
		static char buf[256] = {0};
		sprintf(buf, "%f", value);
		
		return buf;
	}

	std::string to_string(size_t value)
	{
		static char buf[30] = {0};
		sprintf(buf, "%u", value);
		
		return buf;
	}

	
}

#endif
