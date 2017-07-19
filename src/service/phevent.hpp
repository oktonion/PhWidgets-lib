#ifndef PH_EVENT_HPP
#define PH_EVENT_HPP

#include <photon/PtWidget.h>

#include <set>

namespace phevents
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
	}

	struct phevent
	{
		typedef PtCallback_t ph_callback_t;

		template<class ParentT, typename detail::get_parent_func<ph_callback_t, ParentT>::adder_t Adder, typename detail::get_parent_func<ph_callback_t, ParentT>::remover_t Remover = detail::get_parent_func<ph_callback_t, ParentT>::default_remover()>
		class bind
		{
			typedef typename detail::get_parent_func<ph_callback_t, ParentT>::value_t value_t;

			class callback_container
			{
				typedef int(*callback_t)( PtWidget_t *, void *, PtCallbackInfo_t * );
				typedef int(*callback_proxy_t)( callback_container *, PtWidget_t *, void *, PtCallbackInfo_t * );

			public:

				callback_container(callback_t callback):
					_callback(callback)
				{}

				template<class Param1T, class Param2T, class Param3T>
				void init() 
				{
					_proxy_call = &callback_container::proxy_call<Param1T, Param2T, Param3T>;
				}

				inline int operator()(PtWidget_t *p1, void *p2, PtCallbackInfo_t *p3)
				{
					return _proxy_call(this, p1, p2, p3);
				}

				inline bool operator<(const callback_container &rhs) { return (_callback < rhs._callback || _proxy_call < rhs._proxy_call); }

			private:
				callback_t _callback;
				callback_proxy_t _proxy_call;

				template<class Param1T, class Param2T, class Param3T>
				static int proxy_call(callback_container *container, PtWidget_t *p1, void *p2, PtCallbackInfo_t *p3) 
				{ 
					return reinterpret_cast<int(*)(Param1T, Param2T, Param3T)>(container->_callback)(p1, p2, p3); 
				}
			};

			static std::set<callback_container> &repo() { static std::set<callback_container> repo; return repo; }

			static int proxy_call(PtWidgetT *p1, void *p2, PtCallbackInfo_t *p3)
			{
				callback_container &cbc = *reinterpret_cast<callback_container*>(p2);

				return cbc(p1, 0, p3);
			}

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
			
			template<class Param1T, class Param2T, class Param3T>
			inline void add(int(*value)(Param1T, Param2T, Param3T))
			{
				std::pair<std::set<callback_container>::iterator, bool> res = repo().insert(callback_container(value));

				PtCallback_t proxy;
				proxy.event_f = &bind::proxy_call;
				proxy.data = &(*(res.first));

				(_obj->*Adder)(proxy);
			}

			template<class Param1T, class Param2T, class Param3T>
			inline void remove(int(*value)(Param1T, Param2T, Param3T))
			{
				std::pair<std::set<callback_container>::iterator, bool> res = repo().insert(callback_container(value));

				PtCallback_t proxy;
				proxy.event_f = &bind::proxy_call;
				proxy.data = &(*(res.first));

				(_obj->*Remover)(proxy);
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

}

#endif