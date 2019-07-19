#ifndef PHWIDGETS_CONTAINER_H
#define PHWIDGETS_CONTAINER_H

#include <photon/PtContainer.h>
#include <photon/PtFillLayout.h>

#include "./Basic.h"


namespace PhWidgets
{
		
	class Container:
		public Basic
	{
	public:

		struct ThisArgs
		{
			
			struct ArgLong
			{
				enum eArgLong
				{
					container_flags = Pt_ARG_CONTAINER_FLAGS
				};
			};
			
			struct ArgInt
			{
				enum eArgInt
				{
					layout_type = Pt_ARG_LAYOUT_TYPE
				};
			};
			
			struct ArgBool
			{
				enum eArgBool
				{
					cursor_override = Pt_ARG_CURSOR_OVERRIDE
				};
			};

			
			struct ArgPFillLayoutInfo
			{
				enum eArgPFillLayoutInfo
				{
					fill_layout_info = Pt_ARG_FILL_LAYOUT_INFO
				};
			};
			
			struct ArgPGridLayoutInfo
			{
				enum eArgPGridLayoutInfo
				{
					grid_layout_info = Pt_ARG_GRID_LAYOUT_INFO
				};
			};
			
			struct ArgPLayoutDefinition
			{
				enum eArgPLayoutDefinition
				{
					layout = Pt_ARG_LAYOUT
				};
			};
			
			struct ArgPVoid
			{
				enum eArgPVoid
				{
					layout_info = Pt_ARG_LAYOUT_INFO
				};
			};
			
			struct ArgPRowLayoutInfo
			{
				enum eArgPRowLayoutInfo
				{
					row_layout_info = Pt_ARG_ROW_LAYOUT_INFO
				};
			};

									
			struct ArgPChar
			{
				enum eArgPChar
				{
					title = Pt_ARG_TITLE,
					title_font = Pt_ARG_TITLE_FONT
				};
			};	
			
		};

		struct ThisCallbacks
		{
			struct Callback
			{
				enum eCallback
				{
					child_added_removed = Pt_CB_CHILD_ADDED_REMOVED,
					child_getting_focus = Pt_CB_CHILD_GETTING_FOCUS,
					child_losing_focus = Pt_CB_CHILD_LOSING_FOCUS,
					layout = Pt_CB_LAYOUT,
					resize = Pt_CB_RESIZE
				};
			};
		};
			
		struct ArgLong:
			public ArgumentsEx<Basic::ArgLong>,
			public ThisArgs::ArgLong
		{
			typedef ThisArgs::ArgLong::eArgLong eArgLong;
		};
		
		struct ArgInt:
			public ThisArgs::ArgInt,
			public ThisArgs::ArgBool
        { };
		
		struct ArgPFillLayoutInfo:
			public ThisArgs::ArgPFillLayoutInfo
        { };
		
		struct ArgPGridLayoutInfo:
			public ThisArgs::ArgPGridLayoutInfo
        { };
		
		struct ArgPLayoutDefinition:
			public ThisArgs::ArgPLayoutDefinition
        { };
		
		struct ArgPVoid:
			public ArgumentsEx<Basic::ArgPVoid>,
			public ThisArgs::ArgPVoid
		{
			typedef ThisArgs::ArgPVoid::eArgPVoid eArgPVoid;
		};	
		
		struct ArgPRowLayoutInfo:
			public ThisArgs::ArgPRowLayoutInfo
        { };


		struct ArgPChar:
			public ArgumentsEx<Basic::ArgPChar>,
			public ThisArgs::ArgPChar
		{
			typedef ThisArgs::ArgPChar::eArgPChar eArgPChar;
		};	

		struct Callback:
			public ArgumentsEx<Basic::Callback>,
			public ThisCallbacks::Callback
		{
			typedef ThisCallbacks::Callback::eCallback eCallback;
		};

		struct Arguments:
			public ArgLong,
			public ArgInt,
			public ArgPFillLayoutInfo,
			public ArgPGridLayoutInfo,
			public ArgPLayoutDefinition,
			public ArgPVoid,
			public ArgPRowLayoutInfo,
			public ArgPChar,
			public Basic::Arguments
        { };

		struct Callbacks :
			public Callback,
			public Basic::Callbacks
        { };

	protected:
		typedef ResourceFrom<Basic::WidgetResourcesSingleton>::
			Define::String<ThisArgs::ArgPChar::eArgPChar>::
			Define::Boolean<ThisArgs::ArgBool::eArgBool, bool>::
			Define::Scalar<ThisArgs::ArgInt::eArgInt, int>::
			Define::Struct<ThisArgs::ArgPFillLayoutInfo::eArgPFillLayoutInfo, PtFillLayoutInfo_t>::
			Define::Struct<ThisArgs::ArgPGridLayoutInfo::eArgPGridLayoutInfo, PtGridLayoutInfo_t>::
			Define::Struct<ThisArgs::ArgPLayoutDefinition::eArgPLayoutDefinition, PtLayoutDefinition_t>::
			Define::Struct<ThisArgs::ArgPRowLayoutInfo::eArgPRowLayoutInfo, PtRowLayoutInfo_t>::
			Define::Struct<ThisArgs::ArgPVoid::eArgPVoid, void*>::
			Define::Flag<ThisArgs::ArgLong::eArgLong, long>::

			Define::Link<ThisCallbacks::Callback::eCallback, PtCallback_t*>::

		resource_type WidgetResourcesSingleton;

		virtual void check();
						
	public:
		WidgetResourcesSingleton resource;

		Container(int abn);
		Container(PtWidget_t *wdg);

		Container(const Container &rhs);

		Container &operator=(const Container &rhs);
		
		phwidgets_event<Container, Container::Callbacks::child_added_removed>	ChildAddedRemoved;
		phwidgets_event<Container, Container::Callbacks::child_getting_focus>	ChildGettingFocus;
		phwidgets_event<Container, Container::Callbacks::child_losing_focus>	ChildLosingFocus;
		phwidgets_event<Container, Container::Callbacks::layout>				LayoutChanged;
		phwidgets_event<Container, Container::Callbacks::resize>				Resize;
	};
} // namespace PhWidgets


#endif // PHWIDGETS_CONTAINER_H
