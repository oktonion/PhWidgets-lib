#ifndef PT_TIMER_H
#define PT_TIMER_H


#include <photon/PtTimer.h>

#include "./Widget.h"


namespace PhWidgets
{
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

		struct ThisArgs
		{												
			struct ArgUnsignedLong
			{
				enum eArgUnsignedLong
				{
					timer_initial = Pt_ARG_TIMER_INITIAL, //!< The time, in milliseconds, before the first timer callback is activated. 
					timer_repeat = Pt_ARG_TIMER_REPEAT //!< The time, in milliseconds, for the repeat rate of the timer once the initial time period has expired. 
				};
			};

		};

		struct ThisCallbacks
		{
			struct Callback
			{
				enum eCallback
				{
					timer_activate = Pt_CB_TIMER_ACTIVATE //!< A list of PtCallback_t structures that define the callbacks that the widget invokes when the timer has expired. 
				};
			};
		};
		
		struct ArgUnsignedLong:
			public ThisArgs::ArgUnsignedLong
        { };

		struct ArgPVoid
		{
			static const Widget::ArgPVoid::eArgPVoid pointer;
			static const Widget::ArgPVoid::eArgPVoidData data;
			static const Widget::ArgPVoid::eArgPVoidData user_data;
		};

		Widget::ArgLong;//Pt_ARG_FLAGS

		struct Callback :
			public ArgumentsEx<ThisCallbacks::Callback>,
			public Widget::Callback
		{
			typedef ThisCallbacks::Callback::eCallback eCallback;
		};
		
		struct Arguments:
			public ArgUnsignedLong,
			public Widget::ArgLong,
			public ArgPVoid
        { };

		struct Callbacks :
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
		Timer(int abn);

		//! (constructor) 
		/*!
			Constructs a Timer widget by pointer to widget.
			@param[in] wdg pointer to Photon widget.
		*/
		Timer(PtWidget_t *wdg);

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
}

#endif