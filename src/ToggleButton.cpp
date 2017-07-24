#include "ToggleButton.h"
#include "./service/mystd/my_exception.h"

using namespace PhWidgets;

void ToggleButton::check()
{
	if(PtWidgetIsClassMember( widget(), PtToggleButton ) != true)
		throw(std::mystd::exception("ToggleButton: widget is not PtToggleButton."));
}


ToggleButton::ToggleButton(int abn):
	Button(abn),
	Checked(this)
{
	check();
}

ToggleButton::ToggleButton(PtWidget_t *wdg):
	Button(wdg),
	Checked(this)
{
	check();
}

ToggleButton::ToggleButton(const ToggleButton &rhs):
	Button(rhs),
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

