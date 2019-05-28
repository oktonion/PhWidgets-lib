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
	resource(this),
	//properties:
	BevelColor(this),
	Color(this),
	FillColor(this),
	MarginHeight(this),
	MarginWidth(this),
	//flags:
	BasicFlags(this),
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
	resource(this),
	//properties:
	BevelColor(this),
	Color(this),
	FillColor(this),
	MarginHeight(this),
	MarginWidth(this),
	//flags:
	BasicFlags(this),
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
	resource(this),
	//properties:
	BevelColor(this),
	Color(this),
	FillColor(this),
	MarginHeight(this),
	MarginWidth(this),
	//flags:
	BasicFlags(this),
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

void PhWidgets::Basic::OnActivated(PtCallbackInfo_t * info)
{
	resource.callback[Callback::activate].raise(info);
}

void PhWidgets::Basic::OnArmed(PtCallbackInfo_t * info)
{
	resource.callback[Callback::arm].raise(info);
}

void PhWidgets::Basic::OnDisarmed(PtCallbackInfo_t * info)
{
	resource.callback[Callback::disarm].raise(info);
}

void PhWidgets::Basic::OnGotFocused(PtCallbackInfo_t * info)
{
	resource.callback[Callback::got_focus].raise(info);
}

void PhWidgets::Basic::OnLostFocus(PtCallbackInfo_t * info)
{
	resource.callback[Callback::lost_focus].raise(info);
}

void PhWidgets::Basic::OnMenu(PtCallbackInfo_t * info)
{
	resource.callback[Callback::menu].raise(info);
}

void PhWidgets::Basic::OnRepeat(PtCallbackInfo_t * info)
{
	resource.callback[Callback::repeat].raise(info);
}

cppbitmasks::bitmask<unsigned long, PhWidgets::Basic::Flags::Basic::eBasic> operator|(const PhWidgets::Basic::Flags::Basic::eBasic &flag1, const PhWidgets::Basic::Flags::Basic::eBasic &flag2)
{
	cppbitmasks::bitmask<unsigned long, PhWidgets::Basic::Flags::Basic::eBasic> bm(flag1);
	return bm | flag2;
}

cppbitmasks::bitmask<unsigned long, PhWidgets::Basic::Flags::Basic::eBasic> operator&(const PhWidgets::Basic::Flags::Basic::eBasic &flag1, const PhWidgets::Basic::Flags::Basic::eBasic &flag2)
{
	cppbitmasks::bitmask<unsigned long, PhWidgets::Basic::Flags::Basic::eBasic> bm(flag1);
	return bm & flag2;
}

cppbitmasks::bitmask<unsigned long, PhWidgets::Basic::Flags::Basic::eBasic> operator^(const PhWidgets::Basic::Flags::Basic::eBasic &flag1, const PhWidgets::Basic::Flags::Basic::eBasic &flag2)
{
	cppbitmasks::bitmask<unsigned long, PhWidgets::Basic::Flags::Basic::eBasic> bm(flag1);
	return bm ^ flag2;
}