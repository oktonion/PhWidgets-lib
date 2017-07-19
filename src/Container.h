#ifndef PT_CONTAINER_H
#define PT_CONTAINER_H

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
			using Basic::ArgLong::eArgLong;
			using ThisArgs::ArgLong::eArgLong;
		};
		
		struct ArgInt:
			public ThisArgs::ArgInt,
			public ThisArgs::ArgBool
		{
		};
		
		struct ArgPFillLayoutInfo:
			public ThisArgs::ArgPFillLayoutInfo
		{
		};
		
		struct ArgPGridLayoutInfo:
			public ThisArgs::ArgPGridLayoutInfo
		{
		};
		
		struct ArgPLayoutDefinition:
			public ThisArgs::ArgPLayoutDefinition
		{
		};
		
		struct ArgPVoid:
			public ArgumentsEx<Basic::ArgPVoid>,
			public ThisArgs::ArgPVoid
		{
		};	
		
		struct ArgPRowLayoutInfo:
			public ThisArgs::ArgPRowLayoutInfo
		{
		};


		struct ArgPChar:
			public ArgumentsEx<Basic::ArgPChar>,
			public ThisArgs::ArgPChar
		{
		};	

		struct Callback:
			public ArgumentsEx<ThisCallbacks::Callback>,
			public Basic::Callback
		{
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
		{
		};

		struct Callbacks :
			public Callback,
			public Basic::Callbacks
		{
		};

	protected:
		virtual void check();

		void addChildAddedRemovedCallback(callback_t callback);
		void addChildGettingFocusCallback(callback_t callback);
		void addChildLosingFocusCallback(callback_t callback);
		void addLayoutChangedCallback(callback_t callback);
		void addResizeCallback(callback_t callback);
						
	public:
		Container(int abn);
		Container(PtWidget_t *wdg);

		Container(const Container &rhs);
		
		phevent::bind<Container, &Container::addChildAddedRemovedCallback>		ChildAddedRemoved;
		phevent::bind<Container, &Container::addChildGettingFocusCallback>		ChildGettingFocus;
		phevent::bind<Container, &Container::addChildLosingFocusCallback>		ChildLosingFocus;
		phevent::bind<Container, &Container::addLayoutChangedCallback>			LayoutChanged;
		phevent::bind<Container, &Container::addResizeCallback>				Resize;
	};
	
	INIT_WIDGET_RESOURCE0(Container::ThisArgs::ArgPChar::eArgPChar, String);
	INIT_WIDGET_RESOURCE0(Container::ThisArgs::ArgBool::eArgBool, Boolean);

	INIT_WIDGET_RESOURCE1(Container::ThisArgs::ArgInt::eArgInt, int, Scalar);
	INIT_WIDGET_RESOURCE1(Container::ThisArgs::ArgPFillLayoutInfo::eArgPFillLayoutInfo, PtFillLayoutInfo_t, Struct);
	INIT_WIDGET_RESOURCE1(Container::ThisArgs::ArgPGridLayoutInfo::eArgPGridLayoutInfo, PtGridLayoutInfo_t, Struct);
	INIT_WIDGET_RESOURCE1(Container::ThisArgs::ArgPLayoutDefinition::eArgPLayoutDefinition, PtLayoutDefinition_t, Struct);
	INIT_WIDGET_RESOURCE1(Container::ThisArgs::ArgPRowLayoutInfo::eArgPRowLayoutInfo, PtRowLayoutInfo_t, Struct);
	INIT_WIDGET_RESOURCE1(Container::ThisArgs::ArgPVoid::eArgPVoid, void*, Struct);
	INIT_WIDGET_RESOURCE1(Container::ThisCallbacks::Callback::eCallback, PtCallback_t, Link);
	
	INIT_WIDGET_RESOURCE2(Container::ThisArgs::ArgLong::eArgLong, long, long, Flag);
}


#endif
