#include "ImageArea.h"

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
    ImageLocation(this),
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
    ImageLocation(this),
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
    ImageLocation(this),
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