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

Basic &Basic::operator=(const Basic &rhs)
{
	static_cast<Widget&>(*this) = static_cast<const Widget&>(rhs);
	
	return *this;
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

void PhWidgets::Basic::OnActivated(PtCallbackInfo_t * info)
{
	onEvent(resource.callback[Callback::activate].get(), info);
}

void PhWidgets::Basic::OnArmed(PtCallbackInfo_t * info)
{
	onEvent(resource.callback[Callback::arm].get(), info);
}

void PhWidgets::Basic::OnDisarmed(PtCallbackInfo_t * info)
{
	onEvent(resource.callback[Callback::disarm].get(), info);
}

void PhWidgets::Basic::OnGotFocused(PtCallbackInfo_t * info)
{
	onEvent(resource.callback[Callback::got_focus].get(), info);
}

void PhWidgets::Basic::OnLostFocus(PtCallbackInfo_t * info)
{
	onEvent(resource.callback[Callback::lost_focus].get(), info);
}

void PhWidgets::Basic::OnMenu(PtCallbackInfo_t * info)
{
	onEvent(resource.callback[Callback::menu].get(), info);
}

void PhWidgets::Basic::OnRepeat(PtCallbackInfo_t * info)
{
	onEvent(resource.callback[Callback::repeat].get(), info);
}
