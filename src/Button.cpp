#include "Button.h"

#include <stdexcept>

using namespace PhWidgets;

void Button::check()
{
	if(PtWidgetIsClassMember( widget(), PtButton ) != true)
		throw(std::invalid_argument("Button: widget is not PtButton."));
}


Button::Button(int abn):
	Label(abn),
	resource(this),
	ArmColor(this)
{
	check();
}

Button::Button(PtWidget_t *wdg):
	Label(wdg),
	resource(this),
	ArmColor(this)
{
	check();
}


Button::Button(const Button &rhs):
	Label(rhs),
	resource(this),
	ArmColor(this)
{

}

Button &Button::operator=(const Button &rhs)
{
	static_cast<Label&>(*this) = static_cast<const Label&>(rhs);
	
	return *this;
}