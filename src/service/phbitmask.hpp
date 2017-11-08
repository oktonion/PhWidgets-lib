#ifndef PH_BITMASK_HPP
#define PH_BITMASK_HPP

#include "phproperty.hpp"
#include "bitmask.hpp"

#include <cstring>

namespace PhWidgets
{
	template<class MaskT, class FlagT>
	class phbitmask
	{
		template<class WidgetClassT, class ArgumentT, ArgumentT ArgumentID>
		class bind_internal :
			private phproperty<MaskT>::template bind<WidgetClassT, ArgumentT, ArgumentID>
		{
			typedef cppbitmasks::bitmask<MaskT, FlagT> value_t;
			typedef phproperty<MaskT> ph_property_t;
			typedef typename ph_property_t::template bind<WidgetClassT, ArgumentT, ArgumentID> ph_bind_t;

		public:
			bind_internal(WidgetClassT *parent) :
				ph_bind_t(parent)
			{}

			inline void set(value_t value)
			{
				static_cast<ph_bind_t*>(this)->set(value);
			}

			inline value_t get() const
			{
				value_t bm;
				MaskT mask = static_cast<ph_bind_t*>(this)->get();
				std::memcpy(&bm, &mask, sizeof(MaskT));
				return bm;
			}

			inline operator value_t() const { return get(); }

			inline bind_internal &operator=(value_t value) { set(value); return *this; }

			inline value_t operator()(void) const { return get(); }

			inline void operator()(value_t value) { set(value); return *this; }
		};
		
	public:
		template<class WidgetClassT, class ArgumentT, ArgumentT ArgumentID>
		class bind :
			public bind_internal<WidgetClassT, ArgumentT, ArgumentID>
		{
			typedef bind_internal<WidgetClassT, ArgumentT, ArgumentID> internal_bind_t;

		public:
			bind(WidgetClassT *parent) :
				internal_bind_t(parent)
			{}
			
			using internal_bind_t::operator=;
		};
	};

	/*template<class MaskT, class FlagT>
	class phbitmask<const MaskT, FlagT>
	{
	public:
		template<class WidgetClassT, class ArgumentT, ArgumentT ArgumentID>
		class bind :
			private phproperty<const MaskT>::template bind<WidgetClassT, ArgumentT, ArgumentID>
		{
			typedef cppbitmasks::bitmask<MaskT, FlagT> value_t;
			typedef phproperty<const MaskT>::template bind<WidgetClassT, ArgumentT, ArgumentID> ph_bind_t;

		public:
			bind(WidgetClassT *parent) :
				ph_bind_t(parent)
			{}

			inline value_t get() const
			{
				value_t bm;
				MaskT mask = static_cast<ph_bind_t*>(this)->get();
				std::memcpy(&bm, &mask, sizeof(MaskT));
				return bm;
			}

			inline operator value_t() const { return get(); }

			inline value_t operator()(void) const { return get(); }

		private:
			inline bind &operator=(value_t const &);
			inline bind &operator=(bind const &);
		};
	};*/
}

#endif