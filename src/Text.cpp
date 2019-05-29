#include "Text.h"

#include <stdexcept>

using namespace PhWidgets;

void Text::check()
{
	if(PtWidgetIsClassMember( widget(), PtText ) != true)
		throw(std::invalid_argument("Text: widget is not PtText."));
}


Text::Text(int abn):
	Label(abn),
	resource(this),
	//callbacks:
	ModifyNotify(this),
	ModifyVerify(this),
	MotionNotify(this),
	MotionVerify(this),
	TextChanged(this)

{
	check();
}

Text::Text(PtWidget_t *wdg):
	Label(wdg),
	resource(this),
	//callbacks:
	ModifyNotify(this),
	ModifyVerify(this),
	MotionNotify(this),
	MotionVerify(this),
	TextChanged(this)
{
	check();
}

PhWidgets::Text::Text(const Text & rhs):
	Label(rhs),
	resource(this),
	//callbacks:
	ModifyNotify(this),
	ModifyVerify(this),
	MotionNotify(this),
	MotionVerify(this),
	TextChanged(this)
{
}

Text &Text::operator=(const Text &rhs)
{
	static_cast<Label&>(*this) = static_cast<const Label&>(rhs);
	
	return *this;
}

