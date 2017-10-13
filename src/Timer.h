#ifndef PT_TIMER_H
#define PT_TIMER_H


#include <photon/PtTimer.h>

#include "./Widget.h"


namespace PhWidgets
{
		
	class Timer:
		protected Widget
	{
	public:

		struct ThisArgs
		{												
			struct ArgUnsignedLong
			{
				enum eArgUnsignedLong
				{
					timer_initial = Pt_ARG_TIMER_INITIAL,
					timer_repeat = Pt_ARG_TIMER_REPEAT
				};
			};

		};

		struct ThisCallbacks
		{
			struct Callback
			{
				enum eCallback
				{
					timer_activate = Pt_CB_TIMER_ACTIVATE
				};
			};
		};
		
		struct ArgUnsignedLong:
			public ThisArgs::ArgUnsignedLong
		{
		};

		struct ArgPVoid
		{
			static const Widget::ArgPVoid::eArgPVoid pointer;
			static const Widget::ArgPVoid::eArgPVoid data;
			static const Widget::ArgPVoid::eArgPVoid user_data;
		};

		Widget::ArgLong;//Pt_ARG_FLAGS

		struct Callback :
			public ArgumentsEx<ThisCallbacks::Callback>,
			public Widget::Callback
		{
			using ThisCallbacks::Callback::eCallback;
		};
		
		struct Arguments:
			public ArgUnsignedLong,
			public Widget::ArgLong,
			public ArgPVoid
		{
		};

		struct Callbacks :
			public Callback,
			public Widget::Callbacks
		{
		};

		
	protected:
		typedef ResourceFrom<Widget::WidgetResourcesSingleton>::
			Define::Scalar<ThisArgs::ArgUnsignedLong::eArgUnsignedLong, unsigned long>::

			Define::Link<ThisCallbacks::Callback::eCallback, PtCallback_t*>::

		resource_type WidgetResourcesSingleton;

		virtual void check();
						
	public:
		WidgetResourcesSingleton resource;

		Timer(int abn);
		Timer(PtWidget_t *wdg);

		Timer(const Timer &rhs);

		Timer &operator=(const Timer &rhs);
		using Widget::operator=;
		using Widget::operator==;
		using Widget::operator<;

		using Widget::operator PtWidget_t*;
		using Widget::operator const PtWidget_t*;

		phproperty<unsigned long>::bind<Timer, ArgUnsignedLong::eArgUnsignedLong, Arguments::timer_initial> Initial;
		phproperty<unsigned long>::bind<Timer, ArgUnsignedLong::eArgUnsignedLong, Arguments::timer_repeat> Interval;
		Widget::Enabled;

		phwidgets_event<Timer, Timer::Callbacks::timer_activate>		Activate;

		void OnActivate(PtCallbackInfo_t *info);
	};
}

#endif