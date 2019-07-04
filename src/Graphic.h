#ifndef PT_GRAPHIC_H
#define PT_GRAPHIC_H

#include <photon/PtGraphic.h>

#include "./Basic.h"


namespace PhWidgets
{
		
	class Graphic:
		public Basic
	{
	public:

		struct ThisArgs
		{
			
			struct ArgLong
			{
				enum eArgLong
				{
					dash_scale = Pt_ARG_DASH_SCALE, //!< A scaling factor that's applied to each of the bits in the dash list to determine the number of pixels for each dash.
                    line_width = Pt_ARG_LINE_WIDTH //!< The line width for any graphically based widget.
				};
			};	

            struct ArgColor
			{
				enum eArgColor
                {
                    inside_color = Pt_ARG_INSIDE_COLOR //!< The color of the inside of the graphic.
                };
            };

            struct ArgPattern
			{
				enum eArgPattern
				{
					inside_fill_pattern = Pt_ARG_INSIDE_FILL_PATTERN, //!< The background pattern of the inside of the graphic.
					inside_trans_pattern = Pt_ARG_INSIDE_TRANS_PATTERN //!< The transparency pattern for the inside of the graphic. You can use this resource for “ghosting” widgets.
				};
			};
			
			struct ArgUnsignedShort
            {
                enum eArgUnsignedShort
                {
                    line_cap = Pt_ARG_LINE_CAP, //!< Defines how the ends of thick lines are drawn.
                    line_join = Pt_ARG_LINE_JOIN //!< Defines how thick lines are connected
                };
            };

            struct ArgPoint
			{
				enum eArgPoint
				{
					origin = Pt_ARG_ORIGIN //!< A `PhPoint_t` structure that specifies the offset from the upper left corner of the widget's canvas. 
                                           //!< The graphic is rendered with its origin at `Widget::Position + (origin_point)`.
				};
			};

            struct ArgPointArray
            {
				enum eArgPointArray
				{
					points = Pt_ARG_POINTS //!< An array of points (`PhPoint_t` structures) describing the graphic. 
                                           //!< The number of points required in the array and the interpretation of those points depend on the type of graphics primitive being defined. 
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
			
		struct ArgLong:
			public ArgumentsEx<Basic::ArgLong>,
			public ThisArgs::ArgLong
		{
			typedef ThisArgs::ArgLong::eArgLong eArgLong;
		};

		//! Contains resource IDs for Graphic arguments of type `PtColor_t`.
		struct ArgColor:
            public ArgumentsEx<Basic::ArgColor>,
			public ThisArgs::ArgColor
		{
            typedef ThisArgs::ArgColor::eArgColor eArgColor;
		};	

		//! Contains resource IDs for Graphic arguments of type `PgPattern_t`.
		struct ArgPattern:
			public ArgumentsEx<Basic::ArgPattern>,
			public ThisArgs::ArgPattern
		{
            typedef ThisArgs::ArgPattern::eArgPattern eArgPattern;
		};
		
		//! Contains resource IDs for Graphic arguments of type **unsigned short**.
		struct ArgUnsignedShort:
			public ArgumentsEx<Basic::ArgUnsignedShort>,
			public ThisArgs::ArgUnsignedShort
		{
            typedef ThisArgs::ArgUnsignedShort::eArgUnsignedShort eArgUnsignedShort;
		};

		//! Contains resource IDs for Graphic arguments of type `PhPoint_t`.
		struct ArgPoint:
			public ArgumentsEx<Basic::ArgPoint>,
			public ThisArgs::ArgPoint
		{
            typedef ThisArgs::ArgPoint::eArgPoint eArgPoint;
		};

		//! Contains resource IDs for Graphic arguments of `PhPoint_t` array.
		struct ArgPointArray:
			public ThisArgs::ArgPointArray
		{ };

		//! Contains resource IDs for Graphic callbacks of type `PtCallback_t`.
		struct Callback:
			public ArgumentsEx<ThisCallbacks::Callback>,
			public Basic::Callback
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
			//Define::Flag<ThisArgs::ArgLong::eArgLong, long>::

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
