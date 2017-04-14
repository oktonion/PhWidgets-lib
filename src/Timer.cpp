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
	Initial(this),
	Interval(this)
{
	check();
}

Timer::Timer(PtWidget_t *wdg):
	Widget(wdg),
	Initial(this),
	Interval(this)
{
	check();
}

Timer::Timer(const Timer &rhs):
	Widget(rhs),
	Initial(this),
	Interval(this)
{

}

void Timer::setInitial(unsigned long val)
{
	argument.resource[Arguments::timer_initial].set(val);
}

unsigned long Timer::getInitial() const
{
	return argument.resource[Arguments::timer_initial].get();
}

void Timer::setRepeat(unsigned long val)
{
	argument.resource[Arguments::timer_repeat].set(val);
}

unsigned long Timer::getRepeat() const
{
	return argument.resource[Arguments::timer_repeat].get();
}