#ifndef STDEX_CODE_EXTENSIONS_H
#define STDEX_CODE_EXTENSIONS_H

#define forever for(;;)

#ifndef __has_feature
	#define __has_feature(x) 0 // Compatibility with non-clang compilers.
#endif

//#define STDEX_FORCE_CPP11_TYPES_SUPPORT //uncomment to force support of char16_t and char32_t in C++03

// Any compiler claiming C++11 supports, Visual C++ 2015 and Clang version supporting constexp
#if (__cplusplus >= 201103L || _MSC_VER >= 1900 || __has_feature(cxx_constexpr)) // C++ 11 implementation
#define STDEX_HAS_CPP11_SUPPORT
#define STDEX_HAS_CPP11_TYPES_SUPPORT
	namespace detail
	{
		template <typename T, size_t N>
		constexpr size_t my_countof(T const (&)[N]) noexcept
		{
			return N;
		}
	} // namespace detail
	#define countof(arr) detail::my_countof(arr)
	#define STATIC_ASSERT(expression, message) static_assert(expression, #message)
#else //no C++11 support
	#ifdef _MSC_VER
		#define STDEX_MSC_COMPILER_VERSION _MSC_VER
	#else
		#define STDEX_MSC_COMPILER_VERSION 0
	#endif
	#if (STDEX_MSC_COMPILER_VERSION < 1800)


	class nullptr_t
	{
	private:
		void *_padding;
		struct _nat { int _for_bool_; };

	public:
		nullptr_t() : _padding(0) { }
		nullptr_t(int _nat::*) : _padding(0) { }

		//operator int _nat::*() const { return 0; }
		   
		template<class T>
		inline operator T*() const // convertible to any type of null non-member pointer...
		{
			return 0;
		}

		/*template<class T, class C>
		inline operator T C::*() const   // or any type of null member pointer...
		{
			return 0;
		}*/

		template<typename T>
		inline bool operator==(T *val) { return val == static_cast<T*>(*this); }

		template<typename T>
		inline bool operator!=(T *val) { return val != static_cast<T*>(*this); }

		template<typename T>
		inline bool operator<(T *val) { return val != static_cast<T*>(*this); }

		template<typename T>
		inline bool operator<=(T *val) { return val == static_cast<T*>(*this); }

		template<typename T>
		inline bool operator>(T *val) { return false; }

		template<typename T>
		inline bool operator>=(T *val) { return val == static_cast<T*>(*this); }


		template<typename T>
		inline bool operator==(T val) { return val == 0; }

		template<typename T>
		inline bool operator!=(T val) { return val != 0; }

		template<typename T>
		inline bool operator<(T val) { return val != 0; }

		template<typename T>
		inline bool operator<=(T val) { return val == 0; }

		template<typename T>
		inline bool operator>(T val) { return false; }

		template<typename T>
		inline bool operator>=(T val) { return val == 0; }

		//friends:
		template<typename T>
		friend inline bool operator==(T *val, nullptr_t np) { return val == static_cast<T*>(np); }

		template<typename T>
		friend inline bool operator!=(T *val, nullptr_t np) { return val != static_cast<T*>(np); }

		template<typename T>
		friend inline bool operator<(T *val, nullptr_t np) { return false; }

		template<typename T>
		friend inline bool operator<=(T *val, nullptr_t np) { return val == static_cast<T*>(np); }

		template<typename T>
		friend inline bool operator>(T *val, nullptr_t np) { return val != static_cast<T*>(np); }

		template<typename T>
		friend inline bool operator>=(T *val, nullptr_t np) { return val == static_cast<T*>(np); }


		template<typename T>
		friend inline bool operator==(T val, nullptr_t np) { return val == 0; }

		template<typename T>
		friend inline bool operator!=(T val, nullptr_t np) { return val != 0; }

		template<typename T>
		friend inline bool operator<(T val, nullptr_t np) { return false; }

		template<typename T>
		friend inline bool operator<=(T val, nullptr_t np) { return val == 0; }

		template<typename T>
		friend inline bool operator>(T val, nullptr_t np) { return val != 0; }

		template<typename T>
		friend inline bool operator>=(T val, nullptr_t np) { return val == 0; }

	};

	//nullptr_t specialization:

	template<>
	inline bool nullptr_t::operator==(nullptr_t) { return true; }

	template<>
	inline bool nullptr_t::operator!=(nullptr_t) { return false; }

	template<>
	inline bool nullptr_t::operator<(nullptr_t) { return false; }

	template<>
	inline bool nullptr_t::operator<=(nullptr_t) { return true; }

	template<>
	inline bool nullptr_t::operator>(nullptr_t) { return false; }

	template<>
	inline bool nullptr_t::operator>=(nullptr_t) { return true; }

	template<>
	inline bool operator==(nullptr_t, nullptr_t) { return true; }

	template<>
	inline bool operator!=(nullptr_t, nullptr_t) { return false; }

	template<>
	inline bool operator<(nullptr_t, nullptr_t) { return false; }

	template<>
	inline bool operator<=(nullptr_t, nullptr_t) { return true; }

	template<>
	inline bool operator>(nullptr_t, nullptr_t) { return false; }

	template<>
	inline bool operator>=(nullptr_t, nullptr_t) { return true; }

#define nullptr nullptr_t(0)
	namespace detail {

		template <bool>
		struct StaticAssertion;

		template <>
		struct StaticAssertion<true>
		{
		}; // StaticAssertion<true>

		template<int i>
		struct StaticAssertionTest
		{
		}; // StaticAssertionTest<int>
	}

#define CONCATENATE(arg1, arg2)   CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2)  CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2)  arg1##arg2

#define STATIC_ASSERT(expression, message)\
  struct CONCATENATE(__static_assertion_at_line_, __LINE__)\
  {\
	detail::StaticAssertion<static_cast<bool>((expression))> CONCATENATE(CONCATENATE(CONCATENATE(STATIC_ASSERTION_FAILED_AT_LINE_, __LINE__), _WITH__), message);\
  };\
  typedef detail::StaticAssertionTest<sizeof(CONCATENATE(__static_assertion_at_line_, __LINE__))> CONCATENATE(__static_assertion_test_at_line_, __LINE__)

#define static_assert(expression, message) STATIC_ASSERT(expression, ERROR_MESSAGE_STRING)

	namespace std
	{
		template<class T, T Val>
			struct integral_constant
		{	// convenient template for integral constant types
			static const T value = Val;

			typedef const T value_type;
			typedef integral_constant<T, Val> type;

			operator value_type() const
			{	// return stored value
				return (value);
			}

			value_type operator()() const
			{	// return stored value
				return (value);
			}
		};

		typedef integral_constant<bool, true> true_type;
		typedef integral_constant<bool, false> false_type;

		template<bool Val>
		struct bool_constant:
			public integral_constant<bool, Val>
		{};

		template<bool Val>
		struct Cat_base
			: integral_constant<bool, Val>
		{	// base class for type predicates
		};

		template<class T>
		struct remove_const
		{	// remove top level const qualifier
			typedef T type;
		};

		template<class T>
		struct remove_const<const T *>
		{	// remove top level const qualifier
			typedef T *type;
		};

		template<class T>
		struct remove_const<const volatile T *>
		{	// remove top level const qualifier
			typedef volatile T *type;
		};

		// TEMPLATE CLASS remove_volatile
		template<class T>
		struct remove_volatile
		{	// remove top level volatile qualifier
			typedef T type;
		};

		template<class T>
		struct remove_volatile<volatile T*>
		{	// remove top level volatile qualifier
			typedef T *type;
		}; 

		// TEMPLATE CLASS remove_cv
		template<class T>
		struct remove_cv
		{	// remove top level const and volatile qualifiers
			typedef typename remove_const<typename remove_volatile<T>::type>::type
				type;
		};

		namespace detail
		{
			template <class T> struct is_floating_point : public false_type {};

			template<> struct is_floating_point<float> : public true_type {};
			template<> struct is_floating_point<double> : public true_type {};
			template<> struct is_floating_point<long double> : public true_type {};

			template <class T> struct is_integral : public false_type {};
			
			template<> struct is_integral<bool> : public true_type {};
			template<> struct is_integral<char> : public true_type {};
			template<> struct is_integral<wchar_t> : public true_type {};

#ifdef STDEX_FORCE_CPP11_TYPES_SUPPORT
	#include "types_ex.h"
			template<> struct is_integral<char16_t> : public true_type {};
			template<> struct is_integral<char32_t> : public true_type {};
#endif

			template<> struct is_integral<unsigned char> : public true_type {};
			template<> struct is_integral<unsigned short int> : public true_type {};
			template<> struct is_integral<unsigned int> : public true_type {};
			template<> struct is_integral<unsigned long int> : public true_type {};
			template<> struct is_integral<unsigned long long int> : public true_type {};

			template<> struct is_integral<signed char> : public true_type {};
			template<> struct is_integral<short int> : public true_type {};
			template<> struct is_integral<int> : public true_type {};
			template<> struct is_integral<long int> : public true_type {};
			template<> struct is_integral<long long int> : public true_type {};
		}

		
		template <class T> struct is_floating_point : public detail::is_floating_point<typename remove_cv<T>::type> {};
		
		template <class T>
		struct is_integral:
			   public true_type
		{
		};
		
		namespace detail
		{
			template<bool>
			struct SignUnsignChooser
			{
			};

			template<>
			struct SignUnsignChooser<true>//integral
			{
			  template<class T>
			  struct Signed :
					 public Cat_base<(typename remove_cv<T>::type)(-1) < (typename remove_cv<T>::type)(0)>
			  {
			  };

			  template<class T>
			  struct Unsigned:
					 public Cat_base<(typename remove_cv<T>::type)(0) < (typename remove_cv<T>::type)(-1)>
			  {
			  };
			};

			template<>
			struct SignUnsignChooser<false>//floating point
			{
			  template<class T>
			  struct Signed:
					 public is_floating_point<T>
			  {
			  };

			  template<class T>
			  struct Unsigned:
					 public false_type
			  {
			  };
			};
		}

		template <bool, typename T = void>
		struct enable_if
		{};

		template <typename T>
		struct enable_if<true, T> {
			typedef T type;
		};

		template<typename T, typename U>
		struct is_same:
			public false_type
		{
		};

		template<typename T>
		struct is_same<T, T>:
			public true_type//specialization
		{
		};

		template <typename T>
		struct is_const:
			public false_type
		{
		};

		template <typename T>
		struct is_const<const T*>:
			public true_type
		{
		};

		template <typename T>
		struct is_const<const volatile T*> :
			public true_type
		{
		};

		template< class T > 
		struct remove_reference 
		{ 
			typedef T type; 
		};
	
		template< class T > 
		struct remove_reference<T&> 
		{ 
			typedef T type; 
		};

		template<class T>
		struct is_signed
		{	// determine whether T is a signed type

			static const bool value = detail::SignUnsignChooser<is_integral<T>::value>::template Signed<T>::value;
		};

		template<class T>
		struct is_unsigned
		{	// determine whether T is an unsigned type
			static const bool value = detail::SignUnsignChooser<is_integral<T>::value>::template Unsigned<T>::value;
		};

		template<class T>
		struct is_void
			: false_type
		{	// determine whether T is void
		};

		template<>
		struct is_void<void>
			: true_type
		{	// determine whether T is void
		};

		template<class T>
		struct is_lvalue_reference
			: false_type
		{	// determine whether T is an lvalue reference
		};

		template<class T>
		struct is_lvalue_reference<T&>
			: true_type
		{	// determine whether T is an lvalue reference
		};

		template<class T>
		struct is_reference
			: Cat_base<is_lvalue_reference<T>::value
			>//|| is_rvalue_reference<_Ty>::value>
		{	// determine whether T is a reference
		};

		/*template<class T>
		struct remove_reference
		{	// remove reference
			typedef T type;
		};

		template<class T>
		struct remove_reference<T&>
		{	// remove reference
			typedef T type;
		};

		template<class T>
		struct remove_reference<T&&>
		{	// remove rvalue reference
			typedef T type;
		};*/
	}
	#endif
	#undef STDEX_MSC_COMPILER_VERSION

	#if _MSC_VER // Visual C++ fallback
		#define countof(arr) _countof(arr)
	#elif __cplusplus >= 199711L


		#if( // C++ 98 trick
		defined(__INTEL_COMPILER) || defined(__clang__) ||
		(defined(__GNUC__) && ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4)))
			template <typename T, std::size_t N>
			char(&COUNTOF_REQUIRES_ARRAY_ARGUMENT(T(&)[N]))[N];
			#define countof(x) sizeof(COUNTOF_REQUIRES_ARRAY_ARGUMENT(x))
		#endif
	#else
		#define countof(arr) sizeof(arr) / sizeof(arr[0])
	#endif
#endif

#endif//CODE_EXTENSIONS_H
