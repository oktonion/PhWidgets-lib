#ifndef CPP_PROPERTY_HPP
#define CPP_PROPERTY_HPP

#include "stdex/include/type_traits.hpp"

namespace cppproperties
{
	namespace detail
	{
		struct property_flag
		{
			enum e_property_flag
			{
				ro,
				wo,
				rw
			};
		};

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

		template<class T>
		struct remove_reference
		{
			typedef T type;
		};

		template<class T>
		struct remove_reference<T&>
		{
			typedef T type;
		};

		template<class T>
		struct remove_const
		{
			typedef T type;
		};

		template<class T>
		struct remove_const<const T>
		{
			typedef T type;
		};

		template <bool, class T>
		struct enable_if
		{
		private:
			struct enable_if_dummy;
		public:
			//typedef enable_if_dummy(&type)[1];
		};

		template <class T>
		struct enable_if<true, T>
		{
			typedef T type;
		};

		typedef char yes_type;
		struct no_type
		{
			char padding[8];
		};

		template<class T>
		T& declref();

		struct any { template <class T> any(T const&); };

		struct void_type {};

		template<int>
		struct sizeof_void_t
		{
			typedef void_type type;
		};

		template<class LhsT, class RhsT, class T = void_type>
		struct has_equal_test:
			false_type
		{};

		template<class LhsT, class RhsT>
		struct has_equal_test<LhsT, RhsT, 
			typename sizeof_void_t<sizeof(declref<LhsT>() ==/*op*/ declref<RhsT>())>::type>:
			true_type
		{};

		template<class LhsT, class RhsT, class T = void_type>
		struct has_not_equal_test:
			false_type
		{};

		template<class LhsT, class RhsT>
		struct has_not_equal_test<LhsT, RhsT, 
			typename sizeof_void_t<sizeof(declref<LhsT>() !=/*op*/ declref<RhsT>())>::type>:
			true_type
		{};

		template<class LhsT, class RhsT, class T = void_type>
		struct has_less_test:
			false_type
		{};

		template<class LhsT, class RhsT>
		struct has_less_test<LhsT, RhsT, 
			typename sizeof_void_t<sizeof(declref<LhsT>() </*op*/ declref<RhsT>())>::type>:
			true_type
		{};

		template <class LhsT, class RhsT>
		struct has_equal
		{
			static const bool value = 
				has_equal_test<LhsT, RhsT>::value;
		};

		template <class LhsT, class RhsT>
		struct has_not_equal
		{
			static const bool value = 
				has_not_equal_test<LhsT, RhsT>::value;
		};

		template <class LhsT, class RhsT>
		struct has_less
		{
			static const bool value = 
				has_less_test<LhsT, RhsT>::value;
		};

		template<unsigned N> struct priority_tag : priority_tag < N - 1 > {};
		template<> struct priority_tag<0> {};

		template<class T>
		yes_type is_convertable_tester(T, priority_tag<1>);
		template<class T>
		yes_type is_convertable_tester(any, priority_tag<0>);

		template<class FromT, class ToT>
		struct is_convertable
		{
			static const bool value = 
				sizeof(is_convertable_tester<ToT>(declref<FromT>(), priority_tag<1>())) == sizeof(yes_type);
		};

		template <typename ValueT, typename CValueT>
		struct flag_chooser_helper
		{
			static const property_flag::e_property_flag flag = property_flag::rw;
		};

		template <typename ValueT>
		struct flag_chooser_helper<ValueT, ValueT>
		{
			static const property_flag::e_property_flag flag = property_flag::ro;
		};

		template <typename ValueT>
		struct flag_chooser_helper<ValueT, void>
		{
			static const property_flag::e_property_flag flag = property_flag::wo;
		};

		template <>
		struct flag_chooser_helper<void, void>
		{
		};

		template<class T1>
		struct flag_chooser :
			public flag_chooser_helper<T1, const T1>
		{
		};

		template<class T1>
		struct flag_chooser<T1&> :
			public flag_chooser_helper<T1, const T1>
		{
		};

		template<class ValueT, class ParentT = void_type>
		struct property_info
		{
			typedef ValueT value_type;
			typedef typename remove_reference<typename remove_const<value_type>::type>::type & reference;
			typedef typename remove_reference<typename remove_const<value_type>::type>::type const & const_reference;

			typedef ParentT parent_t;
			typedef value_type(parent_t::* getter_t)()const;
			typedef void(parent_t::* setter_t)(value_type);

			static const getter_t &default_getter() { static getter_t getter = getter_t(0); return getter;}
			static const setter_t &default_setter() { static setter_t setter = setter_t(0); return setter;}
		};

		template<>
		struct property_info<void, void>
		{
			typedef void value_type;

			typedef void_type parent_t;
			typedef const int getter_t;
			typedef const int setter_t;

			static const getter_t &default_getter() { static getter_t getter = 0; return getter;}
			static const setter_t &default_setter() { static setter_t setter = 0; return setter;}
		};

		template<class ValueT>
		struct property_info<ValueT, void>
		{
			typedef ValueT value_type;
			typedef typename remove_reference<typename remove_const<value_type>::type>::type & reference;
			typedef typename remove_reference<typename remove_const<value_type>::type>::type const & const_reference;

			typedef value_type(*getter_t)();
			typedef void(*setter_t)(value_type);

			static const getter_t &default_getter() { static getter_t getter = getter_t(0); return getter;}
			static const setter_t &default_setter() { static setter_t setter = setter_t(0); return setter;}
		};

		template<class ParentT>
		struct property_info<void, ParentT> :
			public property_info<void, void>
		{ };

		template<class ParentT>
		struct property_info<void_type, ParentT> :
			public property_info<void, void>
		{ };

		template<class ValueT>
		struct property_info<ValueT, void_type> :
			public property_info<ValueT, void>
		{ };
	}

	template<class ValueT>
	struct Ipropertyr
	{
		typedef ValueT value_type;
		virtual value_type get() const = 0;
	};

	template<class ValueT>
	struct Ipropertyr<ValueT&>
	{
		typedef const ValueT & value_type;
		virtual value_type get() const = 0;

	protected:
		typedef typename detail::property_info<ValueT>::reference backdoor_type;
		virtual backdoor_type backdoor() = 0;
	};

	template<class ValueT>
	struct Ipropertyr<const ValueT&>
	{
		typedef const ValueT & value_type;
		virtual value_type get() const = 0;
	};

	template<class ValueT>
	struct Ipropertyr_without_backdoor:
		public Ipropertyr<ValueT>
	{};

	template<class ValueT>
	struct Ipropertyr_without_backdoor<ValueT&>:
		public Ipropertyr<const ValueT&>
	{};

	template<class ValueT>
	struct Ipropertyw
	{
		typedef ValueT value_type;
		virtual void set(ValueT) = 0;
	};

	template<class ValueT, 
		const detail::property_flag::e_property_flag Flag = 
			static_cast<const detail::property_flag::e_property_flag>(detail::flag_chooser<ValueT>::flag)>
	struct property_traits {};

	template<class ValueT = void,
		const detail::property_flag::e_property_flag Flag = 
			static_cast<const detail::property_flag::e_property_flag>(detail::flag_chooser<ValueT>::flag)>
	class property{};

	//property<void>:
	template<>
	class property<void, detail::property_flag::ro>:
		public detail::property_flag
	{
	public:
		typedef detail::property_flag flags;
	};

	template<>
	class property<void, detail::property_flag::wo>:
		public detail::property_flag
	{
	public:
		typedef detail::property_flag flags;
	};

	template<>
	class property<void, detail::property_flag::rw>:
		public detail::property_flag
	{
	public:
		typedef detail::property_flag flags;
	};

	//property<Value>:
	template<class ValueT>
	class property<ValueT, detail::property_flag::ro>: //ValueT == const...
		public virtual Ipropertyr<typename detail::property_info<ValueT>::const_reference>,
		public property_traits<typename detail::property_info<ValueT>::const_reference, detail::property_flag::ro>
	{
		typedef Ipropertyr_without_backdoor<typename detail::property_info<ValueT>::value_type> Ipropertyr_without_backdoor_type;
	public:
		typedef typename detail::property_info<ValueT>::value_type value_type;
		typedef typename detail::property_info<ValueT>::reference reference;
		typedef typename detail::property_info<ValueT>::const_reference const_reference;

		template<class ParentT, typename detail::property_info<ValueT, ParentT>::getter_t Getter>
		class bind:
			public virtual Ipropertyr_without_backdoor_type,
			public property_traits<typename Ipropertyr_without_backdoor_type::value_type, detail::property_flag::ro>
		{
			typedef typename detail::remove_const<ParentT>::type const parent_type;
			
		public:
			typedef typename Ipropertyr_without_backdoor_type::value_type value_type;
			typedef typename detail::property_info<ValueT, ParentT>::reference reference;
			typedef typename detail::property_info<ValueT, ParentT>::const_reference const_reference;

			inline
			bind(parent_type *parent) :
				_obj(parent)
			{}

			inline
			value_type get() const
			{
				return (_obj->*Getter)();
			}

			inline
			operator value_type() const { return get(); }
			
			inline
			value_type operator()(void) const { return get(); }

		private:
			parent_type *_obj;
			
			bind(const bind &rhs);

			bind &operator=(value_type);
			bind &operator=(bind const &);

			
		};

		template<typename detail::property_info<ValueT, void>::getter_t Getter>
		class bind_static:
			public virtual Ipropertyr_without_backdoor_type,
			public property_traits<typename Ipropertyr_without_backdoor_type::value_type, detail::property_flag::ro>
		{
		public:
			typedef typename Ipropertyr_without_backdoor_type::value_type value_type;
			typedef typename detail::property_info<ValueT>::reference reference;
			typedef typename detail::property_info<ValueT>::const_reference const_reference;

			bind_static()
			{}

			inline 
			value_type get() const
			{
				return (*Getter)();
			}

			inline 
			operator value_type() const { return get(); }
			
			inline 
			value_type operator()(void) const { return get(); }

		private:
			
			bind_static(const bind_static &rhs);

			inline 
			bind_static &operator=(value_type);
			inline 
			bind_static &operator=(bind_static const &);

			
		};

		property(value_type value) :
			_val(value)
		{}

		inline 
		const_reference get() const
		{
			return _val;
		}

		inline 
		operator const_reference() const { return get(); }

		inline 
		const_reference operator()(void) const { return get(); }

	private:

		value_type _val;

		property &operator=(const_reference);
		property &operator=(property const &);

		
	};


	template<class ValueT>
	class property<ValueT, detail::property_flag::rw>: //ValueT != const...
		public virtual Ipropertyr<typename detail::property_info<ValueT>::reference>,
		public Ipropertyw<typename detail::property_info<ValueT>::value_type>,
		public property_traits<typename detail::property_info<ValueT>::reference, detail::property_flag::rw>
	{
	public:
		typedef typename detail::property_info<ValueT>::value_type value_type;
		typedef typename detail::property_info<ValueT>::reference reference;
		typedef typename detail::property_info<ValueT>::const_reference const_reference;

		template<class ParentT, typename detail::property_info<ValueT, ParentT>::getter_t Getter, typename detail::property_info<ValueT, ParentT>::setter_t Setter>
		class bind:
			public virtual Ipropertyr<typename detail::property_info<ValueT>::value_type>,
			public Ipropertyw<typename detail::property_info<ValueT>::value_type>,
			public property_traits<typename detail::property_info<ValueT>::value_type, detail::property_flag::rw>
		{
			typedef typename detail::remove_const<ParentT>::type parent_type;
		public:
			typedef typename detail::property_info<ValueT>::value_type value_type;
			typedef typename detail::property_info<ValueT>::reference reference;
			typedef typename detail::property_info<ValueT>::const_reference const_reference;
			
			bind(parent_type *parent) :
				_obj(parent)
			{}

			bind(parent_type *parent, value_type value) :
				_obj(parent)
			{
				set(value);
			}

			inline
			void set(value_type value)
			{
				(_obj->*Setter)(value);
			}

			inline
			value_type get() const
			{
				return (_obj->*Getter)();
			}

			inline
			operator value_type() const { return get(); }

			inline
			bind &operator=(value_type value) { set(value); return *this; }

			inline
			value_type operator()(void) const { return get(); }

			inline
			void operator()(value_type value) { set(value); }

		private:
			parent_type *_obj;
			
			bind(const bind &);	

			value_type backdoor() {return (_obj->*Getter)();}
		};

		property()
		{}

		property(value_type value) :
			_val(value)
		{}

		inline 
		void set(value_type value)
		{
			_val = value;
		}

		inline 
		const_reference get() const
		{
			return _val;
		}

		inline 
		property &operator=(value_type value) { set(value); return *this; }

		inline 
		operator const_reference() const { return get(); }
		
		inline 
		const_reference operator()(void) const { return get(); }

		inline 
		void operator()(value_type value) { set(value); }

	private:

		value_type _val;

		typedef Ipropertyr<typename detail::property_info<ValueT>::reference> Ipropertyr_base;
		
		typename
		Ipropertyr_base::backdoor_type backdoor() {return _val;}
	};

	template<class ValueT>
	class property<ValueT, detail::property_flag::wo>: //ValueT != const...
		public Ipropertyw<typename detail::property_info<ValueT>::value_type>,
		public property_traits<typename detail::property_info<ValueT>::value_type, detail::property_flag::wo>
	{
	public:
		typedef typename detail::property_info<ValueT>::value_type value_type;
		typedef typename detail::property_info<ValueT>::reference reference;
		typedef typename detail::property_info<ValueT>::const_reference const_reference;

		template<class ParentT, typename detail::property_info<ValueT, ParentT>::setter_t Setter>
		class bind:
			public Ipropertyw<typename detail::property_info<ValueT>::value_type>,
			public property_traits<typename detail::property_info<ValueT>::value_type, detail::property_flag::wo>
		{
			typedef typename detail::remove_const<ParentT>::type parent_type;
		public:
			typedef typename detail::property_info<ValueT>::value_type value_type;
			typedef typename detail::property_info<ValueT>::reference reference;
			typedef typename detail::property_info<ValueT>::const_reference const_reference;

			bind(parent_type *parent) :
				_obj(parent)
			{}

			bind(parent_type *parent, value_type value) :
				_obj(parent)
			{
				set(value);
			}

			inline 
			void set(value_type value)
			{
				(_obj->*Setter)(value);
			}
			
			inline 
			bind &operator=(value_type value) { set(value); return *this; }

			inline 
			void operator()(value_type value) { set(value); }
		private:
			parent_type *_obj;
			
			bind(const bind &);
		};

		property()
		{}

		property(value_type value) :
			_val(value)
		{}

		inline 
		void set(value_type value)
		{
			_val = value;
		}
		
		inline 
		property &operator=(value_type value) { set(value); return *this; }

		inline 
		void operator()(value_type value) { set(value); }

		//custom comparison operators for property to make it useful:
		template<class OtherValueT>
		typename 
		detail::enable_if<
			(
				detail::has_equal<value_type, OtherValueT>::value ||
				(
					detail::is_convertable<OtherValueT, value_type>::value &&
					detail::has_equal<value_type, value_type>::value
				)
			)
			,
			bool
		>::type operator==(const OtherValueT &other) const {return _val == other;}

		typename 
		detail::enable_if<
			detail::has_equal<value_type, value_type>::value,
			bool
		>::type operator==(const property &other) const {return _val == other._val;}

		template<class OtherValueT>
		typename 
		detail::enable_if<
			(
				detail::has_not_equal<value_type, OtherValueT>::value ||
				(
					detail::is_convertable<OtherValueT, value_type>::value &&
					detail::has_not_equal<value_type, value_type>::value
				)
			)
			,
			bool
		>::type operator!=(const OtherValueT &other) const {return _val != other;}

		typename 
		detail::enable_if<
			detail::has_not_equal<value_type, value_type>::value,
			bool
		>::type operator!=(const property &other) const {return _val != other._val;}

		template<class OtherValueT>
		typename 
		detail::enable_if<
			(
				detail::has_less<value_type, OtherValueT>::value ||
				(
					detail::is_convertable<OtherValueT, value_type>::value &&
					detail::has_less<value_type, value_type>::value
				)
			)
			,
			bool
		>::type operator<(const OtherValueT &other) const {return _val < other;}

		typename 
		detail::enable_if<
			detail::has_less<value_type, value_type>::value,
			bool
		>::type operator<(const property &other) const {return _val < other._val;}
		
	private:

		value_type _val;
	};

	template<class ValueT, class OtherValueT>
	typename 
	detail::enable_if<
		(
			detail::has_equal<ValueT, OtherValueT>::value ||
			(
				detail::is_convertable<OtherValueT, ValueT>::value &&
				detail::has_equal<ValueT, ValueT>::value
			)
		)
		,
		bool
	>::type operator==(
		const Ipropertyr<ValueT> &lhs, 
		const OtherValueT &rhs)
	{
		return lhs.get() == rhs;
	}

	template<class ValueT, class OtherValueT>
	typename 
	detail::enable_if<
		(
			detail::has_not_equal<ValueT, OtherValueT>::value ||
			(
				detail::is_convertable<OtherValueT, ValueT>::value &&
				detail::has_not_equal<ValueT, ValueT>::value
			)
		)
		,
		bool
	>::type operator!=(
		const Ipropertyr<ValueT> &lhs, 
		const OtherValueT &rhs)
	{
		return lhs.get() != rhs;
	}

	template<class ValueT, class OtherValueT>
	typename 
	detail::enable_if<
		(
			detail::has_less<ValueT, OtherValueT>::value ||
			(
				detail::is_convertable<OtherValueT, ValueT>::value &&
				detail::has_less<ValueT, ValueT>::value
			)
		)
		,
		bool
	>::type operator<(
		const Ipropertyr<ValueT> &lhs, 
		const OtherValueT &rhs)
	{
		return lhs.get() < rhs;
	}

	/*template<class ValueT, class OtherValueT>
	typename 
	detail::enable_if<
		!detail::has_equal<OtherValueT, property<ValueT, property<>::wo> >::value &&
		(
			detail::has_equal<OtherValueT, ValueT>::value ||
			(
				detail::is_convertable<ValueT, OtherValueT>::value &&
				detail::has_equal<OtherValueT, OtherValueT>::value
			)
		)
		,
		bool
	>::type operator==(
		const OtherValueT &lhs, 
		const property<ValueT, property<>::wo> &rhs)
	{
		return lhs == rhs._val;
	}

	template<class ValueT, class OtherValueT>
	typename 
	detail::enable_if<
		!detail::has_not_equal<OtherValueT, property<ValueT, property<>::wo> >::value &&
		(
			detail::has_not_equal<OtherValueT, ValueT>::value ||
			(
				detail::is_convertable<ValueT, OtherValueT>::value &&
				detail::has_not_equal<OtherValueT, OtherValueT>::value
			)
		)
		,
		bool
	>::type operator!=(
		const OtherValueT &lhs,
		const property<ValueT, property<>::wo> &rhs)
	{
		return lhs != rhs._val;
	}

	template<class ValueT, class OtherValueT>
	typename 
	detail::enable_if<
		!detail::has_less<OtherValueT, property<ValueT, property<>::wo> >::value &&
		(
			detail::has_less<OtherValueT, ValueT>::value ||
			(
				detail::is_convertable<ValueT, OtherValueT>::value &&
				detail::has_less<OtherValueT, OtherValueT>::value
			)
		)
		,
		bool
	>::type operator<(
		const OtherValueT &lhs, 
		const property<ValueT, property<>::wo> &rhs)
	{
		return lhs < rhs._val;
	}*/

	namespace detail
	{
		template<class Enable, class T = void_type>
		struct enable_if_type
		{ typedef T type; };

		template<class T, class Enabled = void_type>
		struct has_size_type
		{ 
			static const bool value = false;
		};
		
		template<class T>
		struct has_size_type<
			T, 
			typename enable_if_type<typename T::size_type>::type
		>
		{ 
			static const bool value = true;
		};

		template<class T, class Enabled = void_type>
		struct has_const_iterator
		{ 
			static const bool value = false;
		};
		
		template<class T>
		struct has_const_iterator<
			T, 
			typename enable_if_type<typename T::const_iterator>::type
		>
		{ 
			static const bool value = true;
		};

		template<class T, class Enabled = void_type>
		struct has_iterator
		{ 
			static const bool value = false;
		};
		
		template<class T>
		struct has_iterator<
			T, 
			typename enable_if_type<typename T::iterator>::type
		>
		{ 
			static const bool value = true;
		};

		template<class T, bool Enabled>
		struct size_property_trait_impl
		{ };
		
		template<class T>
		struct size_property_trait_impl<T, true>:
			public virtual Ipropertyr<T>
		{ 
		private:
			typedef typename remove_reference<T>::type clear_type;
			typedef Ipropertyr<T> base_type;
			using base_type::get;
		public:
			typedef typename clear_type::size_type size_type;
			
			size_type size() const
			{
				return get().size();
			}
		};

		template<class T, bool Enabled>
		struct const_begin_end_property_trait_impl
		{ };
		
		template<class T>
		struct const_begin_end_property_trait_impl<T, true>:
			public virtual Ipropertyr<T>
		{ 
		private:
			typedef typename remove_reference<T>::type clear_type;
			typedef Ipropertyr<T> base_type;
			using base_type::get;
		public:
			typedef typename clear_type::const_iterator const_iterator;
			
			const_iterator begin() const
			{
				return get().begin();
			}

			const_iterator end() const
			{
				return get().end();
			}

			const_iterator cbegin() const
			{
				return get().begin();
			}

			const_iterator cend() const
			{
				return get().end();
			}
		};

		template<class T, bool Enabled>
		struct begin_end_property_trait_impl
		{ };
		
		template<class T>
		struct begin_end_property_trait_impl<T, true>:
			public virtual Ipropertyr<T>
		{ 
		private:
			typedef typename remove_reference<T>::type clear_type;
			typedef Ipropertyr<T> base_type;
			using base_type::backdoor;
		public:
			typedef typename clear_type::iterator iterator;
			
			iterator begin()
			{
				return backdoor().begin();
			}

			iterator end()
			{
				return backdoor().end();
			}
		};

		template<class T, bool HasImpl, bool HasConstImpl>
		struct begin_end_property_trait_impl1
		{ };

		template<class T>
		struct begin_end_property_trait_impl1<T, true, false>:
			begin_end_property_trait_impl<T, true>
		{ };

		template<class T>
		struct begin_end_property_trait_impl1<T, false, true>:
			const_begin_end_property_trait_impl<T, true>
		{ };

		template<class T>
		struct begin_end_property_trait_impl1<T, true, true>:
			const_begin_end_property_trait_impl<T, true>,
			begin_end_property_trait_impl<T, true>
		{ 
			using const_begin_end_property_trait_impl<T, true>::begin;
			using const_begin_end_property_trait_impl<T, true>::end;
			using begin_end_property_trait_impl<T, true>::begin;
			using begin_end_property_trait_impl<T, true>::end;
		};

		template<class T>
		struct size_property_trait:
			size_property_trait_impl<T, has_size_type<typename remove_reference<T>::type>::value>
		{ };

		template<class T>
		struct const_begin_end_property_trait:
			const_begin_end_property_trait_impl<T, has_const_iterator<typename remove_reference<T>::type>::value>
		{ };

		template<class T>
		struct begin_end_property_trait:
			begin_end_property_trait_impl1<T, has_iterator<typename remove_reference<T>::type>::value, has_const_iterator<typename remove_reference<T>::type>::value>
		{ };
	}

	template<class ValueT>
	struct property_traits<ValueT, property<>::ro>:
		detail::size_property_trait<ValueT>,
		detail::const_begin_end_property_trait<ValueT>
	{ };

	template<class ValueT>
	struct property_traits<ValueT, property<>::rw>:
		detail::size_property_trait<ValueT>,
		detail::begin_end_property_trait<ValueT>
	{ };


	/*template<typename ValueT, typename ParentT = void, typename detail::get_parent_func<ValueT, ParentT>::getter_t Getter = 0, typename detail::get_parent_func<ValueT, ParentT>::setter_t Setter = 0,
		const detail::property_flag::e_property_flag Flag = (const detail::property_flag::e_property_flag)(detail::flag_chooser<ValueT>::flag)
				>

	class property:
				public detail::property_base<ValueT, ParentT, detail::property_flag::e_property_flag(Flag)>
	{
	public:

		property(ParentT *parent) :
			detail::property_base<ValueT, ParentT, Flag>(parent, Getter, Setter)
		{}

	private:

		property(const property &rhs);
	};


	//property<void>:
	template<detail::property_flag::e_property_flag Flag>
	class property<void, void, 0, 0, Flag>
	{
	public:
		typedef detail::property_flag flags;
	};


	//property<Value>:
	template<typename ValueT>
	class property<ValueT, void, 0, 0, detail::property_flag::r>//ValueT == const...
	{
	public:

		property(ValueT const &value) :
			_val(value)
		{}

		inline const ValueT &get() const
		{
			return _val;
		}

		operator const ValueT&() const { return get(); }

	private:

		const ValueT _val;

		property &operator=(ValueT const &);
	};


	template<typename ValueT>
	class property<ValueT, void, 0, 0, detail::property_flag::rw>//ValueT != const...
	{
	public:

		property()
		{}

		property(const ValueT &value) :
			_val(value)
		{}

		inline void set(ValueT const &value)
		{
			_val = value;
		}

		inline const ValueT &get() const
		{
			return _val;
		}

		property &operator=(ValueT const &value) { set(value); return *this; }

		operator const ValueT&() const { return get(); }

	private:

		ValueT _val;

	};

	template<typename ValueT>
	class property<ValueT, void, 0, 0, detail::property_flag::w>//ValueT != const...
	{
	public:

		property()
		{}

		property(const ValueT &value) :
			_val(value)
		{}

		inline void set(ValueT const &value)
		{
			_val = value;
		}

		property &operator=(ValueT const &value) { set(value); return *this; }

	private:

		ValueT _val;
	};


	//property<Value, ParentT>:
	template<typename ValueT, typename ParentT>
	class property<ValueT, ParentT, detail::get_parent_func<void, void>::default_getter(), detail::get_parent_func<void, void>::default_setter(), detail::property_flag::w>//ValueT == const...
	{
	public:

		property(ParentT *parent, ValueT(ParentT::*getter)()const) :
			_obj(parent),
			_getter(getter)
		{}

		inline ValueT get() const
		{
			return (_obj->*_getter)();
		}

		operator ValueT() const { return get(); }

	private:
		ParentT *_obj;
		ValueT(ParentT::*_getter)()const;

		property &operator=(ValueT const &);
	};

	template<typename ValueT, typename ParentT, typename ValueT(ParentT::*Getter)()const, typename void(ParentT::*Setter)(ValueT const &), detail::e_get_set_state Active>
	class property<ValueT, ParentT, Getter, Setter, detail::property_flag::rw, Active>//ValueT != const...
	{
	public:

		property(ParentT *parent, const ValueT(ParentT::*getter)()const, void(ParentT::*setter)(ValueT const &), ValueT const & value) :
			_obj(parent),
			_getter(getter),
			_setter(setter)
		{
			set(value);
		}

		property(ParentT *parent, const ValueT(ParentT::*getter)()const, void(ParentT::*setter)(ValueT const &)) :
			_obj(parent),
			_getter(getter),
			_setter(setter)
		{
		}

		inline void set(ValueT const & value)
		{
			(_obj->*_setter)(value);
		}

		inline const ValueT &get() const
		{
			return (_obj->*_getter)();
		}

		property &operator=(ValueT const & value) { set(value); return *this; }
	private:

		ParentT *_obj;
		const ValueT(ParentT::*_getter)()const;
		void(ParentT::*_setter)(ValueT const &);

	};


	//property<Value, ParentT, ValueT(ParentT::*Getter)()>:
	template<typename ValueT, typename ParentT, typename detail::get_parent_func<ValueT, ParentT>::getter_t Getter, detail::property_flag::e_property_flag Flag>
	class property<ValueT, ParentT, Getter, 0, Flag> //typename detail::get_parent_func<typename ValueT, typename ParentT>::default_setter()
	{
	public:

		property(ParentT *parent) :
			_obj(parent)
		{}

		inline ValueT get() const
		{
			return (_obj->*Getter)();
		}

		operator ValueT() const { return get(); }

	private:

		property &operator=(ValueT const &);
	};

	//property<Value, ParentT, 0, ValueT(ParentT::*Setter)(ValueT const &)>:
	template<typename ValueT, typename ParentT, typename void(ParentT::*Setter)(ValueT const &), detail::e_get_set_state Active>
	class property<ValueT, ParentT, 0, Setter, detail::property_flag::r, Active>//ValueT == const...
	{
		property();//Invalid class: value is const but no Getter is provided!

		property(const property &rhs);
	};

	template<typename ValueT, typename ParentT, typename void(ParentT::*Setter)(ValueT const &), detail::property_flag::e_property_flag Flag, detail::e_get_set_state Active>
	class property<ValueT, ParentT, 0, Setter, Flag, Active>//ValueT != const...
	{
	public:

		property()
		{}

		property(ValueT const & value)
		{
			set(value);
		}

		ValueT set(ValueT const & value)
		{
			return (_obj->*Setter)(value);
		}

		property &operator=(ValueT const & value) { set(value); return *this; }

	private:
		ParentT *_obj;

		property(const property &rhs);

	};
	   */

}

#endif
