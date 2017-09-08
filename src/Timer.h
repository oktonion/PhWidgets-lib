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
		virtual void check();

		void setInitial(unsigned long);    
		unsigned long getInitial() const;

		void setRepeat(unsigned long);    
		unsigned long getRepeat() const;
						
	public:
		Timer(int abn);
		Timer(PtWidget_t *wdg);

		Timer(const Timer &rhs);

		Timer &operator=(const Timer &rhs);
		using Widget::operator=;
		using Widget::operator==;
		using Widget::operator<;

		using Widget::operator PtWidget_t*;
		using Widget::operator const PtWidget_t*;

		property<unsigned long>::bind<Timer, &Timer::getInitial, &Timer::setInitial> Initial;
		property<unsigned long>::bind<Timer, &Timer::getRepeat, &Timer::setRepeat> Interval;
		Widget::Enabled;

		phwidgets_event<Timer, Timer::Callbacks::timer_activate>		Activate;
	};
	
	INIT_WIDGET_RESOURCE1(Timer::ThisArgs::ArgUnsignedLong::eArgUnsignedLong, unsigned long, Scalar);
	INIT_WIDGET_RESOURCE1(Timer::ThisCallbacks::Callback::eCallback, PtCallback_t, Link);
}

#endif