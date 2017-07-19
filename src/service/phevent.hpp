#ifndef PH_EVENT_HPP
#define PH_EVENT_HPP

#include <photon/PtWidget.h>

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
		typedef int(*ph_callback_t)(PtWidget_t *, void *, PtCallbackInfo_t *);

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