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
	check();
}


void ToggleButton::Check(bool val)
{
	if(val)
		argument.resource[Arguments::flags].set(Pt_SET, true);
}

void ToggleButton::Uncheck(bool val)
{
	if(val)
		argument.resource[Arguments::flags].set(Pt_SET, false);
}

void ToggleButton::setChecked(bool val)
{
	if(val)
		argument.resource[Arguments::flags].set(Pt_SET, Pt_SET);
	else
		argument.resource[Arguments::flags].set(0x0, Pt_SET);
}

bool ToggleButton::getChecked() const
{
	return argument.resource[Arguments::flags].get(Pt_SET);
}

