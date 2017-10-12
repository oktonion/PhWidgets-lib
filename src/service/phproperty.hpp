#ifndef PH_PROPERTY_HPP
#define PH_PROPERTY_HPP

#include "property.hpp"

namespace PhWidgets
{
	struct IPhWidgetsProperty
	{
		template<class ReturnT, class WidgetClassT, class ArgumentT, ArgumentT ArgumentID>
		ReturnT getArgument() const
		{
			return ReturnT();
			//return static_cast<const WidgetClassT*>(this)->resource[ArgumentID].get();
		}

		template<class ValueT, class WidgetClassT, class ArgumentT, ArgumentT ArgumentID>
		void setArgument(ValueT val)
		{
			//static_cast<const WidgetClassT*>(this)->resource[ArgumentID].set(val);
		}
	};

	template<class ValueT = void,
		const cppproperties::detail::property_flag::e_property_flag Flag = (const cppproperties::detail::property_flag::e_property_flag)(cppproperties::detail::flag_chooser<ValueT>::flag)>
	class phwidgets_property{};

	//phwidgets_property<void>:
	template<>
	class phwidgets_property<void, cppproperties::detail::property_flag::ro> :
		public cppproperties::detail::property_flag
	{
	public:
		typedef cppproperties::detail::property_flag flags;
	};

	template<>
	class phwidgets_property<void, cppproperties::detail::property_flag::wo> :
		public cppproperties::detail::property_flag
	{
	public:
		typedef cppproperties::detail::property_flag flags;
	};

	template<>
	class phwidgets_property<void, cppproperties::detail::property_flag::rw> :
		public cppproperties::detail::property_flag
	{
	public:
		typedef cppproperties::detail::property_flag flags;
	};

	//phwidgets_property<Value>:
	template<typename ValueT>
	class phwidgets_property<ValueT, cppproperties::detail::property_flag::ro>//ValueT == const...
	{
		typedef cppproperties::property<ValueT, cppproperties::detail::property_flag::ro> cpp_property_t;

		template<class WidgetClassT, typename cppproperties::detail::get_parent_func<ValueT, WidgetClassT>::getter_t Getter>
		struct bind_internal :
			public cpp_property_t::template bind<WidgetClassT, Getter>
		{
			bind_internal(WidgetClassT *parent) :
				cpp_property_t::template bind<WidgetClassT, Getter>(parent)
			{}
		};

	public:
		template<class WidgetClassT, class ArgumentT, ArgumentT ArgumentID>
		class bind :
			public bind_internal<
				IPhWidgetsProperty, 
				&IPhWidgetsProperty::getArgument<ValueT, WidgetClassT, ArgumentT, ArgumentID>
			>
		{
			typedef bind_internal<
				IPhWidgetsProperty, 
				&IPhWidgetsProperty::getArgument<ValueT, WidgetClassT, ArgumentT, ArgumentID> 
			> cpp_bind_t;

		public:
			bind(WidgetClassT *parent) :
				cpp_bind_t(parent)
			{}

		};
	};


	template<typename ValueT>
	class phwidgets_property<ValueT, cppproperties::detail::property_flag::rw>//ValueT != const...
	{
		typedef cppproperties::property<ValueT, cppproperties::detail::property_flag::rw> cpp_property_t;

		template<class WidgetClassT, typename cppproperties::detail::get_parent_func<ValueT, WidgetClassT>::getter_t Getter, typename cppproperties::detail::get_parent_func<ValueT, WidgetClassT>::setter_t Setter>
		struct bind_internal :
			public cpp_property_t::template bind<WidgetClassT, Getter, Setter>
		{
			bind_internal(WidgetClassT *parent) :
				cpp_property_t::template bind<WidgetClassT, Getter, Setter>(parent)
			{}
		};

	public:

		template<class WidgetClassT, class ArgumentT, ArgumentT ArgumentID>
		class bind :
			public bind_internal<
				IPhWidgetsProperty, 
				&IPhWidgetsProperty::getArgument<ValueT, WidgetClassT, ArgumentT, ArgumentID>,
				&IPhWidgetsProperty::setArgument<ValueT, WidgetClassT, ArgumentT, ArgumentID>
			>
		{
			typedef bind_internal<
				IPhWidgetsProperty,
				&IPhWidgetsProperty::getArgument<ValueT, WidgetClassT, ArgumentT, ArgumentID>,
				&IPhWidgetsProperty::setArgument<ValueT, WidgetClassT, ArgumentT, ArgumentID>
			> cpp_bind_t;

		public:
			bind(WidgetClassT *parent) :
				cpp_bind_t(parent)
			{}

		};

	};

	template<typename ValueT>
	class phwidgets_property<ValueT, cppproperties::detail::property_flag::wo>//ValueT != const...
	{
		typedef cppproperties::property<ValueT, cppproperties::detail::property_flag::wo> cpp_property_t;

		template<class WidgetClassT, typename cppproperties::detail::get_parent_func<ValueT, WidgetClassT>::setter_t Setter>
		struct bind_internal :
			public cpp_property_t::template bind<WidgetClassT, Setter>
		{
			bind_internal(WidgetClassT *parent) :
				cpp_property_t::template bind<WidgetClassT, Setter>(parent)
			{}
		};

	public:
		template<class WidgetClassT, class ArgumentT, ArgumentT ArgumentID>
		class bind :
			public bind_internal<
				IPhWidgetsProperty, 
				&IPhWidgetsProperty::setArgument<ValueT, WidgetClassT, ArgumentT, ArgumentID>
			>
		{
			typedef bind_internal<
				IPhWidgetsProperty, 
				&IPhWidgetsProperty::setArgument<ValueT, WidgetClassT, ArgumentT, ArgumentID>
			> cpp_bind_t;

		public:
			bind(WidgetClassT *parent) :
				cpp_bind_t(parent)
			{}

		};

	};	
}

#endif