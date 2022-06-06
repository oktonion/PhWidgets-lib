#ifndef PHWIDGETS_BASIC_H
#define PHWIDGETS_BASIC_H

#include <photon/PtBasic.h>

#include "./Widget.h"
#include "./Drawing/Color.h"


namespace PhWidgets
{
    /*!
        @struct PhWidgets::Basic
        @ingroup Widgets
    */

    //! A superclass of basic resources for most widgets
    /*!
        The Basic superclass provides basic resources for all widgets. It provides the fundamental events for:

        getting/losing focus
        activating
        button press, release, and repeat

        Also, Basic supports:

            toggle buttons
            autohighlighting

        and provides properties for:

            margins
            bevel colors
            outline and inline colors
            draw color
            fill color
            fill pattern.
    */    
    class Basic:
        public Widget
    {
    public:

        //! Contains resource IDs for Basic arguments. @ingroup Resources
        template<class T = void, class Disabled = Widget::ResourceTypeTag<0>, bool Dummy = false>
        struct Arguments
			: Widget::Arguments<T>
        {
            typedef void type;
        };

		template<class T, int TypeID>
        struct Arguments<T, Widget::ResourceTypeTag<TypeID> >
            : Arguments<T, Widget::ResourceTag::Alloc>
            , Arguments<T, Widget::ResourceTag::Callback>
            , Arguments<T, Widget::ResourceTag::Color>
            , Arguments<T, Widget::ResourceTag::Flag>
            , Arguments<T, Widget::ResourceTag::Scalar>
            , Arguments<T, Widget::ResourceTag::String>
            , Arguments<T, Widget::ResourceTag::Struct>
			, Widget::Arguments<T>
        { };

        template<class T>
        struct Arguments<Basic, T, false>
            : Arguments<T>
        { };

        //! Contains resource IDs for Basic arguments of type **unsigned short**.
        template<bool Dummy>
        struct Arguments<unsigned short, ResourceTag::Scalar, Dummy>
        {
            //! Resource IDs for Basic arguments of type **unsigned short**.

            /*!
                ### Aliases ###
                
                PhWidgets::Basic::Arguments<unsigned short>::Scalar

                See Widget::resource for usage description.
            */
            typedef enum Scalar
            {
                MarginHeight = Pt_ARG_MARGIN_HEIGHT, //!< The amount of vertical space between the widget's canvas and the widget's border. The canvas is the valid drawing area of the widget and is inside all borders and margins.
                MarginWidth = Pt_ARG_MARGIN_WIDTH //!< The amount of horizontal space between the widget's canvas and the widget's border. The canvas is the valid drawing area of the widget and is inside all borders and margins.
            } type;
        };
        
        //! Contains resource IDs for Basic arguments of type **unsigned long**.
        template<bool Dummy>
        struct Arguments<unsigned long, ResourceTag::Scalar, Dummy>
        {
            //! Resource IDs for Basic arguments of type **unsigned long**.

            /*!
                ### Aliases ###
                
                PhWidgets::Basic::Arguments<unsigned long>::Scalar

                See Widget::resource for usage description.
            */
            typedef enum Scalar
            {
                BandwidthThreshold = Pt_ARG_BANDWIDTH_THRESHOLD, //!< Can't be set! In general, it defines a threshold below which a widget optimizes drawing on a system with a slow connection.
                BasicFlags = Pt_ARG_BASIC_FLAGS //!< This flag resource controls which “edge decorations” are rendered for a widget when it's highlighted
            } type;
        };

        //! Contains resource IDs for Basic arguments of type `PgColor_t`.
        template<bool Dummy>
        struct Arguments<PgColor_t, ResourceTag::Color, Dummy>
        {
            //! Resource IDs for Basic arguments of type `PgColor_t`.

            /*!
                ### Aliases ###
                
                PhWidgets::Basic::Arguments<unsigned long>::Color

                See Widget::resource for usage description.
            */
            typedef enum Color
            {
                BevelColor = Pt_ARG_BEVEL_COLOR, //!< The main color of the bevel.
                Color = Pt_ARG_COLOR, //!< The widget's foreground or drawing color. @default PhWidgets::Drawing::Colors::Black
                DarkBevelColor = Pt_ARG_DARK_BEVEL_COLOR, //!< This resource, with \link Basic::Arguments<>::LightBevelColor LightBevelColor\endlink, specifies the outermost colors used when applying a bevel to a widget.
                DarkFillColor = Pt_ARG_DARK_FILL_COLOR, //!< This resource, with \link Basic::Arguments<>::LightFillColor LightFillColor\endlink, specifies the colors with which a gradient (if applied) starts and ends.
                FillColor = Pt_ARG_FILL_COLOR, //!< The base fill color for the widget. @default PhWidgets::Drawing::Colors::Gray
                InlineColor = Pt_ARG_INLINE_COLOR, //!< The color of the inline of the border.
                LightBevelColor = Pt_ARG_LIGHT_BEVEL_COLOR, //!< This resource, with \link Basic::Arguments<>::DarkBevelColor DarkBevelColor\endlink, specifies the outermost colors used when applying a bevel to a widget.
                LightFillColor = Pt_ARG_LIGHT_FILL_COLOR, //!< This resource, with \link Basic::Arguments<>::DarkFillColor DarkFillColor\endlink, specifies the colors with which a gradient (if applied) starts and ends.
                OutlineColor = Pt_ARG_OUTLINE_COLOR //!< The color of the outline of the border.
            } type;
        };

        //! Contains resource IDs for Basic arguments of type **char**.
        template<bool Dummy>
        struct Arguments<char, ResourceTag::Scalar, Dummy>
        {        
            //! Resource IDs for Basic arguments of type **char**.

            /*!
                ### Aliases ###
                
                PhWidgets::Basic::Arguments<char>::Scalar

                See Widget::resource for usage description.
            */
            typedef enum Scalar
            {
                BevelContrast = Pt_ARG_BEVEL_CONTRAST, //!< This value determines how much the dark and light bevel colors differ from the \link Basic::ArgColor::BevelColor base bevel color\endlink. The higher the value, the greater the difference
                Contrast = Pt_ARG_CONTRAST //!< This value determines how much the dark and light fill colors differ from the \link Basic::ArgColor::FillColor base fill color\endlink. The higher the value, the greater the difference
            } type;
        };

        //! Contains resource IDs for Basic arguments of type `PgPattern_t`.
        template<bool Dummy>
        struct Arguments<PgPattern_t, ResourceTag::Struct, Dummy>
        {
            //! Resource IDs for Basic arguments of type `PgPattern_t`.

            /*!
                ### Aliases ###
                
                PhWidgets::Basic::Arguments<PgPattern_t>::Struct

                See Widget::resource for usage description.
            */
            typedef enum Struct
            {
                FillPattern = Pt_ARG_FILL_PATTERN, //!< The widget's background pattern. @default Pg_PAT_FULL
                TransPattern = Pt_ARG_TRANS_PATTERN //!< The widget's transparency pattern. You'll find this handy for “ghosting” widgets. @default Pg_PAT_NONE
            } type;
        };
        
        //! Contains resource IDs for Basic arguments of type **unsigned char**.
        template<bool Dummy>
        struct Arguments<unsigned char, ResourceTag::Scalar, Dummy>
        {
            //! Resource IDs for Basic arguments of type **unsigned char**.

            /*!
                ### Aliases ###
                
                PhWidgets::Basic::Arguments<unsigned char>::Scalar

                See Widget::resource for usage description.
            */
            typedef enum Scalar
            {
                HighlihgtRoundness = Pt_ARG_HIGHLIGHT_ROUNDNESS //!< The radius, in pixels, of the widget's borders. The default value of 0 results in square corners.
            } type;
        };
        
        //! Contains resource IDs for Basic arguments of type <b>char*</b>.
        template<bool Dummy>
        struct Arguments<char*, ResourceTag::String, Dummy>
        {
            //! Resource IDs for Widget arguments of type <b>char*</b>.

            /*!
                ### Aliases ###
                
                PhWidgets::Basic::Arguments<char*>::String

                See Widget::resource for usage description.
            */
            enum String
            {
                Style = Pt_ARG_STYLE //!< The style to use for this widget instance.
            } type;
        };    

		//! Contains resource IDs for Basic callbacks. @ingroup Resources
        template<class T = void, class Disabled = void, bool Dummy = false>
        struct Callbacks
        {
            typedef Callbacks<> type;
        };

        template<class T>
        struct Callbacks<Basic, T>
            : Callbacks<T>
        { };

        template<class T, bool Dummy>
        struct Callbacks<T, void, Dummy>
            : Callbacks<T, ResourceTag::Callback, Dummy>
        { };

		//! Contains resource IDs for Basic callbacks of type `PtCallback_t`.
		template<bool Dummy>
        struct Callbacks<PtCallback_t, ResourceTag::Callback, Dummy>
		{
			//! Resource IDs for Basic arguments of type `PtCallback_t`.
			/*!
				### Aliases ###
				
				PhWidgets::Basic::Callbacks<PtCallback_t>::Callback

				See Widget::resource for usage description.
			*/
			typedef enum Callback
			{
				Activate = Pt_CB_ACTIVATE,     //!< A list of PtCallback_t structures that define the callbacks that the widget calls when it becomes activated.
											//!< To activate a widget, you typically release the left pointer button while pointing at an armed widget.

				Arm = Pt_CB_ARM, //!< A list of PtCallback_t structures that define the callbacks that the widget calls when it becomes armed.
									//!< To arm a widget, you typically press the left pointer button while pointing at the widget.

				Disarm = Pt_CB_DISARM,     //!< A list of PtCallback_t structures that define the callbacks that the widget calls when it becomes disarmed. 
										//!< To disarm a widget, you typically release the left pointer button when not pointing at an armed widget. 

				GotFocus = Pt_CB_GOT_FOCUS, //!< A list of PtCallback_t structures that define the callbacks invoked when a widget gets focus or its focus status changes 
												//!< (e.g. a child widget gets focus from its parent or the focus switches from a child to its parent).

				LostFocus = Pt_CB_LOST_FOCUS, //!< A list of PtCallback_t structures that define the callbacks that the widget calls when it loses focus.

				Menu = Pt_CB_MENU, //!< A list of PtCallback_t structures that define the callbacks that the widget calls when you press the right button while the pointer is on top of the widget.

				Repeat = Pt_CB_REPEAT     //!< A list of PtCallback_t structures that define the callbacks that the widget calls when it receives Ph_EV_BUT_REPEAT events. 
										//!< These events occur when you hold down the left pointer button (or the right pointer button if the widget has Widget::Flags::AllButtons set in its Widget::Arguments<>::Flags resource).
			} type;
		};
        };

        //! Contains flags for all Basic resources. @ingroup Resources
        struct Flags
			: Widget::Flags
        {
            //! Contains flags for Basic resource Basic::Arguments<>::BasicFlags.
            struct Basic
            {
                //! Cursor flags for Basic resource Basic::Arguments<>::BasicFlags.
                /*!
                    ### Aliases ###
                    
                    PhWidgets::Basic::Flags::Basic::type
                */
                enum type
                {

                    // Edge-control bits:

                    TopEtch = Pt_TOP_ETCH,
                    BottomEtch = Pt_BOTTOM_ETCH,
                    LeftEtch = Pt_LEFT_ETCH,
                    RightEtch = Pt_RIGHT_ETCH, // Render a single alpha line on an edge of the widget. The top and left lines are dark, and the bottom and right lines are light. This can make a widget look like it's slightly inset. 
                    BlankEtches = Pt_BLANK_ETCHES, //!< Don't draw the etched lines. 
                    OpaqueEtches = Pt_OPAQUE_ETCHES, //!< Use a solid line, instead of an alpha line, for the etching. The color is calculated based on the widget's color and widget's parent color. 
                    TopOutline = Pt_TOP_OUTLINE,
                    BottomOutline = Pt_BOTTOM_OUTLINE,
                    LeftOutline = Pt_LEFT_OUTLINE,
                    RightOutline = Pt_RIGHT_OUTLINE, // Render a single-pixel outline on an edge of the widget. 
                    TopBevel = Pt_TOP_BEVEL,
                    BottomBevel = Pt_BOTTOM_BEVEL,
                    LeftBevel = Pt_LEFT_BEVEL,
                    RightBevel = Pt_RIGHT_BEVEL, // Render a bevel Pt_ARG_BEVEL_WIDTH pixels wide on an edge of the widget. 
                    FullBevels = Pt_FULL_BEVELS, // Render a full bevel (i.e. half-round) instead of a half bevel (quarter-round). 
                    TopInline =  Pt_TOP_INLINE,
                    BottomInline = Pt_BOTTOM_INLINE,
                    LeftInline = Pt_LEFT_INLINE,
                    RightInline = Pt_RIGHT_INLINE, // Render a single-pixel inline on an edge of the widget. 

                    // These convenience manifests make working with these bits easier:

                    TopLeftEtch = Pt_TOP_LEFT_ETCH, //!< Adjust the etching on the top/left edges. 
                    BottomRightEtch = Pt_BOTTOM_RIGHT_ETCH, //!< Adjust the etching on the bottom/right edges. 
                    AllEtches = Pt_ALL_ETCHES, //!< Adjust the etching on the all edges.  
                    TopLeftOutline = Pt_TOP_LEFT_OUTLINE, //!< Adjust the outline on the top/left edges. 
                    BottomRightOutline = Pt_BOTTOM_RIGHT_OUTLINE, //!< Adjust the outline on the bottom/right edges. 
                    AllOutlines = Pt_ALL_OUTLINES, //!< Adjust the outline on the all edges. 
                    TopLeftBevel = Pt_TOP_LEFT_BEVEL, //!< Adjust the bevel on the top/left edges. 
                    BottomRightBevel = Pt_BOTTOM_RIGHT_BEVEL, //!< Adjust the bevel on the bottom/right edges. 
                    AllBevels = Pt_ALL_BEVELS, //!< Adjust the bevel on the all edges. 
                    TopLeftInline = Pt_TOP_LEFT_INLINE, //!< Adjust the inline on the top/left edges. 
                    BottomRightInline= Pt_BOTTOM_RIGHT_INLINE, //!< Adjust the inline on the bottom/right edges. 
                    AllInlines = Pt_ALL_INLINES, //!< Adjust the inline on the all edges. 
                    AllTop = Pt_ALL_TOP, //!< Adjust all edge decorations (etch, outline, bevel, and inline) on the top edge. 
                    AllBottom = Pt_ALL_BOTTOM, //!< Adjust all edge decorations (etch, outline, bevel, and inline) on the bottom edge. 
                    AllLeft = Pt_ALL_LEFT, //!< Adjust all edge decorations (etch, outline, bevel, and inline) on the left edge. 
                    AllRight = Pt_ALL_RIGHT, //!< Adjust all edge decorations (etch, outline, bevel, and inline) on the right edge. 
                    All = Pt_ALL, //!< Adjust all edge decorations (etch, outline, bevel, and inline) on the all edges. 

                    // Fill-control bits:

                    FlatFill = Pt_FLAT_FILL, //!<  If set, the widget is filled with a solid color as given by ArgColor::FillColor. If clear, the widget is filled with a gradient. 
                    HorizontalGradient = Pt_HORIZONTAL_GRADIENT, //!<  If set, and Pt_FLAT_FILL is clear, the fill gradient changes colors on the horizontal axis. If clear and ArgColor::flat_fill is clear, the fill gradient changes colors on the vertical axis. 
                    ReverseGradient = Pt_REVERSE_GRADIENT, //!<  If set and Pt_FLAT_FILL is clear, the gradient rendered is reversed (i.e. begin with the dark fill color on the top or left when the widget isn't pressed). 
                    StaticBevelColors = Pt_STATIC_BEVEL_COLORS, //!<  If set, the bevel color doesn't change when you set ArgColor::FillColor. 
                    PreventFill = Pt_BASIC_PREVENT_FILL, //!<  If set, the widget isn't filled. This is useful when you want to set the base color for borders and etches without actually rendering a fill. 

                    // Behavior on state change:

                    // These bits affect how the widget behaves when set (depressed) or unset (raised):

                    StaticGradient = Pt_STATIC_GRADIENT, //!<  If set, the gradient doesn't reverse when the widget is set or unset. 
                    StaticBevels = Pt_STATIC_BEVELS //!<  If set, the rendered bevels don't change when the widget is set or unset. 
                };
            };

		template<int TypeID, bool Dummy>
        struct Arguments<void, Widget::ResourceTypeTag<TypeID>, Dummy>
            : Arguments<unsigned short, Widget::ResourceTypeTag<__LINE__>/**/>,
            , Arguments<unsigned long, Widget::ResourceTypeTag<__LINE__>/**/>
            , Arguments<PgColor_t, Widget::ResourceTypeTag<__LINE__>/**/>
            , Arguments<char, Widget::ResourceTypeTag<__LINE__>/**/>
            , Arguments<PgPattern_t, Widget::ResourceTypeTag<__LINE__>/**/>
            , Arguments<unsigned char, Widget::ResourceTypeTag<__LINE__>/**/>
            , Arguments<char*, Widget::ResourceTypeTag<__LINE__>/**/>
            , Widget::Arguments<>
        { };

        template<bool Dummy>
        struct Callbacks<void, void, Dummy>
            : Callbacks<PtCallback_t>
            , Widget::Callbacks<>
        { };

    protected:

        typedef ResourceFrom<Widget::WidgetResourcesSingleton>::
            Define::String<Arguments<char*>::String>::
            Define::Color<Arguments<PgColor_t>::Color>::
            Define::Scalar<Arguments<unsigned short>::Scalar, unsigned short>::
            Define::Scalar<Arguments<char>::Scalar, char>::
            //Define::Flag<ThisArgs::ArgLong::eArgLong, long>::
            Define::Flag<Arguments<unsigned long>::Scalar, unsigned long>::
            //Define::Flag<ThisArgs::ArgUnsigned::eArgUnsigned, unsigned>::

            Define::Link<Callbacks<PtCallback_t>::type, PtCallback_t*>::

        resource_type WidgetResourcesSingleton;

        virtual void check();
                        
    public:
        //! (constructor) 
        /*!
            Constructs a Basic widget by ID.
            @param[in] abn ID given by PhAB to widget (like 'ABN_WIDGET_NAME').
        */
        explicit Basic(int abn);

        //! (constructor) 
        /*!
            Constructs a Basic widget by pointer to widget.
            @param[in] wdg pointer to Photon widget.
        */
        explicit Basic(PtWidget_t *wdg);
        
        //! (copy constructor) 
        /*!
            Constructs a Basic widget by copy.
            @param[in] other another Basic widget to be used as source to initialize the elements of the container with.
        */
        Basic(const Basic &other);

        //! Assigns value in Basic widget 
        /*!
            Replaces the contents of the Basic widget.
            @param[in] other another Basic widget to use as data source.
        */
        Basic &operator=(const Basic &other);

        //! Resources of the Basic
        /*!
            @see
            - Widget::resource
        */
        WidgetResourcesSingleton resource;
        
        //! @name Properties
        //! @{ 
        
        //! Gets or sets the main color of the bevel.
        /*!
            ### Property Value ### 
            
            > Drawing::Color

            A `Drawing::Color` that represents the main color of the bevel.

            @see
            - Drawing::Colors
            - Drawing::Color
        */
        phproperty<Drawing::Color>::bind<Basic, Arguments<PgColor_t>::Color, Arguments<>::BevelColor> BevelColor;
        
        //! Gets or sets the foreground or drawing color for the widget.
        /*!
            ### Property Value ### 
            
            > Drawing::Color

            A `Drawing::Color` that represents the foreground or drawing color of the widget. The default is the value of the PhWidgets::Drawing::Colors::Black.

            ### Examples ###

            @code
                // You have somewhere:
                PtWidget_t *ptwidget; // pointer to widget

                // constructing Widget
                PhWidgets::Basic widget(ptwidget);
                
                widget.Color = PhWidgets::Drawing::Colors::DarkBlue;
            @endcode

            @remark
            The Basic::Color property does not support transparent colors unless the color model is set to ARGB.
            @par
            The Basic::Color property is an ambient property. An ambient property is a widget property that, 
            if not set, is retrieved from the parent widget. For example, a PhWidgets::Button will have the same Basic::Color as its parent PhWidgets::Window by default. 

            @see
            - Drawing::Colors
            - Drawing::Color
        */
        phproperty<Drawing::Color>::bind<Basic, Arguments<PgColor_t>::Color, Arguments<>::Color> Color;

        //! Gets or sets the dark outermost color used when applying a bevel to a widget.
        /*!
            ### Property Value ### 
            
            > Drawing::Color

            A `Drawing::Color`, with Basic::LightBevelColor, that represents the outermost colors used when applying a bevel to a widget.
            
            @note
            These value is automatically generated when you set Basic::FillColor. 
            Setting Basic::FillColor overrides any values set previously via these property.

            @remark
            See Basic::BasicFlags to find out when gradients and borders are rendered for a given widget. 

            @see
            - Drawing::Colors
            - Drawing::Color
            - BasicFlags
            - FillColor
            - DarkFillColor
            - LightFillColor
            - LightBevelColor
        */
        phproperty<Drawing::Color>::bind<Basic, Arguments<PgColor_t>::Color, Arguments<>::DarkBevelColor> DarkBevelColor;

        //! Gets or sets the dark color with which a gradient (if applied) goes.
        /*!
            ### Property Value ### 
            
            > Drawing::Color

            A `Drawing::Color`, with Basic::LightFillColor, that represents the color with which a gradient (if applied) starts and ends.
            These value is also used as the inner color for the bevels 
            (i.e. the bottom bevel normally goes through a transition from Basic::DarkBevelColor to Basic::DarkFillColor when a bevel is applied to the widget).
            
            @note
            These value is automatically generated when you set Basic::FillColor. 
            Setting Basic::FillColor overrides any values set previously via these property.

            @remark
            See Basic::BasicFlags to find out when gradients and borders are rendered for a given widget. 

            @see
            - Drawing::Colors
            - Drawing::Color
            - BasicFlags
            - FillColor
            - LightFillColor
            - LightBevelColor
            - DarkBevelColor
        */
        phproperty<Drawing::Color>::bind<Basic, Arguments<PgColor_t>::Color, Arguments<>::DarkFillColor> DarkFillColor;

        //! Gets or sets the fill color for the widget.
        /*!
            ### Property Value ### 
            
            > Drawing::Color

            A `Drawing::Color` that represents the fill color of the widget. The default is the value of the PhWidgets::Drawing::Colors::Black.
            
            This color is used as the base color when generating the 
            Basic::BevelColor, Basic::LightBevelColor, Basic::DarkBevelColor, Basic::LightFillColor, and Basic::DarkFillColor.
            
            @note
            Setting this property effectively overrides all values previously set for the 
            Basic::LightBevelColor, Basic::DarkBevelColor, Basic::LightFillColor, and Basic::DarkFillColor properties.
            This is like setting the chroma for a widget.

            - If the widget uses a flat fill, that fill is Basic::FillColor. 
            - If the widget uses a gradient fill, the gradient runs from Basic::LightFillColor to Basic::DarkFillColor. 
            - If the widget uses a bevel, it's rendered with color ranges as defined by Basic::LightBevelColor to Basic::LightFillColor 
            and Basic::DarkBevelColor to Basic::DarkFillColor. 

            @note
            See Basic::BasicFlags to find out when gradients and borders are rendered for a given widget.

            @remark
            The Basic::FillColor property does not support transparent colors unless the color model is set to ARGB.
            @par
            The Basic::Color property is an ambient property. An ambient property is a widget property that, 
            if not set, is retrieved from the parent widget. For example, a PhWidgets::Button will have the same Basic::FillColor as its parent PhWidgets::Window by default. 

            @see
            - Drawing::Colors
            - Drawing::Color
            - BasicFlags
            - LightFillColor
            - DarkFillColor
            - LightBevelColor
            - DarkBevelColor
        */
        phproperty<Drawing::Color>::bind<Basic, Arguments<PgColor_t>::Color, Arguments<>::FillColor> FillColor;

        //! Gets or sets the color of the inline of the border.
        /*!
            ### Property Value ### 
            
            > Drawing::Color

            A `Drawing::Color` that represents the color of the inline of the border.
            
            @remark
            The inline is drawn if any of 'inline' Basic::Flags::Basic flags are set in Basic::BasicFlags.

            @see
            - Drawing::Color
            - Drawing::Colors
            - BasicFlags
        */
        phproperty<Drawing::Color>::bind<Basic, Arguments<PgColor_t>::Color, Arguments<>::InlineColor> InlineColor;

        //! Gets or sets the light outermost color used when applying a bevel to a widget.
        /*!
            ### Property Value ### 
            
            > Drawing::Color

            A `Drawing::Color`, with Basic::DarkBevelColor, that represents the outermost colors used when applying a bevel to a widget.
            
            @note
            These value is automatically generated when you set Basic::FillColor. 
            Setting Basic::FillColor overrides any values set previously via these property.

            @remark
            See Basic::BasicFlags to find out when gradients and borders are rendered for a given widget. 

            @see
            - Drawing::Colors
            - Drawing::Color
            - BasicFlags
            - FillColor
            - DarkFillColor
            - LightFillColor
            - DarkBevelColor
        */
        phproperty<Drawing::Color>::bind<Basic, Arguments<PgColor_t>::Color, Arguments<>::LightBevelColor> LightBevelColor;

        //! Gets or sets the light color with which a gradient (if applied) goes.
        /*!
            ### Property Value ### 
            
            > Drawing::Color

            A `Drawing::Color`, with Basic::DarkFillColor, that represents the color with which a gradient (if applied) starts and ends.
            These value is also used as the inner color for the bevels 
            (i.e. the bottom bevel normally goes through a transition from Basic::DarkBevelColor to Basic::DarkFillColor when a bevel is applied to the widget).
            
            @note
            These value is automatically generated when you set Basic::FillColor. 
            Setting Basic::FillColor overrides any values set previously via these property.

            @remark
            See Basic::BasicFlags to find out when gradients and borders are rendered for a given widget. 

            @see
            - Drawing::Colors
            - Drawing::Color
            - BasicFlags
            - FillColor
            - DarkFillColor
            - LightBevelColor
            - DarkBevelColor
        */
        phproperty<Drawing::Color>::bind<Basic, Arguments<PgColor_t>::Color, Arguments<>::LightFillColor> LightFillColor;

        //! Gets or sets the amount of vertical space between the widget's canvas and the widget's border.
        /*!
            ### Property Value ### 
            
            > **unsigned short**

            A `unsigned short` that represents the amount of vertical space between the widget's canvas and the widget's border.
            @remark
            The canvas is the valid drawing area of the widget and is inside all borders and margins.  
        */
        phproperty<unsigned short>::bind<Basic, Arguments<unsigned short>::Scalar, Arguments<>::MarginHeight> MarginHeight;

        //! Gets or sets the amount of horizontal space between the widget's canvas and the widget's border.
        /*!
            ### Property Value ### 
            
            > **unsigned short**

            A `unsigned short` that represents the amount of horizontal space between the widget's canvas and the widget's border.
            @remark
            The canvas is the valid drawing area of the widget and is inside all borders and margins.  
        */
        phproperty<unsigned short>::bind<Basic, Arguments<unsigned short>::Scalar, Arguments<>::MarginWidth> MarginWidth;

        //! Gets or sets the color of the outline of the border.
        /*!
            ### Property Value ### 
            
            > Drawing::Color

            A `Drawing::Color` that represents the color of the outline of the border.
            
            @remark
            The inline is drawn if any of 'outline' Basic::Flags::Basic flags are set in Basic::BasicFlags.

            @see
            - Drawing::Color
            - Drawing::Colors
            - BasicFlags
        */
        phproperty<Drawing::Color>::bind<Basic, Arguments<PgColor_t>::Color, Arguments<>::OutlineColor> OutlineColor;

        phbitmask<unsigned long, Flags::Basic::type>::
			bind<Basic, Arguments<unsigned long>::Scalar, Arguments<>::BasicFlags>    BasicFlags; //!< Gets or sets basic flags inherited by all widgets. See Flags::Basic::eBasic.

        //! @}

        //! @name Events
        //! @{ 
        phwidgets_event<Basic, Basic::Callbacks<>::Activate>      Activate; //!< Occurs when you release the left pointer button while pointing at an armed widget.
        phwidgets_event<Basic, Basic::Callbacks<>::Arm>           Arm; //!< Occurs when you press the left pointer button while pointing at the widget.
        phwidgets_event<Basic, Basic::Callbacks<>::Disarm>        Disarm; //!< Occurs when you release the left pointer button when not pointing at an armed widget.
        phwidgets_event<Basic, Basic::Callbacks<>::GotFocus>      GotFocus; //!< Occurs when a widget gets focus or its focus status changes.
        phwidgets_event<Basic, Basic::Callbacks<>::LostFocus>     LostFocus; //!< Occurs when a widget loses focus.
        phwidgets_event<Basic, Basic::Callbacks<>::Menu>          Menu; //!< Occurs when you press the right button while the pointer is on top of the widget.
        phwidgets_event<Basic, Basic::Callbacks<>::Repeat>        Repeat; //!< Documentation in progress...

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


    
} // namespace PhWidgets

cppbitmasks::bitmask<unsigned long, PhWidgets::Basic::Flags::Basic::eBasic> operator|(const PhWidgets::Basic::Flags::Basic::eBasic &flag1, const PhWidgets::Basic::Flags::Basic::eBasic &flag2);
cppbitmasks::bitmask<unsigned long, PhWidgets::Basic::Flags::Basic::eBasic> operator&(const PhWidgets::Basic::Flags::Basic::eBasic &flag1, const PhWidgets::Basic::Flags::Basic::eBasic &flag2);
cppbitmasks::bitmask<unsigned long, PhWidgets::Basic::Flags::Basic::eBasic> operator^(const PhWidgets::Basic::Flags::Basic::eBasic &flag1, const PhWidgets::Basic::Flags::Basic::eBasic &flag2);


#endif // PHWIDGETS_BASIC_H
