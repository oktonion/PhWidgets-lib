#include "ImageArea.h"

#include "./service/stdex/stdex.h"

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

CHECK_WIDGET(ImageArea);


ImageArea::ImageArea(int abn):
	Container(abn),
	resource(this),
	//properties:
    AutoScale(this),
    GridColor(this),
    GridThreshold(this),
	Image(this),
    ZoomingFactor(this),
    //events:
    Drag(this),
    Movement(this),
    Scrolled(this),
    Selection(this)
{
	check();
}

ImageArea::ImageArea(PtWidget_t *wdg):
	Container(wdg),
	resource(this),
	//properties:
    AutoScale(this),
    GridColor(this),
    GridThreshold(this),
	Image(this),
    ZoomingFactor(this),
    //events:
    Drag(this),
    Movement(this),
    Scrolled(this),
    Selection(this)
{
	check();
}

ImageArea::ImageArea(const ImageArea &other):
	Container(other),
	resource(this),
	//properties:
    AutoScale(this),
    GridColor(this),
    GridThreshold(this),
	Image(this),
    ZoomingFactor(this),
    //events:
    Drag(this),
    Movement(this),
    Scrolled(this),
    Selection(this)
{
	
}

ImageArea &ImageArea::operator=(const ImageArea &other)
{
	static_cast<Container&>(*this) = static_cast<const Container&>(other);
	
	return *this;
}

Drawing::Image ImageArea::getImage() const
{
	const PhImage_t *result = resource.argument[Arguments::imagearea_image].get();

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

void ImageArea::setImage(Drawing::Image image)
{
	PhImage_t *result = image;
	assert(result != nullptr);
	resource.argument[Arguments::imagearea_image].set(result);
}

void ImageArea::setAutoScale(bool val)
{
	if(resource.argument[Arguments::flags].set(Flags::Autoscale, val) != 0)
		throw(
			std::invalid_argument(std::string("PhWidets::ImageArea::AutoScale: \'") + WidgetClassName(widget()) + "\' - cannot set flags of a widget."));
}

bool ImageArea::getAutoScale() const
{
	return resource.argument[Arguments::imagearea_flags].get(Flags::Autoscale);
}

cppbitmasks::bitmask<unsigned short, PhWidgets::ImageArea::Flags::eImageAreaFlags> operator|(const PhWidgets::ImageArea::Flags::eImageAreaFlags &flag1, const PhWidgets::ImageArea::Flags::eImageAreaFlags &flag2)
{
	cppbitmasks::bitmask<unsigned short, PhWidgets::ImageArea::Flags::eImageAreaFlags> bm(flag1);
	return bm | flag2;
}

cppbitmasks::bitmask<unsigned short, PhWidgets::ImageArea::Flags::eImageAreaFlags> operator&(const PhWidgets::ImageArea::Flags::eImageAreaFlags &flag1, const PhWidgets::ImageArea::Flags::eImageAreaFlags &flag2)
{
	cppbitmasks::bitmask<unsigned short, PhWidgets::ImageArea::Flags::eImageAreaFlags> bm(flag1);
	return bm & flag2;
}

cppbitmasks::bitmask<unsigned short, PhWidgets::ImageArea::Flags::eImageAreaFlags> operator^(const PhWidgets::ImageArea::Flags::eImageAreaFlags &flag1, const PhWidgets::ImageArea::Flags::eImageAreaFlags &flag2)
{
	cppbitmasks::bitmask<unsigned short, PhWidgets::ImageArea::Flags::eImageAreaFlags> bm(flag1);
	return bm ^ flag2;
}