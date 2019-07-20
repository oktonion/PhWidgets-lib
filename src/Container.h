#ifndef PHWIDGETS_CONTAINER_H
#define PHWIDGETS_CONTAINER_H

#include <photon/PtContainer.h>
#include <photon/PtFillLayout.h>

#include "./Basic.h"


namespace PhWidgets
{
	//! Layout and geometry management for all container widgets
	/*!
		The Container superclass provides layout and geometry management for all container widgets. 
		It also redirects certain events—such as button presses, releases, repeats, and keys—to the child that has focus. 
	*/		
	class Container:
		public Basic
	{
	public:

		//! Contains resource IDs for Container arguments.
		struct ThisArgs
		{
			//! Contains resource IDs for Container arguments of type **long**.
			struct ArgLong
			{
				//! Resource IDs for Container arguments of type **long**.

				/*!
					### Aliases ###
					
					PhWidgets::Container::Arguments::eArgLong,
					PhWidgets::Container::ArgLong::eArgLong

					See Widget::resource for usage description.
				*/
				enum eArgLong
				{
					container_flags = Pt_ARG_CONTAINER_FLAGS
				};
			};

			//! Contains resource IDs for Container arguments of type **int**.
			struct ArgInt
			{
				//! Resource IDs for Container arguments of type **long**.

				/*!
					### Aliases ###
					
					PhWidgets::Container::Arguments::eArgInt,
					PhWidgets::Container::ArgInt::eArgInt

					See Widget::resource for usage description.
				*/
				enum eArgInt
				{
					layout_type = Pt_ARG_LAYOUT_TYPE
				};
			};
			
			//! Contains resource IDs for Container arguments of type **bool**.
			struct ArgBool
			{
				//! Resource IDs for Container arguments of type **bool**.

				/*!
					### Aliases ###
					
					PhWidgets::Container::Arguments::eArgBool,
					PhWidgets::Container::ArgBool::eArgBool

					See Widget::resource for usage description.
				*/
				enum eArgBool
				{
					cursor_override = Pt_ARG_CURSOR_OVERRIDE
				};
			};

			//! Contains resource IDs for Container arguments of type `PtFillLayoutInfo_t`.
			struct ArgPFillLayoutInfo
			{
				//! Resource IDs for Container arguments of type `PtFillLayoutInfo_t`.

				/*!
					### Aliases ###
					
					PhWidgets::Container::Arguments::eArgPFillLayoutInfo,
					PhWidgets::Container::ArgPFillLayoutInfo::eArgPFillLayoutInfo

					See Widget::resource for usage description.
				*/
				enum eArgPFillLayoutInfo
				{
					fill_layout_info = Pt_ARG_FILL_LAYOUT_INFO
				};
			};
			
			//! Contains resource IDs for Container arguments of type `PtGridLayoutInfo_t`.
			struct ArgPGridLayoutInfo
			{
				//! Resource IDs for Container arguments of type `PtGridLayoutInfo_t`.

				/*!
					### Aliases ###
					
					PhWidgets::Container::Arguments::eArgPGridLayoutInfo,
					PhWidgets::Container::ArgPGridLayoutInfo::eArgPGridLayoutInfo

					See Widget::resource for usage description.
				*/
				enum eArgPGridLayoutInfo
				{
					grid_layout_info = Pt_ARG_GRID_LAYOUT_INFO
				};
			};
			
			//! Contains resource IDs for Container arguments of type `PtLayoutDefinition_t`.
			struct ArgPLayoutDefinition
			{
				//! Resource IDs for Container arguments of type `PtLayoutDefinition_t`.

				/*!
					### Aliases ###
					
					PhWidgets::Container::Arguments::eArgPLayoutDefinition,
					PhWidgets::Container::ArgPLayoutDefinition::eArgPLayoutDefinition

					See Widget::resource for usage description.
				*/
				enum eArgPLayoutDefinition
				{
					layout = Pt_ARG_LAYOUT
				};
			};
			
			//! Contains resource IDs for Container arguments of type <b>void*</b>.
			struct ArgPVoid
			{
				//! Resource IDs for Container arguments of type <b>void*</b> that are stored in widget.

				/*!
					@note 
					This resource is data that is internally stored in widget as a copy.

					### Aliases ###
					
					PhWidgets::Container::Arguments::eArgPVoidData,
					PhWidgets::Container::ArgPVoid::eArgPVoidData

					See Widget::resource for usage description.
				*/
				enum eArgPVoid
				{
					layout_info = Pt_ARG_LAYOUT_INFO
				};
			};

			//! Contains resource IDs for Container arguments of type `PtRowLayoutInfo_t`.
			struct ArgPRowLayoutInfo
			{
				//! Resource IDs for Container arguments of type `PtRowLayoutInfo_t`.

				/*!
					### Aliases ###
					
					PhWidgets::Container::Arguments::eArgPRowLayoutInfo,
					PhWidgets::Container::ArgPRowLayoutInfo::eArgPRowLayoutInfo

					See Widget::resource for usage description.
				*/
				enum eArgPRowLayoutInfo
				{
					row_layout_info = Pt_ARG_ROW_LAYOUT_INFO
				};
			};

			//! Contains resource IDs for Container arguments of type <b>char*</b>.
			struct ArgPChar
			{
				//! Resource IDs for Container arguments of type <b>char*</b>.

				/*!
					### Aliases ###
					
					PhWidgets::Container::Arguments::eArgPChar,
					PhWidgets::Container::ArgPChar::eArgPChar

					See Widget::resource for usage description.
				*/
				enum eArgPChar
				{
					title = Pt_ARG_TITLE,
					title_font = Pt_ARG_TITLE_FONT
				};
			};	
			
		};

		//! Contains resource IDs for Container callbacks.
		struct ThisCallbacks
		{
			//! Contains resource IDs for Container callbacks of type `PtCallback_t`.
			struct Callback
			{
				//! Resource IDs for Container arguments of type `PtCallback_t`.
				/*!
					### Aliases ###
					
					PhWidgets::Container::Callbacks::eCallback,
					PhWidgets::Container::Callback::eCallback

					See Widget::resource for usage description.
				*/
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
			
		//! Contains resource IDs for arguments of type **long**.
		struct ArgLong:
			public ArgumentsEx<Basic::ArgLong>,
			public ThisArgs::ArgLong
		{
			typedef ThisArgs::ArgLong::eArgLong eArgLong;
		};
		
		//! Contains resource IDs for arguments of type **int**.
		struct ArgInt:
			public ThisArgs::ArgInt,
			public ThisArgs::ArgBool
        { };
		
		//! Contains resource IDs for arguments of type `PtFillLayoutInfo_t`.
		struct ArgPFillLayoutInfo:
			public ThisArgs::ArgPFillLayoutInfo
        { };
		
		//! Contains resource IDs for arguments of type `PtGridLayoutInfo_t`.
		struct ArgPGridLayoutInfo:
			public ThisArgs::ArgPGridLayoutInfo
        { };

		//! Contains resource IDs for arguments of type `PtLayoutDefinition_t`.
		struct ArgPLayoutDefinition:
			public ThisArgs::ArgPLayoutDefinition
        { };
		
		//! Contains resource IDs for arguments of type <b>void*</b>.
		struct ArgPVoid:
			public ArgumentsEx<Basic::ArgPVoid>,
			public ThisArgs::ArgPVoid
		{
			typedef ThisArgs::ArgPVoid::eArgPVoid eArgPVoid;
		};	

		//! Contains resource IDs for arguments of type `PtRowLayoutInfo_t`.
		struct ArgPRowLayoutInfo:
			public ThisArgs::ArgPRowLayoutInfo
        { };


		//! Contains resource IDs for arguments of type <b>char*</b>.
		struct ArgPChar:
			public ArgumentsEx<Basic::ArgPChar>,
			public ThisArgs::ArgPChar
		{
			typedef ThisArgs::ArgPChar::eArgPChar eArgPChar;
		};	

		//! Contains resource IDs for callbacks of type `PtCallback_t`.
		struct Callback:
			public ArgumentsEx<Basic::Callback>,
			public ThisCallbacks::Callback
		{
			typedef ThisCallbacks::Callback::eCallback eCallback;
		};

		//! Contains resource IDs for all Container arguments.
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

		//! Contains resource IDs for all Container callbacks.
		struct Callbacks:
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
