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

		struct ThisFlags
		{
			struct Basic
			{
				enum eBasic
				{
					// Edge-control bits:

					top_etch = Pt_TOP_ETCH,
					bottom_etch = Pt_BOTTOM_ETCH,
					left_etch = Pt_LEFT_ETCH,
					right_etch = Pt_RIGHT_ETCH, // Render a single alpha line on an edge of the widget. The top and left lines are dark, and the bottom and right lines are light. This can make a widget look like it's slightly inset. 
					blank_etches = Pt_BLANK_ETCHES, //!< Don't draw the etched lines. 
					opaque_etches = Pt_OPAQUE_ETCHES, //!< Use a solid line, instead of an alpha line, for the etching. The color is calculated based on the widget's color and widget's parent color. 
					top_outline = Pt_TOP_OUTLINE,
					bottom_outline = Pt_BOTTOM_OUTLINE,
					left_outline = Pt_LEFT_OUTLINE,
					right_outline = Pt_RIGHT_OUTLINE, // Render a single-pixel outline on an edge of the widget. 
					top_bevel = Pt_TOP_BEVEL,
					bottom_bevel = Pt_BOTTOM_BEVEL,
					left_bevel = Pt_LEFT_BEVEL,
					right_bevel = Pt_RIGHT_BEVEL, // Render a bevel Pt_ARG_BEVEL_WIDTH pixels wide on an edge of the widget. 
					full_bevels = Pt_FULL_BEVELS, // Render a full bevel (i.e. half-round) instead of a half bevel (quarter-round). 
					top_inline =  Pt_TOP_INLINE,
					bottom_inline = Pt_BOTTOM_INLINE,
					left_inline = Pt_LEFT_INLINE,
					right_inline = Pt_RIGHT_INLINE, // Render a single-pixel inline on an edge of the widget. 

					// These convenience manifests make working with these bits easier:

					top_left_etch = Pt_TOP_LEFT_ETCH, //!< Adjust the etching on the top/left edges. 
					bottom_right_etch = Pt_BOTTOM_RIGHT_ETCH, //!< Adjust the etching on the bottom/right edges. 
					all_etches = Pt_ALL_ETCHES, //!< Adjust the etching on the all edges.  
					top_left_outline = Pt_TOP_LEFT_OUTLINE, //!< Adjust the outline on the top/left edges. 
					bottom_right_outline = Pt_BOTTOM_RIGHT_OUTLINE, //!< Adjust the outline on the bottom/right edges. 
					all_outlines = Pt_ALL_OUTLINES, //!< Adjust the outline on the all edges. 
					top_left_bevel = Pt_TOP_LEFT_BEVEL, //!< Adjust the bevel on the top/left edges. 
					bottom_right_bevel = Pt_BOTTOM_RIGHT_BEVEL, //!< Adjust the bevel on the bottom/right edges. 
					all_bevels = Pt_ALL_BEVELS, //!< Adjust the bevel on the all edges. 
					top_left_inline = Pt_TOP_LEFT_INLINE, //!< Adjust the inline on the top/left edges. 
					bottom_right_inline= Pt_BOTTOM_RIGHT_INLINE, //!< Adjust the inline on the bottom/right edges. 
					all_inlines = Pt_ALL_INLINES, //!< Adjust the inline on the all edges. 
					all_top = Pt_ALL_TOP, //!< Adjust all edge decorations (etch, outline, bevel, and inline) on the top edge. 
					all_bottom = Pt_ALL_BOTTOM, //!< Adjust all edge decorations (etch, outline, bevel, and inline) on the bottom edge. 
					all_left = Pt_ALL_LEFT, //!< Adjust all edge decorations (etch, outline, bevel, and inline) on the left edge. 
					all_right = Pt_ALL_RIGHT, //!< Adjust all edge decorations (etch, outline, bevel, and inline) on the right edge. 
					all = Pt_ALL, //!< Adjust all edge decorations (etch, outline, bevel, and inline) on the all edges. 

					// Fill-control bits:

					flat_fill = Pt_FLAT_FILL, //!<  If set, the widget is filled with a solid color as given by ArgColor::fill_color. If clear, the widget is filled with a gradient. 
					horizontal_gradient = Pt_HORIZONTAL_GRADIENT, //!<  If set, and Pt_FLAT_FILL is clear, the fill gradient changes colors on the horizontal axis. If clear and ArgColor::flat_fill is clear, the fill gradient changes colors on the vertical axis. 
					reverse_gradient = Pt_REVERSE_GRADIENT, //!<  If set and Pt_FLAT_FILL is clear, the gradient rendered is reversed (i.e. begin with the dark fill color on the top or left when the widget isn't pressed). 
					static_bevel_colors = Pt_STATIC_BEVEL_COLORS, //!<  If set, the bevel color doesn't change when you set ArgColor::fill_color. 
					prevent_fill = Pt_BASIC_PREVENT_FILL, //!<  If set, the widget isn't filled. This is useful when you want to set the base color for borders and etches without actually rendering a fill. 

					// Behavior on state change:

					// These bits affect how the widget behaves when set (depressed) or unset (raised):

					static_gradient = Pt_STATIC_GRADIENT, //!<  If set, the gradient doesn't reverse when the widget is set or unset. 
					static_bevels = Pt_STATIC_BEVELS, //!<  If set, the rendered bevels don't change when the widget is set or unset. 
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

		struct Flags:
			public ThisFlags,
			public Widget::Flags
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

		phbitmask<unsigned long, Flags::Basic::eBasic>::bind<Widget, ArgUnsignedLong::eArgUnsignedLong, ArgUnsignedLong::basic_flags>	BasicFlags; //!< Gets or sets basic flags inherited by all widgets. See Flags::Basic::eBasic.

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

cppbitmasks::bitmask<unsigned long, PhWidgets::Basic::Flags::Basic::eBasic> operator|(const PhWidgets::Basic::Flags::Basic::eBasic &flag1, const PhWidgets::Basic::Flags::Basic::eBasic &flag2);
cppbitmasks::bitmask<unsigned long, PhWidgets::Basic::Flags::Basic::eBasic> operator&(const PhWidgets::Basic::Flags::Basic::eBasic &flag1, const PhWidgets::Basic::Flags::Basic::eBasic &flag2);
cppbitmasks::bitmask<unsigned long, PhWidgets::Basic::Flags::Basic::eBasic> operator^(const PhWidgets::Basic::Flags::Basic::eBasic &flag1, const PhWidgets::Basic::Flags::Basic::eBasic &flag2);


#endif
