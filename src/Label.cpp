#include "Label.h"

#include <stdexcept>
#include <cassert>

using namespace PhWidgets;

namespace PhWidgets
{
    const char * WidgetClassName(PtWidget_t *wdg);
}

#define FORM_THROW_MESSAGE(xxx) (std::string("PhWidgets::") + std::string(#xxx": wrong class of photon widget - got \'") + WidgetClassName(widget()) + "\' instead of \'Pt"#xxx"\'.").c_str()
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
	//properties:
	Image(this),
	Text(this),
	Font(this),
	BalloonColor(this),
	BalloonFillColor(this),
	BalloonPosition(this),
	TextAlign(this),
	TextClippedAlign(this),
	Type(this),
	UnderlineColor1(this),
	UnderlineColor2(this),
	UnderlineType(this)
{
	check();
}

Label::Label(PtWidget_t *wdg):
	Basic(wdg),
	resource(this),
	//properties:
	Image(this),
	Text(this),
	Font(this),
	BalloonColor(this),
	BalloonFillColor(this),
	BalloonPosition(this),
	TextAlign(this),
	TextClippedAlign(this),
	Type(this),
	UnderlineColor1(this),
	UnderlineColor2(this),
	UnderlineType(this)
{
	check();
}

Label::Label(const Label &other):
	Basic(other),
	resource(this),
	//properties:
	Image(this),
	Text(this),
	Font(this),
	BalloonColor(this),
	BalloonFillColor(this),
	BalloonPosition(this),
	TextAlign(this),
	TextClippedAlign(this),
	Type(this),
	UnderlineColor1(this),
	UnderlineColor2(this),
	UnderlineType(this)
{
	
}

Label &Label::operator=(const Label &other)
{
	static_cast<Basic&>(*this) = static_cast<const Basic&>(other);
	
	return *this;
}

Drawing::Image Label::getImage() const
{
	const PhImage_t *result = resource.argument[Arguments::label_image].get();

	if(nullptr != result)
		return Drawing::Image(*result);
	else
	{
		PhImage_t empty;
		empty.image = nullptr;
		empty.size.w = 0;
		empty.size.h = 0;
		return Drawing::Image(empty);
	}
}

void Label::setImage(Drawing::Image image)
{
	PhImage_t *result = image;
	assert(result != nullptr);
	resource.argument[Arguments::label_image].set(result);
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
	char result = resource.argument[Arguments::label_type].get();
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

void Label::setUnderlineType(PhWidgets::UnderlineType::eUnderlineType val)
{
	resource.argument[Arguments::undeline_type].set(val);
}

PhWidgets::UnderlineType::eUnderlineType Label::getUnderlineType() const
{
	unsigned short result = resource.argument[Arguments::undeline_type].get();
	switch(result)
	{
		case UnderlineType::DoubleUline:
			break;
		case UnderlineType::NoUline:
			break;
		case UnderlineType::SingleUline:
			break;
		case UnderlineType::UlineEtchedIn:
			break;
		case UnderlineType::UlineEtchedOut:
			break;
		default:
			throw(std::invalid_argument("Label::UnderlineType is invalid."));
	}
	return static_cast<UnderlineType::eUnderlineType>(result);
}

void Label::setTextAlign(Drawing::ContentAlignment::eContentAlignment val)
{
	#define PHWIDGETS_V(v) ((short)(((v) >> 8) & 0xFF))
	#define PHWIDGETS_H(h) ((short)((h) & 0xFF))

	resource.argument[Arguments::vertical_alingment].set(PHWIDGETS_V(val));
	resource.argument[Arguments::horizontal_alignment].set(PHWIDGETS_H(val));

	#undef PHWIDGETS_V
	#undef PHWIDGETS_H
}

Drawing::ContentAlignment::eContentAlignment Label::getTextAlign() const
{
	#define	PHWIDGETS_VH(v,h) (((short)((v) & 0xFF) << 8) | (short)((h) & 0xFF))

	unsigned char v = resource.argument[Arguments::vertical_alingment].get();
	unsigned char h = resource.argument[Arguments::horizontal_alignment].get();

	return static_cast<Drawing::ContentAlignment::eContentAlignment>(PHWIDGETS_VH(v, h));

	#undef	PHWIDGETS_VH
}

void Label::setTextClippedAlign(Drawing::ContentAlignment::eContentAlignment val)
{
	#define PHWIDGETS_V(v) ((short)(((v) >> 8) & 0xFF))
	#define PHWIDGETS_H(h) ((short)((h) & 0xFF))

	resource.argument[Arguments::secondary_v_align].set(PHWIDGETS_V(val));
	resource.argument[Arguments::secondary_h_align].set(PHWIDGETS_H(val));

	#undef PHWIDGETS_V
	#undef PHWIDGETS_H
}

Drawing::ContentAlignment::eContentAlignment Label::getTextClippedAlign() const
{
	#define	PHWIDGETS_VH(v,h) (((short)((v) & 0xFF) << 8) | (short)((h) & 0xFF))

	unsigned char v = resource.argument[Arguments::secondary_v_align].get();
	unsigned char h = resource.argument[Arguments::secondary_h_align].get();

	return static_cast<Drawing::ContentAlignment::eContentAlignment>(PHWIDGETS_VH(v, h));

	#undef	PHWIDGETS_VH
}