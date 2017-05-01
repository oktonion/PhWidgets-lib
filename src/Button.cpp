#include "Button.h"
#include "./service/mystd/my_exception.h"

using namespace PhWidgets;

void Button::check()
{
	if(PtWidgetIsClassMember( widget(), PtButton ) != true)
		throw(std::mystd::exception("Button: widget is not PtButton."));
}


Button::Button(int abn):
	Label(abn),
	ArmColor(this)
{
	check();
}

Button::Button(PtWidget_t *wdg):
	Label(wdg),
	ArmColor(this)
{
	check();
}


Button::Button(const Button &rhs):
	Label(rhs),
	ArmColor(this)
{

}

void Button::setArmColor(PgColor_t val)
{
	resource.argument[Arguments::arm_color].set(val);
}

PgColor_t Button::getArmColor() const
{
	return resource.argument[Arguments::arm_color].get();
}