#ifndef PH_EVENT_HPP
#define PH_EVENT_HPP

#include <photon/PtWidget.h>

#include <set>
#include <map>

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

	class phevent
	{
			class callback_container
			{
				typedef int(*callback_t)( PtWidget_t *, void *, PtCallbackInfo_t * );
				typedef int(*callback_proxy_t)(const callback_container *, PtWidget_t *, void *, PtCallbackInfo_t * );

			public:
				
				template<class Param1T, class Param2T, class Param3T>
				callback_container(int(*callback)( Param1T, Param2T, Param3T)):
					_callback(reinterpret_cast<callback_t>(callback)),
					_proxy_call(&callback_container::proxy_call<Param1T, Param2T, Param3T>)
				{}

				template<class Param1T, class Param2T, class Param3T>
				void init() 
				{
					_proxy_call = &callback_container::proxy_call<Param1T, Param2T, Param3T>;
				}

				inline int operator()(PtWidget_t *p1, void *p2, PtCallbackInfo_t *p3) const
				{
					return _proxy_call(this, p1, p2, p3);
				}

				inline bool operator<(const callback_container &rhs) const { return (_callback < rhs._callback || _proxy_call < rhs._proxy_call); }

			private:
				callback_t _callback;
				callback_proxy_t _proxy_call;

				template<class Param1T, class Param2T, class Param3T>
				static int proxy_call(const callback_container *container, PtWidget_t *p1, void *p2, PtCallbackInfo_t *p3) 
				{ 
					return reinterpret_cast<int(*)(Param1T, Param2T, Param3T)>(container->_callback)(p1, reinterpret_cast<Param2T>(p2), p3); 
				}
			};

	public:
		class ph_callback_t
		{
			class cb_with_data
			{
				typedef std::set<callback_container> callback_repo_t;

			public:

				cb_with_data(callback_container cb, void *dt = 0)
				{
					std::pair<callback_repo_t::iterator, bool> res = cb_with_data::repo().insert(cb);

					callback = &(*res.first);
					data = dt;
				}

				inline int operator()(PtWidget_t *p1, PtCallbackInfo_t *p3) const
				{
					return (*callback)(p1, data, p3);
				}

				inline bool operator<(const cb_with_data &rhs) const { return callback < rhs.callback || data < rhs.data; }

			private:
				const callback_container *callback;
				void *data;

				static callback_repo_t &repo() { static callback_repo_t repo; return repo; }
			};
			
			typedef std::set<cb_with_data> cb_data_repo_t;

			static cb_data_repo_t &repo() { static cb_data_repo_t repo; return repo; }
			
			static int proxy_call(PtWidget_t *p1, void *p2, PtCallbackInfo_t *p3)
			{
				const cb_with_data &cbwd = *reinterpret_cast<const cb_with_data*>(p2);

				cb_data_repo_t::iterator it = repo().find(cbwd);

				if(repo().end() == it)
					return 0;

				return cbwd(p1, p3);
			}

		public:
			ph_callback_t(const PtCallback_t &callback):
				_callback(callback)
			{}
			
			template<class Param1T, class Param2T, class Param3T>
			ph_callback_t(int(*value)(Param1T, Param2T, Param3T))
			{
				std::pair<cb_data_repo_t::iterator, bool> res = repo().insert(cb_with_data(value));

				_callback.event_f = &proxy_call;
				_callback.data = const_cast<cb_with_data*>(&(*(res.first)));
			}

			template<class Param1T, class Param2T, class Param3T>
			ph_callback_t(int(*value)(Param1T, Param2T, Param3T), Param2T &data)
			{
				std::pair<cb_data_repo_t::iterator, bool> res = repo().insert(cb_with_data(value, data));

				_callback.event_f = &proxy_call;
				_callback.data = const_cast<cb_with_data*>(&(*(res.first)));
			}

			~ph_callback_t()
			{
				//do NOTHING!
			}

			inline operator PtCallback_t() const{ return _callback; }
			
		private:
			PtCallback_t _callback;
		};

		template<class ParentT, typename detail::get_parent_func<ph_callback_t, ParentT>::adder_t Adder, typename detail::get_parent_func<ph_callback_t, ParentT>::remover_t Remover = detail::get_parent_func<ph_callback_t, ParentT>::default_remover()>
		class bind
		{
			typedef typename detail::get_parent_func<ph_callback_t, ParentT>::value_t value_t;

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

}

#endif