#ifndef CPP_PROPERTY_HPP
#define CPP_PROPERTY_HPP

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

		template<typename T>
		struct remove_reference
		{
			typedef T type;
		};

		template<typename T>
		struct remove_reference<T&>
		{
			typedef T type;
		};

		template<typename T>
		struct remove_const
		{
			typedef T type;
		};

		template<typename T>
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

#ifdef CPP_PROPERTIES_COMPARE_OPERATORS
		template<class T1, class T2>
		no_type operator==(T1,T2);
		
		template<class T1, class T2>
		no_type operator!=(T1,T2);

		template<class T1, class T2>
		no_type operator<(T1,T2);
#endif

		yes_type has_comparison_operator_tester(bool);
		no_type has_comparison_operator_tester(...);

		template<class T>
		T& declref();

#define CPP_PROPERTIES_COMPARE_OPERATORS
		template<class T, class CompT>
		struct has_equal
		{
			static const bool value = 
				sizeof(has_comparison_operator_tester(declref<T>() == declref<CompT>())) != sizeof(no_type);
		};

		template<class T, class CompT>
		struct has_not_equal
		{
			static const bool value = 
				sizeof(has_comparison_operator_tester(declref<T>() != declref<CompT>())) != sizeof(no_type);
		};

		template<class T, class CompT>
		struct has_less
		{
			static const bool value = 
				sizeof(has_comparison_operator_tester(declref<T>() < declref<CompT>())) != sizeof(no_type);
		};
#undef CPP_PROPERTIES_COMPARE_OPERATORS
		
		template<class T>
		yes_type is_convertable_tester(T);
		template<class T>
		no_type is_convertable_tester(...);

		template<class T, class ConvT>
		struct is_convertable
		{
			static const bool value = 
				sizeof(is_convertable_tester<ConvT>(declref<T>())) == sizeof(yes_type);
		};

		template<class T>
		struct is_array
		{
			static const bool value = false;
		};

		template<class T, int Size>
		struct is_array<T[Size]>
		{
			static const bool value = true;
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

		struct Void {};

		template<typename ValueT, typename ParentT>
		struct get_parent_func
		{
			typedef ValueT value_type;
			typedef ParentT parent_t;
			typedef value_type(parent_t::* getter_t)()const;
			typedef void(parent_t::* setter_t)(value_type);

			static const getter_t &default_getter() { static getter_t getter = getter_t(0); return getter;}
			static const setter_t &default_setter() { static setter_t setter = setter_t(0); return setter;}
		};

		template<>
		struct get_parent_func<void, void>
		{
			typedef void value_type;
			typedef Void parent_t;
			typedef const int getter_t;
			typedef const int setter_t;

			static const getter_t &default_getter() { static getter_t getter = 0; return getter;}
			static const setter_t &default_setter() { static setter_t setter = 0; return setter;}
		};

		template<typename ValueT>
		struct get_parent_func<ValueT, void>
		{
			typedef ValueT value_type;
			typedef value_type(*getter_t)();
			typedef void(*setter_t)(value_type);

			static const getter_t &default_getter() { static getter_t getter = getter_t(0); return getter;}
			static const setter_t &default_setter() { static setter_t setter = setter_t(0); return setter;}
		};

		template<typename ParentT>
		struct get_parent_func<void, ParentT> :
			public get_parent_func<void, void>
		{
		};
	}

	template<class ValueT>
	struct Ipropertyr
	{
		typedef ValueT value_type;
		virtual value_type get() const = 0;
	};

	template<class ValueT>
	struct Ipropertyw
	{
		typedef ValueT value_type;
		virtual void set(ValueT) = 0;
	};

	template<class ValueT, 
		const detail::property_flag::e_property_flag Flag = 
			static_cast<const detail::property_flag::e_property_flag>(detail::flag_chooser<ValueT>::flag)>
	struct property_traits;

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
	template<typename ValueT>
	class property<ValueT, detail::property_flag::ro>: //ValueT == const...
		public Ipropertyr<typename detail::remove_const<typename detail::remove_reference<ValueT>::type const &>::type>,
		public property_traits<typename detail::remove_const<typename detail::remove_reference<ValueT>::type const &>::type, detail::property_flag::ro>
	{
	public:
		typedef typename Ipropertyr<typename detail::remove_const<typename detail::remove_reference<ValueT>::type const &>::type>::value_type value_type;

		template<class ParentT, typename detail::get_parent_func<ValueT, ParentT>::getter_t Getter>
		class bind:
			public Ipropertyr<typename detail::get_parent_func<ValueT, ParentT>::value_type>,
			public property_traits<typename detail::get_parent_func<ValueT, ParentT>::value_type, detail::property_flag::ro>
		{
			typedef Ipropertyr<typename detail::get_parent_func<ValueT, ParentT>::value_type> base_type;
			typedef typename detail::enable_if<detail::has_equal<ValueT, ValueT>::value, const base_type&>::type operator_equal_type;
		public:
			typedef typename base_type::value_type value_type;

			bind(ParentT *parent) :
				_obj(parent)
			{}

			inline value_type get() const
			{
				return (_obj->*Getter)();
			}

			inline operator value_type() const { return get(); }
			
			inline value_type operator()(void) const { return get(); }

			inline bool operator==(operator_equal_type other) const {return get() == other.get();}

		private:
			ParentT *_obj;
			
			bind(const bind &rhs);

			inline bind &operator=(typename detail::remove_const<typename detail::remove_reference<ValueT>::type>::type const &);
			inline bind &operator=(bind const &);
		};

		template<typename detail::get_parent_func<ValueT, void>::getter_t Getter>
		class bind_static:
			public Ipropertyr<typename detail::get_parent_func<ValueT, void>::value_type>,
			public property_traits<typename detail::get_parent_func<ValueT, void>::value_type, detail::property_flag::ro>
		{
		public:
			typedef typename Ipropertyr<typename detail::get_parent_func<ValueT, void>::value_type>::value_type value_type;

			bind_static()
			{}

			inline value_type get() const
			{
				return (*Getter)();
			}

			inline operator value_type() const { return get(); }
			
			inline value_type operator()(void) const { return get(); }

		private:
			
			bind_static(const bind_static &rhs);

			inline bind_static &operator=(typename detail::remove_const<typename detail::remove_reference<ValueT>::type>::type const &);
			inline bind_static &operator=(bind_static const &);
		};

		property(value_type value) :
			_val(value)
		{}

		inline value_type get() const
		{
			return _val;
		}

		inline operator value_type() const { return get(); }

		inline value_type operator()(void) const { return get(); }

	private:

		//inline operator value_type&();

		const ValueT _val;

		inline property &operator=(value_type);
		inline property &operator=(property const &);
	};


	template<typename ValueT>
	class property<ValueT, detail::property_flag::rw>: //ValueT != const...
		public Ipropertyr<typename detail::remove_reference<ValueT>::type &>,
		public Ipropertyw<typename detail::remove_reference<ValueT>::type &>,
		public property_traits<typename detail::remove_reference<ValueT>::type &, detail::property_flag::rw>
	{
	public:
		typedef typename Ipropertyr<typename detail::remove_reference<ValueT>::type &>::value_type value_type;

		template<class ParentT, typename detail::get_parent_func<ValueT, ParentT>::getter_t Getter, typename detail::get_parent_func<ValueT, ParentT>::setter_t Setter>
		class bind:
			public Ipropertyr<typename detail::get_parent_func<ValueT, ParentT>::value_type>,
			public property_traits<typename detail::get_parent_func<ValueT, ParentT>::value_type, detail::property_flag::rw>
		{

		public:
			typedef typename Ipropertyr<typename detail::get_parent_func<ValueT, ParentT>::value_type>::value_type value_type;
			
			bind(ParentT *parent) :
				_obj(parent)
			{}

			inline void set(value_type value)
			{
				(_obj->*Setter)(value);
			}

			inline value_type get() const
			{
				return (_obj->*Getter)();
			}

			inline operator value_type() const { return get(); }

			inline bind &operator=(value_type value) { set(value); return *this; }

			inline value_type operator()(void) const { return get(); }

			inline void operator()(value_type value) { set(value); return *this; }
			
			inline bool operator==(value_type value) {return value == get();}

		private:
			ParentT *_obj;
			
			bind(const bind &rhs);
		};

		property()
		{}

		property(value_type value) :
			_val(value)
		{}

		inline void set(value_type const value)
		{
			_val = value;
		}

		inline value_type get() const
		{
			return _val;
		}

		inline property &operator=(value_type const value) { set(value); return *this; }

		inline operator value_type() const { return get(); }
		
		inline value_type operator()(void) const { return get(); }

		inline void operator()(value_type const value) { set(value); }

	private:

		ValueT _val;

	};

	template<typename ValueT>
	class property<ValueT, detail::property_flag::wo>: //ValueT != const...
		public Ipropertyw<typename detail::remove_reference<ValueT>::type &>,
		public property_traits<ValueT, detail::property_flag::wo>
	{
	public:
		typedef typename Ipropertyw<typename detail::remove_reference<ValueT>::type const &>::value_type value_type;

		template<class ParentT, typename detail::get_parent_func<ValueT, ParentT>::setter_t Setter>
		class bind:
			public Ipropertyw<typename detail::get_parent_func<ValueT, ParentT>::value_type>,
			public property_traits<ValueT, detail::property_flag::wo>
		{
		public:
			typedef typename Ipropertyw<typename detail::get_parent_func<ValueT, ParentT>::value_type>::value_type value_type;

			bind(ParentT *parent) :
				_obj(parent)
			{}

			inline void set(value_type value)
			{
				(_obj->*Setter)(value);
			}
			
			inline bind &operator=(value_type value) { set(value); return *this; }

			inline void operator()(value_type value) { set(value); return *this; }
		private:
			ParentT *_obj;
			
			bind(const bind &rhs);
		};

		property()
		{}

		property(ValueT value) :
			_val(value)
		{}

		inline void set(value_type value)
		{
			_val = value;
		}
		
		inline property &operator=(value_type value) { set(value); return *this; }

		inline void operator()(value_type value) { set(value); }
	private:

		ValueT _val;
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
		) &&
		detail::is_array<ValueT>::value == false
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
		) &&
		detail::is_array<ValueT>::value == false
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
		) &&
		detail::is_array<ValueT>::value == false
		,
		bool
	>::type operator<(
		const Ipropertyr<ValueT> &lhs, 
		const OtherValueT &rhs)
	{
		return lhs.get() < rhs;
	}

	namespace detail
	{
		struct void_type {};

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

		template<class T, bool Enabled>
		struct size_property_trait_impl
		{ };
		
		template<class T>
		struct size_property_trait_impl<T, true>
		{ 
		private:
			typedef typename remove_reference<T>::type clear_type;
		public:
			typedef typename clear_type::size_type size_type;
			
			size_type size() const
			{
				return reinterpret_cast<const Ipropertyr<T>*>(this)->get().size();
			}
		};

		template<class T, bool Enabled>
		struct const_begin_end_property_trait_impl
		{ };
		
		template<class T>
		struct const_begin_end_property_trait_impl<T, true>
		{ 
		private:
			typedef typename remove_reference<T>::type clear_type;
		public:
			typedef typename clear_type::const_iterator const_iterator;
			
			const_iterator begin() const
			{
				return reinterpret_cast<const Ipropertyr<T>*>(this)->get().begin();
			}

			const_iterator end() const
			{
				return reinterpret_cast<const Ipropertyr<T>*>(this)->get().end();
			}

			const_iterator cbegin() const
			{
				return reinterpret_cast<const Ipropertyr<T>*>(this)->get().begin();
			}

			const_iterator cend() const
			{
				return reinterpret_cast<const Ipropertyr<T>*>(this)->get().end();
			}
		};

		template<class T>
		struct size_property_trait:
			size_property_trait_impl<T, has_size_type<typename remove_reference<T>::type>::value>
		{ };

		template<class T>
		struct const_begin_end_property_trait:
			const_begin_end_property_trait_impl<T, has_const_iterator<typename remove_reference<T>::type>::value>
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
		detail::const_begin_end_property_trait<ValueT>
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