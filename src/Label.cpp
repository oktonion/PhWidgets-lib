#include "Label.h"
#include "./service/mystd/my_exception.h"

using namespace PhWidgets;

void Label::check()
{
	if(PtWidgetIsClassMember( widget(), PtLabel ) != true)
		throw(std::mystd::exception("Label: widget is not PtLabel."));
}


Label::Label(int abn):
	Basic(abn),
	Caption(this),
	BalloonColor(this)
{
	check();
}

Label::Label(PtWidget_t *wdg):
	Basic(wdg),
	Caption(this),
	BalloonColor(this)
{
	check();
}

Label::Label(const Label &rhs):
	Basic(rhs),
	Caption(this),
	BalloonColor(this)
{
	
}

std::string Label::getCaption() const
{
	return argument.resource[Arguments::text_string].get();
}

void Label::setCaption(std::string caption)
{
	argument.resource[Arguments::text_string].set(caption.c_str());
}

void Label::setBalloonColor(PgColor_t val)
{
	argument.resource[Arguments::balloon_color].set(val);
}

PgColor_t Label::getBalloonColor() const
{
	return argument.resource[Arguments::balloon_color].get();
}

