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


Timer::Timer(int abn):
	Widget(abn),
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
	//properties:
	Initial(this),
	Interval(this),
	//callbacks:
	Activate(this)
{

}

void Timer::setInitial(unsigned long val)
{
	resource.argument[Arguments::timer_initial].set(val);
}

unsigned long Timer::getInitial() const
{
	return resource.argument[Arguments::timer_initial].get();
}

void Timer::setRepeat(unsigned long val)
{
	resource.argument[Arguments::timer_repeat].set(val);
}

unsigned long Timer::getRepeat() const
{
	return resource.argument[Arguments::timer_repeat].get();
}

void PhWidgets::Timer::addActivateCallback(Widget::callback_t callback)
{
	resource.callback[Timer::Callbacks::timer_activate].add(callback);
}
