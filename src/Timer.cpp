#include "Timer.h"

#include <stdexcept>


using namespace PhWidgets;

const Widget::ArgPVoid::eArgPVoidData Timer::ArgPVoid::data = Widget::ArgPVoid::data;
const Widget::ArgPVoid::eArgPVoidData Timer::ArgPVoid::user_data = Widget::ArgPVoid::user_data;
const Widget::ArgPVoid::eArgPVoid Timer::ArgPVoid::pointer = Widget::ArgPVoid::pointer;

namespace PhWidgets
{
    const char * WidgetClassName(PtWidget_t *wdg);
}

#define FORM_THROW_MESSAGE(xxx) (std::string("PhWidgets::") + std::string(#xxx": wrong class of photon widget - got \'") + WidgetClassName(widget()) + "\' instead of \'Pt"#xxx"\'.").c_str()
#define WIDGET_IS_CLASS_MEMBER(xxx) \
	if(PtWidgetIsClassMember( widget(), Pt##xxx ) != true)\
		throw(std::invalid_argument(FORM_THROW_MESSAGE(xxx)));

#define CHECK_WIDGET(xxx) \
void xxx::check() \
{ \
	WIDGET_IS_CLASS_MEMBER(xxx); \
}

CHECK_WIDGET(Timer);


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

Timer::Timer(const Timer &other):
	Widget(other),
	resource(this),
	//properties:
	Initial(this),
	Interval(this),
	//callbacks:
	Activate(this)
{
}

Timer &Timer::operator=(const Timer &other)
{
	static_cast<Widget&>(*this) = static_cast<const Widget&>(other);
	
	return *this;
}

void Timer::OnActivate(PtCallbackInfo_t *info)
{
	resource.callback[Callback::timer_activate].raise(info);
}