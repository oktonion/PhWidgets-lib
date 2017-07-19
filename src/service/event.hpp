#ifndef CPP_EVENT_HPP
#define CPP_EVENT_HPP

#include <map>

namespace cppevents
{
	namespace detail
	{
		struct Void {};

		template<typename ValueT, typename ParentT>
		struct get_parent_func
		{
			typedef ValueT value_t;
			typedef ParentT parent_t;
			typedef void(parent_t::* adder_t)(value_t);
			typedef void(parent_t::* remover_t)(value_t);

			static const adder_t &default_adder() { static adder_t adder = adder_t(0); return adder; }
			static const remover_t &default_remover() { static remover_t remover = remover_t(0); return remover; }
		};

		template<>
		struct get_parent_func<void, void>
		{
			typedef void value_t;
			typedef Void parent_t;
			typedef const int adder_t;
			typedef const int remover_t;

			static const adder_t &default_adder() { static adder_t adder = 0; return adder; }
			static const remover_t &default_remover() { static remover_t remover = 0; return remover; }
		};

		template<typename ValueT>
		struct get_parent_func<ValueT, void> :
			public get_parent_func<void, void>
		{
		};

		template<typename ParentT>
		struct get_parent_func<void, ParentT> :
			public get_parent_func<void, void>
		{
		};

		template<class event_delegate>
		struct event_base
		{
			template<class ParentT, typename detail::get_parent_func<typename event_delegate::delegate_t, ParentT>::adder_t Adder, typename detail::get_parent_func<typename event_delegate::delegate_t, ParentT>::remover_t Remover = detail::get_parent_func<typename event_delegate::delegate_t, ParentT>::default_remover()>
			class bind
			{
				typedef typename detail::get_parent_func<typename event_delegate::delegate_t, ParentT>::value_t value_t;

			public:
				bind(ParentT *parent) :
					_obj(parent)
				{}

				inline void add(value_t value)
				{
					(_obj->*Adder)(value);
				}

				inline void remove(value_t value)
				{
					(_obj->*Remover)(value);
				}

				inline void operator+=(value_t value)
				{
					add(value);
				}

				inline void operator-=(value_t value)
				{
					remove(value);
				}


			private:
				ParentT *_obj;

				bind(const bind &rhs);

				inline bind &operator=(value_t);
				inline bind &operator=(bind const &);
			};
		};

		template <class ReturnT, class Param1T, class Param2T, class Param3T, class Param4T, class Param5T, class Param6T, class Param7T, class Param8T>
		struct get_event_delegate;

#define DELEGATE_COMMON \
		public:\
			delegate_t(free_delegate_t val):\
				_type(free),\
				_free_delegate(val)\
			{\
\
			}\
\
			delegate_t(member_delegate_t val):\
				_type(member),\
				_member_delegate(val)\
			{\
				\
			}\
\
			delegate_t(global_delegate_t val):\
				_type(global),\
				_global_delegate(val)\
			{\
\
			}\
\
		private:\
			union\
			{\
				free_delegate_t _free_delegate;\
				member_delegate_t _member_delegate;\
				global_delegate_t _global_delegate;\
			};\
\
			enum\
			{\
				free,\
				member,\
				global\
			} _type;

		template <>
		struct get_event_delegate<void, void, void, void, void, void, void, void, void>
		{
			typedef void(*free_delegate_t)(void);

			template<class ThisT = Void>
			class delegate_t
			{
				typedef void(*free_delegate_t)(ThisT*);
				typedef void(ThisT::*member_delegate_t)(void);

				typedef void(*global_delegate_t)(void);

				DELEGATE_COMMON;

			public:

				inline void operator()(ThisT *obj)
				{
					switch(_type)
					{
						case free:
							(*_free_delegate)(obj);
							break;
						case member:
							(obj->*_member_delegate)();
							break;
						case global:
							(*_global_delegate)();
							break;
						default:
							break;
					}
				}

				inline void operator()()
				{
					switch(_type)
					{
						case global:
							(*_global_delegate)();
							break;
						default:
							break;
					}
				}
			};
		};

		template <class ReturnT, class Param1T, class Param2T, class Param3T>
		struct get_event_delegate<ReturnT, Param1T, Param2T, Param3T, void, void, void, void, void>
		{
			typedef ReturnT(*free_delegate_t)(Param1T, Param2T, Param3T);
		};

		#undef DELEGATE_COMMON
	}

	template <class ReturnT = void, class Param1T = void, class Param2T = void, class Param3T = void, class Param4T = void, class Param5T = void, class Param6T = void, class Param7T = void, class Param8T = void>
	class event:
		public detail::event_base< detail::get_event_delegate<ReturnT, Param1T, Param2T, Param3T, Param4T, Param5T, Param6T, Param7T, Param8T> >
	{

	};

}

#endif