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
			typedef MaskT mask_type;
			typedef phproperty<mask_type> ph_property_t;
			typedef typename ph_property_t::template bind<WidgetClassT, ArgumentT, ArgumentID> ph_bind_t;

		public:
			typedef cppbitmasks::bitmask<MaskT, FlagT> value_type;

			bind_internal(WidgetClassT *parent) :
				ph_bind_t(parent)
			{}

			inline void set(value_type value)
			{
				static_cast<ph_bind_t*>(this)->set(value);
			}

			inline value_type get() const
			{
				value_type bm;
				mask_type mask = static_cast<const ph_bind_t*>(this)->get();
				std::memcpy(&bm, &mask, sizeof(MaskT));
				return bm;
			}

			inline operator value_type() const { return get(); }
			inline operator mask_type() const { return static_cast<const ph_bind_t*>(this)->get(); }

			inline bind_internal &operator=(value_type value) { set(value); return *this; }

			inline value_type operator()(void) const { return get(); }

			inline void operator()(value_type value) { set(value); return *this; }
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
}

#endif