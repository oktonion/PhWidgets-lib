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
	Font(this),
	BalloonColor(this)
{
	check();
}

Label::Label(PtWidget_t *wdg):
	Basic(wdg),
	resource(this),
	Caption(this),
	Font(this),
	BalloonColor(this)
{
	check();
}

Label::Label(const Label &other):
	Basic(other),
	resource(this),
	Caption(this),
	Font(this),
	BalloonColor(this)
{
	
}

Label &Label::operator=(const Label &other)
{
	static_cast<Basic&>(*this) = static_cast<const Basic&>(other);
	
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

FontDef Label::getFont() const
{
	const char *text_font = resource.argument[Arguments::text_font].get();

	FontID *id = PfDecomposeStemToID(text_font);

	if(NULL == id)
		throw(std::invalid_argument(std::string("Label::Font is an invalid string (\"") + text_font + "\")."));
}

void Label::setFont(FontDef fdef)
{
	resource.argument[Arguments::text_font].set(fdef.Name.c_str());
}

