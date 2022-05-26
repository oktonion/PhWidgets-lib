#ifndef PHWIDGETS_GAUGE_H
#define PHWIDGETS_GAUGE_H

#include <photon/PtGauge.h>

#include "./Basic.h"
#include "./Drawing/Font.h"


namespace PhWidgets
{
	/*!
		@struct PhWidgets::Gauge
		@ingroup Widgets
	*/

	//! Common class for gauge-type widgets
	/*!
		The Gauge superclass provides common functionality for gauge-like widgets, 
        which are capabale of displaying a range of values.
	*/		
	class Gauge:
		public Basic
	{
	public:

		//! Contains resource IDs for Gauge arguments. @ingroup Resources
		struct ThisArgs
		{
			//! Contains resource IDs for Gauge arguments of type **long**.
			struct ArgLong
			{
				//! Resource IDs for Gauge arguments of type **long**.

				/*!
					### Aliases ###
					
					PhWidgets::Gauge::Arguments::eArgLong,
					PhWidgets::Gauge::ArgLong::eArgLong

					See Widget::resource for usage description.
				*/
				enum eArgLong
				{
					gauge_value = Pt_ARG_GAUGE_VALUE, //!< The gauge's current value. 
                    maximum = Pt_ARG_MAXIMUM, //!< The maximum value of the gauge.
                    minimum = Pt_ARG_MINIMUM //!< The minimum value of the gauge.
				};
			};

			//! Contains resource IDs for Gauge arguments of type **short**.
			struct ArgShort
			{
				//! Resource IDs for Gauge arguments of type **short**.

				/*!
					### Aliases ###
					
					PhWidgets::Gauge::Arguments::eArgShort,
					PhWidgets::Gauge::ArgShort::eArgShort

					See Widget::resource for usage description.
				*/
				enum eArgShort
				{
					gauge_flags = Pt_ARG_GAUGE_FLAGS //!< Gauge [flags](@ref Gauge::Flags::eGaugeFlags).
				};
			};
			
			//! Contains resource IDs for Gauge arguments of type **char**.
			struct ArgChar
			{
				//! Resource IDs for Gauge arguments of type **char**.

				/*!
					### Aliases ###
					
					PhWidgets::Gauge::Arguments::eArgChar,
					PhWidgets::Gauge::ArgChar::eArgChar

					See Widget::resource for usage description.
				*/
				enum eArgChar
				{
					gauge_orientation = Pt_ARG_GAUGE_ORIENTATION //!< Indicates whether the gauge will be drawn vertically or horizontally. @see PhWidgets::Gauge::Flags::Orientation::eOrientation
				};
			};

			//! Contains resource IDs for Gauge arguments of type **unsigned char**.
			struct ArgUnsignedChar
			{
				//! Resource IDs for Gauge arguments of type **unsigned char**.

				/*!
					### Aliases ###
					
					PhWidgets::Gauge::Arguments::eArgUnsignedChar,
					PhWidgets::Gauge::ArgUnsignedChar::eArgUnsignedChar

					See Widget::resource for usage description.
				*/
				enum eArgUnsignedChar
				{
					gauge_horizontal_align = Pt_ARG_GAUGE_H_ALIGN, //!< Controls horizontal alignment. @see PhWidgets::Gauge::Flags::Alignment::eHorizontal
                    gauge_vertical_align = Pt_ARG_GAUGE_V_ALIGN //!< Controls vertical alignment. @see PhWidgets::Gauge::Flags::Alignment::eVertical
				};
			};

			//! Contains resource IDs for Gauge arguments of type <b>char*</b>.
			struct ArgPChar
			{
				//! Resource IDs for Gauge arguments of type <b>char*</b>.

				/*!
					### Aliases ###
					
					PhWidgets::Gauge::Arguments::eArgPChar,
					PhWidgets::Gauge::ArgPChar::eArgPChar

					See Widget::resource for usage description.
				*/
				enum eArgPChar
				{
					value_prefix = Pt_ARG_GAUGE_VALUE_PREFIX, //!< Text prefixed to the value displayed. For example, Red: would result in Red:35. @default `NULL`
                    value_suffix = Pt_ARG_GAUGE_VALUE_SUFFIX, //!< Text appended to the value displayed. For example, % would result in 35%. @default `NULL`
					gauge_font = Pt_ARG_GAUGE_FONT //!< The font used for displaying the value, title, and any other text. @default "helv12"
				};
			};	
			
		};

        //! Contains flags for Gauge resources.
		struct ThisFlags
		{	
            //! Contains flags for Gauge resource Gauge::Arguments::gauge_flags.
            struct Gauge
            {
                //! Common flags for Gauge resource Gauge::Arguments::gauge_flags.
                /*! 
                    Common flags used by all gauge-like widgets.

                    ### Aliases ###
                        
                    PhWidgets::Gauge::Flags::Gauge::eGaugeFlags
                */
                enum eGaugeFlags
                {

#ifndef Pt_SHOW_VALUE
    #define Pt_SHOW_VALUE_IMPL Pt_GAUGE_SHOW_VALUE
#else
    #define Pt_SHOW_VALUE_IMPL Pt_SHOW_VALUE
#endif

#ifndef Pt_VALUE_XOR
    #define Pt_VALUE_XOR_IMPL Pt_GAUGE_VALUE_XOR
#else
    #define Pt_VALUE_XOR_IMPL Pt_VALUE_XOR
#endif

#ifndef Pt_GAUGE_MAX_ON_RIGHT
    #define Pt_GAUGE_MAX_ON_RIGHT_IMPL 0
#else
    #define Pt_GAUGE_MAX_ON_RIGHT_IMPL Pt_GAUGE_MAX_ON_RIGHT
#endif

#ifndef Pt_GAUGE_MAX_ON_BOTTOM
    #define Pt_GAUGE_MAX_ON_BOTTOM_IMPL 0
#else
    #define Pt_GAUGE_MAX_ON_BOTTOM_IMPL Pt_GAUGE_MAX_ON_BOTTOM
#endif

#ifndef Pt_GAUGE_INDETERMINATE
    #define Pt_GAUGE_INDETERMINATE_IMPL 0
#else
    #define Pt_GAUGE_INDETERMINATE_IMPL Pt_GAUGE_INDETERMINATE
#endif

#ifndef Pt_GAUGE_INTERACTIVE
    #define Pt_GAUGE_INTERACTIVE_IMPL 0
#else
    #define Pt_GAUGE_INTERACTIVE_IMPL Pt_GAUGE_INTERACTIVE
#endif

                    ShowValue = Pt_SHOW_VALUE_IMPL, //!< Indicates whether or not the value of the gauge will be displayed. 
                    ValueXOR = Pt_VALUE_XOR_IMPL, //!< XOR the value display with the background (i.e. invert the fill of the type face).
                    MaximumOnTop = Pt_GAUGE_MAX_ON_TOP, //!< Place position of the maximum value to top.
                    MaximumOnRight = Pt_GAUGE_MAX_ON_RIGHT_IMPL, //!< Place position of the maximum value to right.
                    MaximumOnLeft = Pt_GAUGE_MAX_ON_LEFT, //!< Place position of the maximum value to left.
                    MaximumOnBottom = Pt_GAUGE_MAX_ON_BOTTOM_IMPL, //!< Place position of the maximum value to bottom.
                    Indeterminate = Pt_GAUGE_INDETERMINATE_IMPL, 
                    Interactive = Pt_GAUGE_INTERACTIVE_IMPL

#undef Pt_SHOW_VALUE_IMPL
#undef Pt_VALUE_XOR_IMPL
#undef Pt_GAUGE_MAX_ON_RIGHT_IMPL
#undef Pt_GAUGE_MAX_ON_BOTTOM_IMPL
#undef Pt_GAUGE_INDETERMINATE_IMPL
#undef Pt_GAUGE_INTERACTIVE_IMPL
                };
            };

            //! Contains flags for Gauge resource Gauge::Arguments::gauge_orientation.
			struct Orientation
            {
                //! Orientation flags for Gauge resource Gauge::Arguments::gauge_orientation.
				/*!
					Orientation flags to control a gauge orientation.

                ### Aliases ###
					
					PhWidgets::Gauge::Flags::Orientation::eOrientation
				*/
                enum eOrientation
                {
                    Horizontal = Pt_HORIZONTAL, //!< The gauge will be drawn horizontally.
                    Vertical = Pt_VERTICAL //!< The gauge will be drawn vertically.
                };
            };

            //! Contains flags for Gauge resource Gauge::Arguments::gauge_horizontal_align and Gauge::Arguments::gauge_vertical_align.
			struct Alignment
            {
                //! Contains flags for Gauge resource Gauge::Arguments::gauge_horizontal_align.
                struct Horizontal
                {
                    //! Horizontal alignment flags for Gauge resource Gauge::Arguments::gauge_horizontal_align.
                    /*!
                        Alignment flags to control a gauge horizontal alignment.

                    ### Aliases ###
                        
                        PhWidgets::Gauge::Flags::Alignment::eHorizontal
                    */
                    enum eHorizontal
                    {
                        Left = Pt_LEFT, //!< Draw the value aligned to the left edge. 
                        Right = Pt_RIGHT, //!< Draw the value aligned to the right edge. 
                        Center = Pt_CENTER //!< Draw the value centered.
                    };
                };

                //! Contains flags for Gauge resource Gauge::Arguments::gauge_vertical_align.
                struct Vertical
                {
                    //! Vertical alignment flags for Gauge resource Gauge::Arguments::gauge_vertical_align.
                    /*!
                        Alignment flags to control a gauge vertical alignment.

                    ### Aliases ###
                        
                        PhWidgets::Gauge::Flags::Alignment::eVertical
                    */
                    enum eVertical
                    {
                        Top = Pt_TOP, //!< Draw the value aligned with the top edge. 
                        Bottom = Pt_BOTTOM, //!< Draw the value aligned with the bottom edge. 
                        Center = Pt_CENTER //!< Draw the value centered. 
                    };
                };
            };
        };

		//! Contains resource IDs for arguments of type **long**. @ingroup Resources
		struct ArgLong:
			public ArgumentsEx<Basic::ArgLong>,
			public ThisArgs::ArgLong
		{
			typedef ThisArgs::ArgLong::eArgLong eArgLong;
		};
		
		//! Contains resource IDs for arguments of type **short**. @ingroup Resources
		struct ArgShort:
			public ThisArgs::ArgShort
        { };
		
		//! Contains resource IDs for arguments of type **char**. @ingroup Resources
		struct ArgChar:
			public ArgumentsEx<Basic::ArgChar>,
			public ThisArgs::ArgChar
		{
			typedef ThisArgs::ArgChar::eArgChar eArgChar;
		};	

        //! Contains resource IDs for arguments of type **unsigned char**. @ingroup Resources
		struct ArgUnsignedChar:
			public ArgumentsEx<Basic::ArgUnsignedChar>,
			public ThisArgs::ArgUnsignedChar
		{
			typedef ThisArgs::ArgUnsignedChar::eArgUnsignedChar eArgUnsignedChar;
		};

		//! Contains resource IDs for arguments of type <b>char*</b>. @ingroup Resources
		struct ArgPChar:
			public ArgumentsEx<Basic::ArgPChar>,
			public ThisArgs::ArgPChar
		{
			typedef ThisArgs::ArgPChar::eArgPChar eArgPChar;
		};	

		//! Contains resource IDs for all Gauge arguments. @ingroup Resources
		struct Arguments:
			public ArgLong,
			public ArgShort,
			public ArgChar,
            public ArgUnsignedChar,
			public ArgPChar,
			public Basic::Arguments
        { };

        //! Contains flags for all Gauge resources. @ingroup Resources
		struct Flags:
			public ThisFlags,
			public Basic::Flags
        { };

	protected:
		typedef ResourceFrom<Basic::WidgetResourcesSingleton>::
			Define::String<ThisArgs::ArgPChar::eArgPChar>::
			Define::Scalar<ThisArgs::ArgLong::eArgLong, long>::
			Define::Flag<ThisArgs::ArgShort::eArgShort, short int>::
			Define::Scalar<ThisArgs::ArgChar::eArgChar, char>::
            Define::Scalar<ThisArgs::ArgUnsignedChar::eArgUnsignedChar, unsigned char>::

		resource_type WidgetResourcesSingleton;

        Drawing::Font getFont() const;
		void setFont(Drawing::Font);

        std::string getPrefix() const;
        void setPrefix(std::string text);

        std::string getSuffix() const;
        void setSuffix(std::string text);

		virtual void check();
        
						
	public:
		//! Resources of the Gauge
		/*!
			@see
			- Widget::resource
		*/
		WidgetResourcesSingleton resource;

		//! (constructor) 
		/*!
			Constructs a Gauge widget by ID.
			@param[in] abn ID given by PhAB to widget (like 'ABN_WIDGET_NAME').
		*/
		explicit Gauge(int abn);

		//! (constructor) 
		/*!
			Constructs a Gauge widget by pointer to widget.
			@param[in] wdg pointer to Photon widget.
		*/		
		explicit Gauge(PtWidget_t *wdg);

		//! (copy constructor) 
		/*!
			Constructs a Gauge widget by copy.
			@param[in] other another Gauge widget to be used as source to initialize the elements of the container with.
		*/
		Gauge(const Gauge &other);

		//! Assigns value in Gauge widget 
		/*!
			Replaces the contents of the Gauge widget.
			@param[in] other another Gauge widget to use as data source.
		*/
		Gauge &operator=(const Gauge &other);

		//! @name Properties
		//! Properties are used to simplify use of widget resources.
		//@{

        //! Gets or sets the font of the value, title, and any other text in the Gauge.
		/*!
			### Property Value ### 
			
			> Drawing::Font

			The Drawing::Font used for displaying the value, title, and any other text. 
            The default is the font set by the container.
			
			@remark
			The Gauge::Font property is an ambient property. 
			An ambient property is a widget property that, if not set, is retrieved from the parent widget. 
			For example, a Button will have the same BackColor as its parent PhWidgets::Window by default.
			@par
			Because the Gauge::Font is immutable (meaning that you cannot adjust any of its properties), 
			you can only assign the Gauge::Font property a new Drawing::Font. However, you can base the new font on the existing font. 

			@see
			- Drawing::Font
		*/
		property<Drawing::Font>::bind<Gauge, &Gauge::getFont, &Gauge::setFont> Font;

        //! Gets or sets the text prefixed to the value displayed in the Gauge.
		/*!
			### Property Value ### 
			
			> `std::string`

			Text prefixed to the value displayed. For example, Red: would result in Red:35.
		*/
		property<std::string>::bind<Gauge, &Gauge::getPrefix, &Gauge::setPrefix> Prefix;

        //! Gets or sets the text appended to the value displayed in the Gauge.
		/*!
			### Property Value ### 
			
			> `std::string`

			Text appended to the value displayed. For example, % would result in 35%.
		*/
		property<std::string>::bind<Gauge, &Gauge::getSuffix, &Gauge::setSuffix> Suffix;

		//! Gets or sets the the gauge's current value.
		/*!
			### Property Value ### 
			
			> **long**

			The gauge's current value.
		*/
		phproperty<long>::bind<Gauge, ArgLong::eArgLong, Arguments::gauge_value> Value;

		//! Gets or sets the maximum value of the range of the gauge.
		/*!
			### Property Value ### 
			
			> **long**

			The maximum value of the range. The default is 100.
		*/
		phproperty<long>::bind<Gauge, ArgLong::eArgLong, Arguments::maximum> Maximum;

        //! Gets or sets the minimum value of the range of the gauge.
		/*!
			### Property Value ### 
			
			> **long**

			The minimum value of the range. The default is 0.
		*/
		phproperty<long>::bind<Gauge, ArgLong::eArgLong, Arguments::minimum> Minimum;
        

        //! Gets or sets gauge flags inherited by all gauge-like widgets. See Flags::Gauge::eGaugeFlags.
        phbitmask<short int, Flags::Gauge::eGaugeFlags>::bind<Gauge, ArgShort::eArgShort, ArgShort::gauge_flags> GaugeFlags; 

		
		//@}
	};
} // namespace PhWidgets


#endif // PHWIDGETS_GAUGE_H
