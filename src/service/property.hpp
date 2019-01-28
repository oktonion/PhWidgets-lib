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


	template<class ValueT = void,
		const detail::property_flag::e_property_flag Flag = (const detail::property_flag::e_property_flag)(detail::flag_chooser<ValueT>::flag)>
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
	class property<ValueT, detail::property_flag::ro>//ValueT == const...
	{
	public:
		typedef typename detail::remove_const<typename detail::remove_reference<ValueT>::type>::type value_type;

		template<class ParentT, typename detail::get_parent_func<ValueT, ParentT>::getter_t Getter>
		class bind
		{
		public:
			typedef typename detail::get_parent_func<ValueT, ParentT>::value_type value_type;

			bind(ParentT *parent) :
				_obj(parent)
			{}

			inline value_type get() const
			{
				return (_obj->*Getter)();
			}

			inline operator value_type() const { return get(); }
			
			inline value_type operator()(void) const { return get(); }

		private:
			ParentT *_obj;
			
			bind(const bind &rhs);

			inline bind &operator=(typename detail::remove_const<typename detail::remove_reference<ValueT>::type>::type const &);
			inline bind &operator=(bind const &);
		};

		template<typename detail::get_parent_func<ValueT, void>::getter_t Getter>
		class bind_static
		{
		public:
			typedef typename detail::get_parent_func<ValueT, void>::value_type value_type;

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

		property(value_type const &value) :
			_val(value)
		{}

		inline const value_type &get() const
		{
			return _val;
		}

		inline operator const value_type&() const { return get(); }

		inline const value_type& operator()(void) const { return get(); }

	private:

		//inline operator value_type&();

		const ValueT _val;

		inline property &operator=(value_type const &);
		inline property &operator=(property const &);
	};


	template<typename ValueT>
	class property<ValueT, detail::property_flag::rw>//ValueT != const...
	{
	public:
		typedef typename detail::remove_reference<ValueT>::type value_type;

		template<class ParentT, typename detail::get_parent_func<ValueT, ParentT>::getter_t Getter, typename detail::get_parent_func<ValueT, ParentT>::setter_t Setter>
		class bind
		{
		public:
			typedef typename detail::get_parent_func<ValueT, ParentT>::value_type value_type;

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
			

		private:
			ParentT *_obj;
			
			bind(const bind &rhs);
		};

		property()
		{}

		property(ValueT value) :
			_val(value)
		{}

		inline void set(value_type const &value)
		{
			_val = value;
		}

		inline value_type &get() const
		{
			return _val;
		}

		inline property &operator=(value_type const &value) { set(value); return *this; }

		inline operator value_type&() const { return get(); }
		
		inline value_type operator()(void) const { return get(); }

		inline void operator()(value_type const &value) { set(value); }

	private:

		ValueT _val;

	};

	template<typename ValueT>
	class property<ValueT, detail::property_flag::wo>//ValueT != const...
	{
	public:
		typedef typename detail::remove_reference<ValueT>::type value_type;

		template<class ParentT, typename detail::get_parent_func<ValueT, ParentT>::setter_t Setter>
		class bind
		{
		public:
			typedef typename detail::get_parent_func<ValueT, ParentT>::value_type value_type;

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

		inline void set(value_type const &value)
		{
			_val = value;
		}
		
		inline property &operator=(value_type const &value) { set(value); return *this; }

		inline void operator()(value_type const &value) { set(value); }
	private:

		ValueT _val;
	};


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