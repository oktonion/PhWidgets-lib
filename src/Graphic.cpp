#include "Graphic.h"

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

CHECK_WIDGET(Graphic);


Graphic::Graphic(int abn):
	Basic(abn),
	resource(this),
	//callbacks:
	Rescale(this)
{
	check();
}

Graphic::Graphic(PtWidget_t *wdg):
	Basic(wdg),
	resource(this),
	//callbacks:
	Rescale(this)
{
	check();
}

PhWidgets::Graphic::Graphic(const Graphic & other):
	Basic(other),
	resource(this),
	//callbacks:
	Rescale(this)
{
}

Graphic &Graphic::operator=(const Graphic &other)
{
	static_cast<Basic&>(*this) = static_cast<const Basic&>(other);
	
	return *this;
}


