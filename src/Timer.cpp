#include "Timer.h"
#include "./service/mystd/my_exception.h"


using namespace PhWidgets;

const Widget::ArgPVoid::eArgPVoid Timer::ArgPVoid::data = Widget::ArgPVoid::data;
const Widget::ArgPVoid::eArgPVoid Timer::ArgPVoid::user_data = Widget::ArgPVoid::user_data;
const Widget::ArgPVoid::eArgPVoid Timer::ArgPVoid::pointer = Widget::ArgPVoid::pointer;

void Timer::check()
{
	if(PtWidgetIsClassMember( widget(), PtTimer ) != true)
		throw(std::mystd::exception("Timer: widget is not PtTimer."));
}


Timer::Timer(int abn) :
	Widget(abn),
	resource(this),
	//properties:
	Initial(this),
	Interval(this),
	//callbacks:
	Activate(this)
{
	check();
}

Timer::Timer(PtWidget_t *wdg):
	Widget(wdg),
	resource(this),
	//properties:
	Initial(this),
	Interval(this),
	//callbacks:
	Activate(this)
{
	check();
}

Timer::Timer(const Timer &rhs):
	Widget(rhs),
	resource(this),
	//properties:
	Initial(this),
	Interval(this),
	//callbacks:
	Activate(this)
{
}

Timer &Timer::operator=(const Timer &rhs)
{
	static_cast<Widget&>(*this) = static_cast<const Widget&>(rhs);
	
	return *this;
}

void Timer::OnActivate(PtCallbackInfo_t *info)
{
	resource.callback[Callback::timer_activate].raise(info);
}