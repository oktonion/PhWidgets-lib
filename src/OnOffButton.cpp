#include "OnOffButton.h"

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

CHECK_WIDGET(OnOffButton);

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

OnOffButton::OnOffButton(const OnOffButton &other):
	Button(other),
	resource(this),
	//properties:
	Checked(this),
	//callbacks:
	NewValue(this)
{
}

OnOffButton &OnOffButton::operator=(const OnOffButton &other)
{
	static_cast<Button&>(*this) = static_cast<const Button&>(other);
	
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


