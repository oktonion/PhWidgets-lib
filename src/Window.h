#ifndef PHWIDGETS_WINDOW_H
#define PHWIDGETS_WINDOW_H

#include <photon/PtWindow.h>

#include "./Disjoint.h"


namespace PhWidgets
{
	/*!
		@struct PhWidgets::Window
		@ingroup Widgets
	*/

	//! An Application window that's managed by the Photon window manager
	/*!
		The Window class provides a top-level container for your applications' widgets. 
		It also provides a standard appearance for all windows. 
		Windows are managed by the Photon window manager if it's present.

		@note
		A Window is the top-level Widget of the Application. 
		If you try to use another class for the top-level Widget (aside from a Region), 
		the behavior is undefined — you'll likely get a fatal error.  

		### Interacting with the Photon window manager ###

		Using resources, you can choose which elements of the window frame will be displayed. 
		You can control which window management functions the window manager will perform, 
		and whether they're invoked from the window menu or from one of the window controls. 
		You can also have your application notified when the user has requested a window management function, 
		regardless of whether or not the window manager will perform that function. 

		### Setting the Window's title ###

		You can specify the string displayed in the window's title bar by setting the Window::Title property. 
	*/
	class Window:
		public Disjoint
	{
	public:

        //! Contains resource IDs for Window arguments. @ingroup Resources
		struct ThisArgs
		{		
            //! Contains resource IDs for Window arguments of type **short**.
			struct ArgShort
			{
                //! Resource IDs for Window arguments of type **short**.

				/*!
					### Aliases ###
					
					PhWidgets::Window::Arguments::eArgShort,
					PhWidgets::Window::ArgShort::eArgShort

					See Widget::resource for usage description.
				*/
				enum eArgShort
				{
					max_height = Pt_ARG_MAX_HEIGHT, //!< The maximum height of the Window. 
                                                    //!< If you set this resource to 0, the default value specified by the window manager is used.

                    max_width = Pt_ARG_MAX_WIDTH,   //!< The maximum width of the Window.
                                                    //!< If you set this resource to 0, the default value specified by the window manager is used.

                    min_height = Pt_ARG_MIN_HEIGHT, //!< The minimum width of the Window.
                                                    //!< If you set this resource to 0, the default value specified by the window manager is used. 

                    min_width = Pt_ARG_MIN_WIDTH    //!< The minimum width of the Window.
                                                    //!< If you set this resource to 0, the default value specified by the window manager is used.                       
				};
			};	

            //! Contains resource IDs for Window arguments of type `PgColor_t`.
			struct ArgColor
			{
				//! Resource IDs for Window arguments of type `PgColor_t`.

				/*!
					### Aliases ###
					
					PhWidgets::Window::Arguments::eArgColor,
					PhWidgets::Window::ArgColor::eArgColor

					See Widget::resource for usage description.
				*/
				enum eArgColor
				{
					window_active_color = Pt_ARG_WINDOW_ACTIVE_COLOR, //!< The color of the window's frame when the Window has focus. 
                                                                      //!< This overrides the color specified by the window manager. 
                    
                    window_inactive_color = Pt_ARG_WINDOW_INACTIVE_COLOR,   //!< The color of the window's frame when the Window doesn't have focus. 
                                                                            //!< This overrides the color specified by the window manager.
                    
                    window_title_color = Pt_ARG_WINDOW_TITLE_COLOR  //!< The color of the window's title (i.e. the text). 
                                                                    //!< This overrides the color specified by the window manager.          

				};	
			};

			//! Contains resource IDs for Window arguments of type <b>char*</b>.
			struct ArgPChar
			{
				//! Resource IDs for Window arguments of type <b>char*</b>.

				/*!
					### Aliases ###
					
					PhWidgets::Window::Arguments::eArgPChar,
					PhWidgets::Window::ArgPChar::eArgPChar

					See Widget::resource for usage description.
				*/
				enum eArgPChar
				{
					window_title = Pt_ARG_WINDOW_TITLE, //!< The string that the Window Manager displays in the title bar.
					window_help_root = Pt_ARG_WINDOW_HELP_ROOT //!< Defines the root topic path for the Window.

				};	
			};
		};

        //! Contains resource IDs for Window callbacks.
		struct ThisCallbacks
		{
            //! Contains resource IDs for Window callbacks of type `PtCallback_t`.
			struct Callback
			{
                //! Resource IDs for Window arguments of type `PtCallback_t`.
				/*!
					### Aliases ###
					
					PhWidgets::Window::Callbacks::eCallback,
					PhWidgets::Window::Callback::eCallback

					See Widget::resource for usage description.
				*/
				enum eCallback
				{
					window = 
                        Pt_CB_WINDOW,   //!< A list of `PtCallback_t` structures that define the callbacks that the widget invokes when it receives an event from the window manager.
									    //!< Documentation in progress...

					window_closing = 
                        Pt_CB_WINDOW_CLOSING,   //!< A list of `PtCallback_t` structures that define the callbacks that the widget invokes when the window is being closed.
											    //!< It's invoked before the window's region is removed.
												//!< These callbacks are invoked when the window is about to unrealize for any reason
												//!< Documentation in progress...

					window_opening = 
                        Pt_CB_WINDOW_OPENING,   //!< A list of `PtCallback_t` structures that define the callbacks that the widget invokes when the window is being opened.
									            //!< If you want to resize the Window and want anchoring to be in effect, do it in this type of callback.
                                                //!< Documentation in progress...

					window_transport = 
                        Pt_CB_WINDOW_TRANSPORT  //!< A list of `PtCallback_t` structures that define the callbacks that the widget invokes when the window is being transported through a Jump Gate.
												//!< Documentation in progress...
				};
			};
		};
		
        //! Contains resource IDs for arguments of type **short**. @ingroup Resources
		struct ArgShort:
			public ThisArgs::ArgShort
        { };	

        //! Contains resource IDs for arguments of type `PgColor_t`. @ingroup Resources
        struct ArgColor:
			public ArgumentsEx<Disjoint::ArgColor>,
			public ThisArgs::ArgColor
		{
			typedef ThisArgs::ArgColor::eArgColor eArgColor;
		};

		//! Contains resource IDs for arguments of type <b>char*<\b>. @ingroup Resources
		struct ArgPChar:
			public ArgumentsEx<Disjoint::ArgPChar>,
			public ThisArgs::ArgPChar
		{
			typedef ThisArgs::ArgPChar::eArgPChar eArgPChar;
		};

        //! Contains resource IDs for callbacks of type `PtCallback_t`. @ingroup Resources
		struct Callback:
			public ArgumentsEx<ThisCallbacks::Callback>,
			public Disjoint::Callback
		{
			typedef ThisCallbacks::Callback::eCallback eCallback;
		};

        //! Contains resource IDs for all Window arguments. @ingroup Resources
		struct Arguments:
			public ArgShort,
            public ArgColor,
			public ArgPChar,
			public Disjoint::Arguments
        { };

        //! Contains resource IDs for all Window callbacks. @ingroup Resources
		struct Callbacks:
			public Callback,
			public Disjoint::Callbacks
        { };

	protected:
		typedef ResourceFrom<Disjoint::WidgetResourcesSingleton>::
			Define::Scalar<ThisArgs::ArgShort::eArgShort, short>::
            Define::Color<ThisArgs::ArgColor::eArgColor>::
			Define::String<ThisArgs::ArgPChar::eArgPChar>::

			Define::Link<ThisCallbacks::Callback::eCallback, PtCallback_t*>::

		resource_type WidgetResourcesSingleton;

		virtual void check();

		//for properties:

		void setTitle(std::string);
		std::string getTitle() const;
						
	public:
		//! (constructor) 
		/*!
			Constructs a Window by ID.
			@param[in] abn ID given by PhAB to widget (like 'ABN_WIDGET_NAME').
		*/
		explicit Window(int abn);

		//! (constructor) 
		/*!
			Constructs a Window by pointer to widget.
			@param[in] wdg pointer to Photon widget.
		*/
		explicit Window(PtWidget_t *wdg);

		//! (copy constructor) 
		/*!
			Constructs a Widget by copy.
			@param[in] other another Widget to be used as source to initialize the elements of the container with.
		*/
		Window(const Window &other);

		//! Assigns value in Window 
		/*!
			Replaces the contents of the Window.
			@param[in] other another Window to use as data source.
		*/
		Window &operator=(const Window &other);

		//! Resources of the Window
		/*!
			@see
			- Widget::resource
		*/
		WidgetResourcesSingleton resource;

		//! @name Properties
		//! Properties are used to simplify use of widget resources.
		//@{

		//! Gets or sets a window's title.
		/*!
			### Property Value ### 
			
			> `std::string`

			A `std::string` that contains the window's title.
		*/
		property<std::string>::bind<Window, &Window::getTitle, &Window::setTitle> Title;


		//@}
		
        //! @name Events
		//@{ 
		phwidgets_event<Window, Window::Callbacks::window_closing>	Closing;
        phwidgets_event<Window, Window::Callbacks::window_opening>	Opening;
        //@}
	};
} // namespace PhWidgets


#endif // PHWIDGETS_WINDOW_H
