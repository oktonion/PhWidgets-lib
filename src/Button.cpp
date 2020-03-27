#include "Button.h"

#include <stdexcept>

using namespace PhWidgets;

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

CHECK_WIDGET(Button);


Button::Button(int abn):
	Label(abn),
	resource(this),
	ArmColor(this),
	ArmFill(this)
{
	check();
}

Button::Button(PtWidget_t *wdg):
	Label(wdg),
	resource(this),
	ArmColor(this),
	ArmFill(this)
{
	check();
}


Button::Button(const Button &other):
	Label(other),
	resource(this),
	ArmColor(this),
	ArmFill(this)
{

}

Button &Button::operator=(const Button &other)
{
	static_cast<Label&>(*this) = static_cast<const Label&>(other);
	
	return *this;
}