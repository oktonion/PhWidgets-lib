#ifndef PHWIDGETS_TIMER_H
#define PHWIDGETS_TIMER_H


#include <photon/PtTimer.h>

#include "./Widget.h"


namespace PhWidgets
{
	/*!
		@struct PhWidgets::Timer
		@ingroup Widgets
	*/

	//! A widget that invokes a callback after a given length of time
	/*!
		A Timer widget invokes a callback after an initial and repeated time period, given in milliseconds. 
		This widget is intended to provide a non-accurate, resourceless time base for your application. 
		To disable the timer, set Timer::Interval to 0 or unrealize the widget. 
	*/
	class Timer:
		protected Widget
	{
	public:
		using Widget::IPhWidgetsProperty;

		//! Contains resource IDs for Timer arguments. @ingroup Resources
		struct ThisArgs
		{												
			//! Contains resource IDs for Timer arguments of type **unsigned long**.
			struct ArgUnsignedLong
			{
				//! Resource IDs for Timer arguments of type **unsigned long**.

				/*!
					### Aliases ###
					
					PhWidgets::Timer::Arguments::eArgUnsignedLong,
					PhWidgets::Timer::ArgUnsignedLong::eArgUnsignedLong

					See Widget::resource for usage description.
				*/
				enum eArgUnsignedLong
				{
					timer_initial = Pt_ARG_TIMER_INITIAL, //!< The time, in milliseconds, before the first timer callback is activated. 
					timer_repeat = Pt_ARG_TIMER_REPEAT //!< The time, in milliseconds, for the repeat rate of the timer once the initial time period has expired. 
				};
			};

		};

		//! Contains resource IDs for Timer callbacks. @ingroup Resources
		struct ThisCallbacks
		{
			//! Contains resource IDs for Timer callbacks of type `PtCallback_t`.
			struct Callback
			{
				//! Resource IDs for Timer arguments of type `PtCallback_t`.
				/*!
					### Aliases ###
					
					PhWidgets::Timer::Callbacks::eCallback,
					PhWidgets::Timer::Callback::eCallback

					See Widget::resource for usage description.
				*/
				enum eCallback
				{
					timer_activate = Pt_CB_TIMER_ACTIVATE //!< A list of PtCallback_t structures that define the callbacks that the widget invokes when the timer has expired. 
				};
			};
		};
		
		//! Contains resource IDs for arguments of type **unsigned long**. @ingroup Resources
		struct ArgUnsignedLong:
			public ThisArgs::ArgUnsignedLong
        { };

		//! Contains resource IDs for arguments of type <b>void*</b>. @ingroup Resources
		struct ArgPVoid
		{
			static const Widget::ArgPVoid::eArgPVoid pointer;
			static const Widget::ArgPVoid::eArgPVoidData data;
			static const Widget::ArgPVoid::eArgPVoidData user_data;
		};

		//! Contains resource IDs for arguments of type **long**. @ingroup Resources
		Widget::ArgLong;//Pt_ARG_FLAGS

		//! Contains resource IDs for callbacks of type `PtCallback_t`. @ingroup Resources
		struct Callback:
			public ArgumentsEx<ThisCallbacks::Callback>,
			public Widget::Callback
		{
			typedef ThisCallbacks::Callback::eCallback eCallback;
		};
		
		//! Contains resource IDs for all Timer arguments. @ingroup Resources
		struct Arguments:
			public ArgUnsignedLong,
			public Widget::ArgLong,
			public ArgPVoid
        { };

		//! Contains resource IDs for all Timer callbacks. @ingroup Resources
		struct Callbacks:
			public Callback,
			public Widget::Callbacks
        { };

	private:
				
	protected:
		typedef ResourceFrom<Widget::WidgetResourcesSingleton>::
			Define::Scalar<ThisArgs::ArgUnsignedLong::eArgUnsignedLong, unsigned long>::

			Define::Link<ThisCallbacks::Callback::eCallback, PtCallback_t*>::

		resource_type WidgetResourcesSingleton;

		virtual void check();
						
	public:

		//! (constructor) 
		/*!
			Constructs a Timer widget by ID.
			@param[in] abn ID given by PhAB to widget (like 'ABN_WIDGET_NAME').
		*/
		explicit Timer(int abn);

		//! (constructor) 
		/*!
			Constructs a Timer widget by pointer to widget.
			@param[in] wdg pointer to Photon widget.
		*/
		explicit Timer(PtWidget_t *wdg);

		//! (copy constructor) 
		/*!
			Constructs a Timer widget by copy.
			@param[in] other another Timer widget to be used as source to initialize the elements of the container with.
		*/
		Timer(const Timer &other);
		
		//! Assigns value in Timer widget 
		/*!
			Replaces the contents of the Timer widget.
			@param[in] other another Timer widget to use as data source.
		*/
		Timer &operator=(const Timer &other);

		//! Resources of the Timer
		/*!
			@see
			- Widget::resource
		*/
		WidgetResourcesSingleton resource;

		using Widget::operator=;
		using Widget::operator==;
		using Widget::operator<;

		using Widget::operator PtWidget_t*;
		using Widget::operator const PtWidget_t*;

		//! @name Properties
		//! Properties are used to simplify use of widget resources.
		//! @{
		phproperty<unsigned long>::bind<Timer, ArgUnsignedLong::eArgUnsignedLong, Arguments::timer_initial> Initial; //!< The time, in milliseconds, before the first timer callback is activated.
		phproperty<unsigned long>::bind<Timer, ArgUnsignedLong::eArgUnsignedLong, Arguments::timer_repeat> Interval; //!< The time, in milliseconds, for the repeat rate of the timer once the initial time period has expired. 
		Widget::Enabled;

		//! @}

		//! @name Events
		//! @{
		phwidgets_event<Timer, Timer::Callbacks::timer_activate>		Activate;

		//! @}

		//! @name Event raisers
		//! @{
		void OnActivate(PtCallbackInfo_t *info);

		//! @}
	};
} // namespace PhWidgets

#endif // PHWIDGETS_TIMER_H