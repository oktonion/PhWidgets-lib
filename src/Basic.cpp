#include "Basic.h"
#include "./service/mystd/my_exception.h"


using namespace PhWidgets;

void Basic::check()
{
	if(PtWidgetIsClassMember( widget(), PtBasic ) != true)
		throw(std::mystd::exception("Basic: widget is not PtBasic."));
}


Basic::Basic(int abn):
	Widget(abn),
	//properties:
	Color(this),
	FillColor(this),
	//callbacks:
	Activate(this),
	Arm(this),
	Disarm(this),
	GotFocus(this),
	LostFocus(this),
	Menu(this),
	Repeat(this)
{
	check();
}

Basic::Basic(PtWidget_t *wdg):
	Widget(wdg),
	//properties:
	Color(this),
	FillColor(this),
	//callbacks:
	Activate(this),
	Arm(this),
	Disarm(this),
	GotFocus(this),
	LostFocus(this),
	Menu(this),
	Repeat(this)
{
	check();
}

Basic::Basic(const Basic &rhs):
	Widget(rhs),
	//properties:
	Color(this),
	FillColor(this),
	//callbacks:
	Activate(this),
	Arm(this),
	Disarm(this),
	GotFocus(this),
	LostFocus(this),
	Menu(this),
	Repeat(this)
{

}

void Basic::setColor(PgColor_t val)
{
	resource.argument[Arguments::color].set(val);
}

PgColor_t Basic::getColor() const
{
	return resource.argument[Arguments::color].get();
}

void Basic::setFillColor(PgColor_t val)
{
	resource.argument[Arguments::fill_color].set(val);
}

PgColor_t Basic::getFillColor() const
{
	return resource.argument[Arguments::fill_color].get();
}

void PhWidgets::Basic::addActivateCallback(Widget::callback_t callback)
{
	resource.callback[Callbacks::activate].add(callback);
}

void PhWidgets::Basic::addArmCallback(Widget::callback_t callback)
{
	resource.callback[Callbacks::arm].add(callback);
}

void PhWidgets::Basic::addDisarmCallback(Widget::callback_t callback)
{
	resource.callback[Callbacks::disarm].add(callback);
}

void PhWidgets::Basic::addGotFocusCallback(Widget::callback_t callback)
{
	resource.callback[Callbacks::got_focus].add(callback);
}

void PhWidgets::Basic::addLostFocusCallback(Widget::callback_t callback)
{
	resource.callback[Callbacks::lost_focus].add(callback);
}

void PhWidgets::Basic::addMenuCallback(Widget::callback_t callback)
{
	resource.callback[Callbacks::menu].add(callback);
}

void PhWidgets::Basic::addRepeatCallback(Widget::callback_t callback)
{
	resource.callback[Callbacks::repeat].add(callback);
}

void PhWidgets::Basic::OnActivated(void * data, PtCallbackInfo_t * info)
{
	onEvent(resource.callback[Callback::activate].get(), data, info);
}

void PhWidgets::Basic::OnArmed(void * data, PtCallbackInfo_t * info)
{
	onEvent(resource.callback[Callback::arm].get(), data, info);
}

void PhWidgets::Basic::OnDisarmed(void * data, PtCallbackInfo_t * info)
{
	onEvent(resource.callback[Callback::disarm].get(), data, info);
}

void PhWidgets::Basic::OnGotFocused(void * data, PtCallbackInfo_t * info)
{
	onEvent(resource.callback[Callback::got_focus].get(), data, info);
}

void PhWidgets::Basic::OnLostFocus(void * data, PtCallbackInfo_t * info)
{
	onEvent(resource.callback[Callback::lost_focus].get(), data, info);
}

void PhWidgets::Basic::OnMenu(void * data, PtCallbackInfo_t * info)
{
	onEvent(resource.callback[Callback::menu].get(), data, info);
}

void PhWidgets::Basic::OnRepeat(void * data, PtCallbackInfo_t * info)
{
	onEvent(resource.callback[Callback::repeat].get(), data, info);
}
