#include "ToggleButton.h"

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

CHECK_WIDGET(ToggleButton);


ToggleButton::ToggleButton(int abn):
	Button(abn),
	resource(this),
	//properties:
	Checked(this)
{
	check();
}

ToggleButton::ToggleButton(PtWidget_t *wdg):
	Button(wdg),
	resource(this),
	//properties:
	Checked(this)
{
	check();
}

ToggleButton::ToggleButton(const ToggleButton &other):
	Button(other),
	resource(this),
	//properties:
	Checked(this)
{
}

ToggleButton &ToggleButton::operator=(const ToggleButton &other)
{
	static_cast<Button&>(*this) = static_cast<const Button&>(other);
	
	return *this;
}


void ToggleButton::Check(bool val)
{
	if(val)
		resource.argument[Arguments::flags].set(Pt_SET, true);
}

void ToggleButton::Uncheck(bool val)
{
	if(val)
		resource.argument[Arguments::flags].set(Pt_SET, false);
}

void ToggleButton::setChecked(bool val)
{

	resource.argument[Arguments::flags].set(Pt_SET, val);

}

bool ToggleButton::getChecked() const
{
	return resource.argument[Arguments::flags].get(Pt_SET);
}

