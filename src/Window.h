#ifndef PT_WINDOW_H
#define PT_WINDOW_H

#include <photon/PtWindow.h>

#include "./Disjoint.h"


namespace PhWidgets
{
		
	class Window:
		public Disjoint
	{
	public:

        //! Contains resource IDs for Window arguments.
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
		
        //! Contains resource IDs for Window arguments of type **short**.
		struct ArgShort:
			public ThisArgs::ArgShort
        { };	

        //! Contains resource IDs for Window arguments of type `PgColor_t`.
        struct ArgColor:
			public ArgumentsEx<Disjoint::ArgColor>,
			public ThisArgs::ArgColor
		{
			typedef ThisArgs::ArgColor::eArgColor eArgColor;
		};

        //! Contains resource IDs for Window callbacks of type `PtCallback_t`.
		struct Callback:
			public ArgumentsEx<ThisCallbacks::Callback>,
			public Disjoint::Callback
		{
			typedef ThisCallbacks::Callback::eCallback eCallback;
		};

        //! Contains resource IDs for all Window arguments.
		struct Arguments:
			public ArgShort,
            public ArgColor,
			public Disjoint::Arguments
        { };

        //! Contains resource IDs for all Window callbacks.
		struct Callbacks :
			public Callback,
			public Disjoint::Callbacks
        { };

	protected:
		typedef ResourceFrom<Disjoint::WidgetResourcesSingleton>::
			Define::Scalar<ThisArgs::ArgShort::eArgShort, short>::
            Define::Color<ThisArgs::ArgColor::eArgColor>::

			Define::Link<ThisCallbacks::Callback::eCallback, PtCallback_t*>::

		resource_type WidgetResourcesSingleton;

		virtual void check();
						
	public:
		WidgetResourcesSingleton resource;

		Window(int abn);
		Window(PtWidget_t *wdg);

		Window(const Window &rhs);

		Window &operator=(const Window &rhs);
		
        //! @name Events
		//@{ 
		phwidgets_event<Window, Window::Callbacks::window_closing>	Closing;
        phwidgets_event<Window, Window::Callbacks::window_opening>	Opening;
        //@}
	};
}


#endif
