#ifndef PH_PROPERTY_HPP
#define PH_PROPERTY_HPP

#include "property.hpp"

namespace PhWidgets
{
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

	public:
		template<class WidgetClassT, class ArgumentT, ArgumentT ArgumentID>
		class bind:
			public cpp_property_t::bind<WidgetClassT, &(WidgetClassT::getArgument<ValueT, WidgetClassT, ArgumentT, ArgumentID>) >
		{

		public:
			typedef cpp_property_t::bind<WidgetClassT, &(WidgetClassT::getArgument<ValueT, WidgetClassT, ArgumentT, ArgumentID>) > cpp_bind_t;

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

		

	public:

		template<class WidgetClassT, class ArgumentT, ArgumentT ArgumentID>
		class bind:
			public cpp_property_t::bind<
							WidgetClassT, 
							&(WidgetClassT::getArgument<ValueT, WidgetClassT, ArgumentT, ArgumentID>),
							&(WidgetClassT::setArgument<ValueT, WidgetClassT, ArgumentT, ArgumentID>) >
		{
			typedef cpp_property_t::bind<
							WidgetClassT,
							&(WidgetClassT::getArgument<ValueT, WidgetClassT, ArgumentT, ArgumentID>),
							&(WidgetClassT::setArgument<ValueT, WidgetClassT, ArgumentT, ArgumentID>)>
			cpp_bind_t;

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

	public:

		template<class WidgetClassT, class ArgumentT, ArgumentT ArgumentID>
		class bind:
			public cpp_property_t::bind<
			WidgetClassT,
			&(WidgetClassT::setArgument<ValueT, WidgetClassT, ArgumentT, ArgumentID>) >
		{
			typedef cpp_property_t::bind<
				WidgetClassT,
				&(WidgetClassT::setArgument<ValueT, WidgetClassT, ArgumentT, ArgumentID>) >
			cpp_bind_t;

		public:
			bind(WidgetClassT *parent) :
				cpp_bind_t(parent)
			{}
		};

	};	
}

#endif