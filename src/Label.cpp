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
	resource(this),
	Caption(this),
	BalloonColor(this)
{
	check();
}

Label::Label(PtWidget_t *wdg):
	Basic(wdg),
	resource(this),
	Caption(this),
	BalloonColor(this)
{
	check();
}

Label::Label(const Label &rhs):
	Basic(rhs),
	resource(this),
	Caption(this),
	BalloonColor(this)
{
	
}

Label &Label::operator=(const Label &rhs)
{
	static_cast<Basic&>(*this) = static_cast<const Basic&>(rhs);
	
	return *this;
}

std::string Label::getCaption() const
{
	return resource.argument[Arguments::text_string].get();
}

void Label::setCaption(std::string caption)
{
	resource.argument[Arguments::text_string].set(caption.c_str());
}

