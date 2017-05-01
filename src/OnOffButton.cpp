#include "OnOffButton.h"
#include "./service/mystd/my_exception.h"


using namespace PhWidgets;

void OnOffButton::check()
{
	if(PtWidgetIsClassMember( widget(), PtOnOffButton ) != true)
		throw(std::mystd::exception("OnOffButton: widget is not PtOnOffButton."));
}

OnOffButton::OnOffButton(int abn):
	Button(abn),
	Checked(this)
{
	check();
}

OnOffButton::OnOffButton(PtWidget_t *wdg):
	Button(wdg),
	Checked(this)
{
	check();
}

OnOffButton::OnOffButton(const OnOffButton &rhs):
	Button(rhs),
	Checked(this)
{
	check();
}

void OnOffButton::Check(bool val)
{
	if(val)
		resource.argument[Arguments::onoff_state].set(true);
}

void OnOffButton::Uncheck(bool val)
{
	if(val)
		resource.argument[Arguments::onoff_state].set(false);
}

void OnOffButton::setChecked(bool val)
{
	resource.argument[Arguments::onoff_state].set(val);
}

bool OnOffButton::getChecked() const
{
	return resource.argument[Arguments::onoff_state].get();
}

