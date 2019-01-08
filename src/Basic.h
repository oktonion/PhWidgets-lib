#ifndef PT_BASIC_H
#define PT_BASIC_H

#include <photon/PtBasic.h>

#include "./Widget.h"


namespace PhWidgets
{
		
	class Basic:
		public Widget
	{
	public:

		struct ThisArgs
		{
			struct ArgUnsignedShort
			{
				enum eArgUnsignedShort
				{
					margin_height = Pt_ARG_MARGIN_HEIGHT, //!< The amount of vertical space between the widget's canvas and the widget's border. The canvas is the valid drawing area of the widget and is inside all borders and margins.
					margin_width = Pt_ARG_MARGIN_WIDTH //!< The amount of horizontal space between the widget's canvas and the widget's border. The canvas is the valid drawing area of the widget and is inside all borders and margins.
				};
			};
			
			struct ArgUnsignedLong
			{
				enum eArgUnsignedLong
				{
					bandwidth_threshold = Pt_ARG_BANDWIDTH_THRESHOLD, //!< Can't be set! In general, it defines a threshold below which a widget optimizes drawing on a system with a slow connection.
					basic_flags = Pt_ARG_BASIC_FLAGS //!< This flag resource controls which “edge decorations” are rendered for a widget when it's highlighted
				};
			};

			struct ArgColor
			{
				enum eArgColor
				{
					bevel_color = Pt_ARG_BEVEL_COLOR, //!< The main color of the bevel.
					color = Pt_ARG_COLOR, //!< The widget's foreground or drawing color.
					dark_bevel_color = Pt_ARG_DARK_BEVEL_COLOR, //!< This resource, with \link Basic::ArgColor::light_bevel_color light_bevel_color\endlink, specifies the outermost colors used when applying a bevel to a widget.
					dark_fill_color = Pt_ARG_DARK_FILL_COLOR, //!< This resource, with \link Basic::ArgColor::light_fill_color light_fill_color\endlink, specifies the colors with which a gradient (if applied) starts and ends.
					fill_color = Pt_ARG_FILL_COLOR, //!< The base fill color for the widget.
					inline_color = Pt_ARG_INLINE_COLOR, //!< The color of the inline of the border.
					light_bevel_color = Pt_ARG_LIGHT_BEVEL_COLOR, //!< This resource, with \link Basic::ArgColor::dark_bevel_color dark_bevel_color\endlink, specifies the outermost colors used when applying a bevel to a widget.
					light_fill_color = Pt_ARG_LIGHT_FILL_COLOR, //!< This resource, with \link Basic::ArgColor::dark_fill_color dark_fill_color\endlink, specifies the colors with which a gradient (if applied) starts and ends.
					outline_color = Pt_ARG_OUTLINE_COLOR //!< The color of the outline of the border.
				};
			};

			struct ArgChar
			{		
				enum eArgChar
				{
					bevel_contrast = Pt_ARG_BEVEL_CONTRAST, //!< This value determines how much the dark and light bevel colors differ from the \link Basic::ArgColor::bevel_color base bevel color\endlink. The higher the value, the greater the difference
					contrast = Pt_ARG_CONTRAST //!< This value determines how much the dark and light fill colors differ from the \link Basic::ArgColor::fill_color base fill color\endlink. The higher the value, the greater the difference
				};
			};
			
			struct ArgPattern
			{
				enum eArgPattern
				{
					fill_pattern = Pt_ARG_FILL_PATTERN, //!< The widget's background pattern.
					trans_pattern = Pt_ARG_TRANS_PATTERN //!< The widget's transparency pattern. You'll find this handy for “ghosting” widgets.
				};
			};
			
			struct ArgUnsignedChar
			{
				enum eArgUnsignedChar
				{
					highlihgt_roundness = Pt_ARG_HIGHLIGHT_ROUNDNESS //!< The radius, in pixels, of the widget's borders. The default value of 0 results in square corners.
				};
			};
			
			struct ArgPChar
			{
				enum eArgPChar
				{
					style = Pt_ARG_STYLE //!< The style to use for this widget instance.
				};
			};	
		};

		struct ThisCallbacks
		{
			struct Callback
			{
				enum eCallback
				{
					activate = Pt_CB_ACTIVATE, 	//!< A list of PtCallback_t structures that define the callbacks that the widget calls when it becomes activated.
												//!< To activate a widget, you typically release the left pointer button while pointing at an armed widget.

					arm = Pt_CB_ARM, //!< A list of PtCallback_t structures that define the callbacks that the widget calls when it becomes armed.
									 //!< To arm a widget, you typically press the left pointer button while pointing at the widget.

					disarm = Pt_CB_DISARM, 	//!< A list of PtCallback_t structures that define the callbacks that the widget calls when it becomes disarmed. 
											//!< To disarm a widget, you typically release the left pointer button when not pointing at an armed widget. 

					got_focus = Pt_CB_GOT_FOCUS, //!< A list of PtCallback_t structures that define the callbacks invoked when a widget gets focus or its focus status changes 
												 //!< (e.g. a child widget gets focus from its parent or the focus switches from a child to its parent).

					lost_focus = Pt_CB_LOST_FOCUS, //!< A list of PtCallback_t structures that define the callbacks that the widget calls when it loses focus.

					menu = Pt_CB_MENU, //!< A list of PtCallback_t structures that define the callbacks that the widget calls when you press the right button while the pointer is on top of the widget.

					repeat = Pt_CB_REPEAT 	//!< A list of PtCallback_t structures that define the callbacks that the widget calls when it receives Ph_EV_BUT_REPEAT events. 
											//!< These events occur when you hold down the left pointer button (or the right pointer button if the widget has Pt_ALL_BUTTONS set in its Pt_ARG_FLAGS resource).
				};
			};
		};

		struct ArgUnsignedShort:
			public ArgumentsEx<Widget::ArgUnsignedShort>,
			public ThisArgs::ArgUnsignedShort
		{
			typedef ThisArgs::ArgUnsignedShort::eArgUnsignedShort eArgUnsignedShort;
		};
			
		struct ArgUnsignedLong:
			public ArgumentsEx<Widget::ArgUnsignedLong>,
			public ThisArgs::ArgUnsignedLong
		{
			typedef ThisArgs::ArgUnsignedLong::eArgUnsignedLong eArgUnsignedLong;
		};

		struct ArgColor:
			public ArgumentsEx<Widget::ArgColor>,
			public ThisArgs::ArgColor
		{
			typedef ThisArgs::ArgColor::eArgColor eArgColor;
		};

		struct ArgChar:
			public ThisArgs::ArgChar
		{
		};
			
		struct ArgPattern:
			public ThisArgs::ArgPattern
		{
		};
			
		struct ArgUnsignedChar:
			public ThisArgs::ArgUnsignedChar
		{
		};

		struct ArgPChar:
			public ArgumentsEx<Widget::ArgPChar>,
			public ThisArgs::ArgPChar
		{
			typedef ThisArgs::ArgPChar::eArgPChar eArgPChar;
		};	

		struct Callback:
			public ArgumentsEx<ThisCallbacks::Callback>,
			public Widget::Callback
		{
			typedef ThisCallbacks::Callback::eCallback eCallback;
		};

		struct Arguments:
			public ArgUnsignedShort,
			public ArgUnsignedLong,
			public ArgColor,
			public ArgChar,
			public ArgPattern,
			public ArgUnsignedChar,
			public ArgPChar,
			public Widget::Arguments
		{
		};

		struct Callbacks :
			public Callback,
			public Widget::Callbacks
		{
		};

	protected:

		typedef ResourceFrom<Widget::WidgetResourcesSingleton>::
			Define::String<ThisArgs::ArgPChar::eArgPChar>::
			Define::Color<ThisArgs::ArgColor::eArgColor>::
			Define::Scalar<ThisArgs::ArgUnsignedShort::eArgUnsignedShort, unsigned short>::
			Define::Scalar<ThisArgs::ArgChar::eArgChar, char>::
			//Define::Flag<ThisArgs::ArgLong::eArgLong, long>::
			Define::Flag<ThisArgs::ArgUnsignedLong::eArgUnsignedLong, unsigned long>::
			//Define::Flag<ThisArgs::ArgUnsigned::eArgUnsigned, unsigned>::

			Define::Link<ThisCallbacks::Callback::eCallback, PtCallback_t*>::

		resource_type WidgetResourcesSingleton;

		virtual void check();
						
	public:
		Basic(int abn);
		Basic(PtWidget_t *wdg);
		
		Basic(const Basic &rhs);

		Basic &operator=(const Basic &rhs);

		WidgetResourcesSingleton resource;
		
		//! @name Properties
		//! @{ 
		phproperty<PgColor_t>::bind<Basic, ArgColor::eArgColor, Arguments::color> Color; //!< The widget's foreground or drawing color.
		phproperty<PgColor_t>::bind<Basic, ArgColor::eArgColor, Arguments::fill_color> FillColor; //!< The base fill color for the widget.
		//! @}

		//! @name Events
		//! @{ 
		phwidgets_event<Basic, Basic::Callbacks::activate>		Activate; //!< Occurs when you release the left pointer button while pointing at an armed widget.
		phwidgets_event<Basic, Basic::Callbacks::arm>			Arm; //!< Occurs when you press the left pointer button while pointing at the widget.
		phwidgets_event<Basic, Basic::Callbacks::disarm>		Disarm; //!< Occurs when you release the left pointer button when not pointing at an armed widget.
		phwidgets_event<Basic, Basic::Callbacks::got_focus>		GotFocus; //!< Occurs when a widget gets focus or its focus status changes.
		phwidgets_event<Basic, Basic::Callbacks::lost_focus>	LostFocus; //!< Occurs when a widget loses focus.
		phwidgets_event<Basic, Basic::Callbacks::menu>			Menu; //!< Occurs when you press the right button while the pointer is on top of the widget.
		phwidgets_event<Basic, Basic::Callbacks::repeat>		Repeat; //!< Documentation in progress...
		//! @}

		//! @name Event raisers
		//! @{
		void OnActivated(PtCallbackInfo_t *info); //!< Raises the Basic::Activate event.
		void OnArmed(PtCallbackInfo_t *info); //!< Raises the Basic::Arm event.
		void OnDisarmed(PtCallbackInfo_t *info); //!< Raises the Basic::Disarm event.
		void OnGotFocused(PtCallbackInfo_t *info); //!< Raises the Basic::GotFocus event.
		void OnLostFocus(PtCallbackInfo_t *info); //!< Raises the Basic::LostFocus event.
		void OnMenu(PtCallbackInfo_t *info); //!< Raises the Basic::Menu event.
		void OnRepeat(PtCallbackInfo_t *info); //!< Raises the Basic::Repeat event.
		//! @}
	};		  


	
}


#endif
