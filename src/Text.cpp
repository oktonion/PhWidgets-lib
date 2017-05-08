#include "Text.h"
#include "./service/mystd/my_exception.h"

using namespace PhWidgets;

void Text::check()
{
	if(PtWidgetIsClassMember( widget(), PtText ) != true)
		throw(std::mystd::exception("Text: widget is not PtText."));
}


Text::Text(int abn):
	Label(abn),
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
	//callbacks:
	ModifyNotify(this),
	ModifyVerify(this),
	MotionNotify(this),
	MotionVerify(this),
	TextChanged(this)
{
}

