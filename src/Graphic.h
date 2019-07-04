#ifndef PT_GRAPHIC_H
#define PT_GRAPHIC_H

#include <photon/PtGraphic.h>

#include "./Basic.h"


namespace PhWidgets
{
	//! Common resources for graphical widgets
	/*!
		The Graphic superclass provides the common resources used by all graphic widgets. 
		Graphical widgets provide attributes for color, fills, patterns, line thickness, joins, and much more.

		@remark
		When you want to incorporate simple, static drawings in your interface, use the subclasses of Graphic. 

		@see
		- Arc
		- Bezier
		- Ellipse
		- Grid
		- Line
		- Pixel
		- Polygon
		- Rect
	*/	
	class Graphic:
		public Basic
	{
	public:

		//! Contains resource IDs for Graphic arguments.
		struct ThisArgs
		{
			//! Contains resource IDs for Graphic arguments of type **long**.
			struct ArgLong
			{
				//! Resource IDs for Graphic arguments of type **long**.

				/*!
					### Aliases ###
					
					PhWidgets::Graphic::Arguments::eArgLong,
					PhWidgets::Graphic::ArgLong::eArgLong

					See Widget::resource for usage description.
				*/
				enum eArgLong
				{
					dash_scale = Pt_ARG_DASH_SCALE, //!< A scaling factor that's applied to each of the bits in the dash list to determine the number of pixels for each dash.
                    line_width = Pt_ARG_LINE_WIDTH //!< The line width for any graphically based widget.
				};
			};	

			//! Contains resource IDs for Graphic arguments of type `PtColor_t`.
            struct ArgColor
			{
				//! Resource IDs for Graphic arguments of type `PtColor_t`.

				/*!
					### Aliases ###
					
					PhWidgets::Graphic::Arguments::eArgColor,
					PhWidgets::Graphic::ArgColor::eArgColor

					See Widget::resource for usage description.
				*/
				enum eArgColor
                {
                    inside_color = Pt_ARG_INSIDE_COLOR //!< The color of the inside of the graphic.
                };
            };

			//! Contains resource IDs for Graphic arguments of type `PgPattern_t`.
            struct ArgPattern
			{
				//! Resource IDs for Graphic arguments of type `PgPattern_t`.

				/*!
					### Aliases ###
					
					PhWidgets::Graphic::Arguments::eArgPattern,
					PhWidgets::Graphic::ArgPattern::eArgPattern

					See Widget::resource for usage description.
				*/
				enum eArgPattern
				{
					inside_fill_pattern = Pt_ARG_INSIDE_FILL_PATTERN, //!< The background pattern of the inside of the graphic.
					inside_trans_pattern = Pt_ARG_INSIDE_TRANS_PATTERN //!< The transparency pattern for the inside of the graphic. You can use this resource for “ghosting” widgets.
				};
			};
			
			//! Contains resource IDs for Graphic arguments of type **unsigned short**.
			struct ArgUnsignedShort
            {
				//! Resource IDs for Graphic arguments of type **unsigned short**.

				/*!
					### Aliases ###
					
					PhWidgets::Graphic::Arguments::eArgUnsignedShort,
					PhWidgets::Graphic::ArgUnsignedShort::eArgUnsignedShort

					See Widget::resource for usage description.
				*/
                enum eArgUnsignedShort
                {
                    line_cap = Pt_ARG_LINE_CAP, //!< Defines how the ends of thick lines are drawn.
                    line_join = Pt_ARG_LINE_JOIN //!< Defines how thick lines are connected
                };
            };

			//! Contains resource IDs for Graphic arguments of type `PhPoint_t`.
            struct ArgPoint
			{
				//! Resource IDs for Graphic arguments of type `PhPoint_t`.

				/*!
					### Aliases ###
					
					PhWidgets::Graphic::Arguments::eArgPoint,
					PhWidgets::Graphic::ArgPoint::eArgPoint

					See Widget::resource for usage description.
				*/
				enum eArgPoint
				{
					origin = Pt_ARG_ORIGIN //!< A `PhPoint_t` structure that specifies the offset from the upper left corner of the widget's canvas. 
                                           //!< The graphic is rendered with its origin at `Widget::Position + (origin_point)`.
				};
			};

			//! Contains resource IDs for Graphic arguments of `PhPoint_t` array.
            struct ArgPointArray
            {
				//! Resource IDs for Graphic arguments of `PhPoint_t` array.

				/*!
					### Aliases ###
					
					PhWidgets::Graphic::Arguments::eArgPointArray,
					PhWidgets::Graphic::ArgPointArray::eArgPointArray

					See Widget::resource for usage description.
				*/
				enum eArgPointArray
				{
					points = Pt_ARG_POINTS //!< An array of points (`PhPoint_t` structures) describing the graphic. 
                                           //!< The number of points required in the array and the interpretation of those points depend on the type of graphics primitive being defined. 
				};
            };

			//! Contains resource IDs for Graphic arguments of type **char**.
			struct ArgChar
			{
				//! Resource IDs for Graphic arguments of type **char**.

				/*!
					### Aliases ###
					
					PhWidgets::Graphic::Arguments::eArgChar,
					PhWidgets::Graphic::ArgChar::eArgChar

					See Widget::resource for usage description.
				*/
				enum eArgChar
				{
					graphic_flags = Pt_ARG_GRAPHIC_FLAGS //!< Graphics flags. See Graphic::Flags::eGraphicFlags for possible values.
				};
			};
			
		};

        //! Contains resource IDs for Graphic callbacks.
		struct ThisCallbacks
		{
            //! Contains resource IDs for Graphic callbacks of type `PtCallback_t`.
			struct Callback
			{
                //! Resource IDs for Graphic arguments of type `PtCallback_t`.
				/*!
					### Aliases ###
					
					PhWidgets::Graphic::Callbacks::eCallback,
					PhWidgets::Graphic::Callback::eCallback

					See Widget::resource for usage description.
				*/
				enum eCallback
				{
					rescale = Pt_CB_RESCALE //!< A list of `PtCallback_t` structures that define the callbacks that the widget invokes 
                                            //!< if its Widget::Arguments::dim or Widget::Arguments::area resource is modified. 
                                            //!< You can use this callback to rescale the widget. 
				};
			};
		};

		//! Contains flags for Graphic resources.
		struct ThisFlags
		{
			//! Graphics flags for Graphic resource Graphic::Arguments::graphic_flags.
			/*!
				The default setting of Graphic::Arguments::graphic_flags resource is 0; that is, no flags have been set. 

				### Aliases ###
				
				PhWidgets::Graphic::Flags::eGraphicFlags
			*/
			enum eGraphicFlags
			{
				/*!
					Adjust the position and origin of the Widget,
					but leave the Graphic in place relative to the widget's parent. 
					The upper left corner of the widget's canvas
					is at the upper left corner of the bounding box described by the point array. 
					Depending on its resize policy, the widget may resize to fit the rendering. 
				*/
				FloatPos = Pt_FLOAT_POS, 

				/*!
					Adjust the origin of the Graphic, 
					but leave the Widget in place relative to its parent. 
					The upper left corner of the bounding box described by the point array
					is at the upper left corner of the widget's canvas.  
				*/
				FloatOrigin = Pt_FLOAT_ORIGIN
			};
		};
			
		struct ArgLong:
			public ArgumentsEx<Basic::ArgLong>,
			public ThisArgs::ArgLong
		{
			typedef ThisArgs::ArgLong::eArgLong eArgLong;
		};

		//! Contains resource IDs for arguments of type `PtColor_t`.
		struct ArgColor:
            public ArgumentsEx<Basic::ArgColor>,
			public ThisArgs::ArgColor
		{
            typedef ThisArgs::ArgColor::eArgColor eArgColor;
		};	

		//! Contains resource IDs for arguments of type `PgPattern_t`.
		struct ArgPattern:
			public ArgumentsEx<Basic::ArgPattern>,
			public ThisArgs::ArgPattern
		{
            typedef ThisArgs::ArgPattern::eArgPattern eArgPattern;
		};
		
		//! Contains resource IDs for arguments of type **unsigned short**.
		struct ArgUnsignedShort:
			public ArgumentsEx<Basic::ArgUnsignedShort>,
			public ThisArgs::ArgUnsignedShort
		{
            typedef ThisArgs::ArgUnsignedShort::eArgUnsignedShort eArgUnsignedShort;
		};

		//! Contains resource IDs for arguments of type `PhPoint_t`.
		struct ArgPoint:
			public ArgumentsEx<Basic::ArgPoint>,
			public ThisArgs::ArgPoint
		{
            typedef ThisArgs::ArgPoint::eArgPoint eArgPoint;
		};

		//! Contains resource IDs for arguments of `PhPoint_t` array.
		struct ArgPointArray:
			public ThisArgs::ArgPointArray
		{ };

		//! Contains resource IDs for arguments of type **char**.
		struct ArgChar:
			public ArgumentsEx<Basic::ArgChar>,
			public ThisArgs::ArgChar
        { };

		//! Contains resource IDs for callbacks of type `PtCallback_t`.
		struct Callback:
			public ArgumentsEx<Basic::Callback>,
			public ThisCallbacks::Callback
		{
			typedef ThisCallbacks::Callback::eCallback eCallback;
		};

		//! Contains resource IDs for all Graphic arguments.
		struct Arguments:
			public ArgLong,
			public ArgColor,
			public ArgPattern,
			public ArgUnsignedShort,
			public ArgPoint,
			public ArgPointArray,
			public Basic::Arguments
		{ };

		//! Contains resource IDs for all Graphic callbacks.
		struct Callbacks :
			public Callback,
			public Basic::Callbacks
		{ };

	protected:
		typedef ResourceFrom<Basic::WidgetResourcesSingleton>::
			Define::Scalar<ThisArgs::ArgLong::eArgLong, long>::
			Define::Color<ThisArgs::ArgColor::eArgColor>::
			Define::Struct<ThisArgs::ArgPattern::eArgPattern, PgPattern_t>::
			Define::Scalar<ThisArgs::ArgUnsignedShort::eArgUnsignedShort, unsigned short>::
			Define::Struct<ThisArgs::ArgPoint::eArgPoint, PhPoint_t>::
			Define::Array<ThisArgs::ArgPointArray::eArgPointArray, PhPoint_t>::
			Define::Flag<ThisArgs::ArgChar::eArgChar, char>::

			Define::Link<ThisCallbacks::Callback::eCallback, PtCallback_t*>::

		resource_type WidgetResourcesSingleton;

		virtual void check();
						
	public:
		WidgetResourcesSingleton resource;

		Graphic(int abn);
		Graphic(PtWidget_t *wdg);

		Graphic(const Graphic &rhs);

		Graphic &operator=(const Graphic &rhs);
		
		phwidgets_event<Graphic, Graphic::Callbacks::rescale>	Rescale;
	};
}


#endif // PT_GRAPHIC_H
