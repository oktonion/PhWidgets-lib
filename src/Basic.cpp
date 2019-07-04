#include "Basic.h"

#include <stdexcept>


using namespace PhWidgets;

namespace PhWidgets
{
    const char * WidgetClassName(PtWidget_t *wdg);
}

#define FORM_THROW_MESSAGE(xxx) (std::string(#xxx": wrong class of photon widget - got \'") + WidgetClassName(widget()) + "\' instead of \'Pt"#xxx"\'").c_str()
#define WIDGET_IS_CLASS_MEMBER(xxx) \
	if(PtWidgetIsClassMember( widget(), Pt##xxx ) != true)\
		throw(std::invalid_argument(FORM_THROW_MESSAGE(xxx)));

#define CHECK_WIDGET(xxx) \
void xxx::check() \
{ \
	WIDGET_IS_CLASS_MEMBER(xxx); \
}

CHECK_WIDGET(Basic);


Basic::Basic(int abn):
	Widget(abn),
	resource(this),
	//properties:
	BevelColor(this),
	Color(this),
	DarkBevelColor(this),
	DarkFillColor(this),
	FillColor(this),
	InlineColor(this),
	LightBevelColor(this),
	LightFillColor(this),
	MarginHeight(this),
	MarginWidth(this),
	OutlineColor(this),
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
	DarkBevelColor(this),
	DarkFillColor(this),
	FillColor(this),
	InlineColor(this),
	LightBevelColor(this),
	LightFillColor(this),
	MarginHeight(this),
	MarginWidth(this),
	OutlineColor(this),
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
	DarkBevelColor(this),
	DarkFillColor(this),
	FillColor(this),
	InlineColor(this),
	LightBevelColor(this),
	LightFillColor(this),
	MarginHeight(this),
	MarginWidth(this),
	OutlineColor(this),
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