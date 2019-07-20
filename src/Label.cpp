#include "Label.h"

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

CHECK_WIDGET(Label);


Label::Label(int abn):
	Basic(abn),
	resource(this),
	Text(this),
	Font(this),
	BalloonColor(this),
	BalloonPosition(this),
	Type(this)
{
	check();
}

Label::Label(PtWidget_t *wdg):
	Basic(wdg),
	resource(this),
	Text(this),
	Font(this),
	BalloonColor(this),
	BalloonPosition(this),
	Type(this)
{
	check();
}

Label::Label(const Label &other):
	Basic(other),
	resource(this),
	Text(this),
	Font(this),
	BalloonColor(this),
	BalloonPosition(this),
	Type(this)
{
	
}

Label &Label::operator=(const Label &other)
{
	static_cast<Basic&>(*this) = static_cast<const Basic&>(other);
	
	return *this;
}

std::string Label::getText() const
{
	return resource.argument[Arguments::text_string].get();
}

void Label::setText(std::string caption)
{
	resource.argument[Arguments::text_string].set(caption.c_str());
}

Drawing::Font Label::getFont() const
{
	const char *text_font = resource.argument[Arguments::text_font].get();

	FontID *fid = PfDecomposeStemToID(text_font);

	if(NULL == fid)
		throw(std::invalid_argument(std::string("Label::Font is an invalid string (\"") + text_font + "\")."));
	
	return fid;
}

void Label::setFont(Drawing::Font fdef)
{
	resource.argument[Arguments::text_font].set(fdef.Name.c_str());
}

void Label::setBalloonPosition(PhWidgets::BalloonPosition::eBalloonPosition val)
{
	resource.argument[Arguments::balloon_position].set(val);
}

PhWidgets::BalloonPosition::eBalloonPosition Label::getBalloonPosition() const
{
	short result = resource.argument[Arguments::balloon_position].get();
	switch(result)
	{
		case BalloonPosition::Inplace:
			break;
		case BalloonPosition::Top:
			break;
		case BalloonPosition::Left:
			break;
		case BalloonPosition::Right:
			break;
		case BalloonPosition::Bottom:
			break;
		default:
			throw(std::invalid_argument("Label::BalloonPosition is invalid."));
	}
	return static_cast<BalloonPosition::eBalloonPosition>(result);
}

void Label::setType(PhWidgets::LabelType::eLabelType val)
{
	resource.argument[Arguments::label_type].set(val);
}

PhWidgets::LabelType::eLabelType Label::getType() const
{
	short result = resource.argument[Arguments::label_type].get();
	switch(result)
	{
		case LabelType::Image:
			break;
		case LabelType::String:
			break;
		case LabelType::TextImage:
			break;
		default:
			throw(std::invalid_argument("Label::Type is invalid."));
	}
	return static_cast<LabelType::eLabelType>(result);
}