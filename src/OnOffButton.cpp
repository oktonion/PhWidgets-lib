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
	resource(this),
	//properties:
	Checked(this),
	//callbacks:
	NewValue(this)
{
	check();
}

OnOffButton::OnOffButton(PtWidget_t *wdg):
	Button(wdg),
	resource(this),
	//properties:
	Checked(this),
	//callbacks:
	NewValue(this)
{
	check();
}

OnOffButton::OnOffButton(const OnOffButton &rhs):
	Button(rhs),
	resource(this),
	//properties:
	Checked(this),
	//callbacks:
	NewValue(this)
{
}

OnOffButton &OnOffButton::operator=(const OnOffButton &rhs)
{
	static_cast<Button&>(*this) = static_cast<const Button&>(rhs);
	
	return *this;
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

