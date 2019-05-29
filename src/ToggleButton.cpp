#include "ToggleButton.h"

#include <stdexcept>

using namespace PhWidgets;

void ToggleButton::check()
{
	if(PtWidgetIsClassMember( widget(), PtToggleButton ) != true)
		throw(std::invalid_argument("ToggleButton: widget is not PtToggleButton."));
}


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

ToggleButton::ToggleButton(const ToggleButton &rhs):
	Button(rhs),
	resource(this),
	//properties:
	Checked(this)
{
}

ToggleButton &ToggleButton::operator=(const ToggleButton &rhs)
{
	static_cast<Button&>(*this) = static_cast<const Button&>(rhs);
	
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

