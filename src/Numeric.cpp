#include "Numeric.h"

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

CHECK_WIDGET(Numeric);


Numeric::Numeric(int abn):
	Compound(abn),
	resource(this)
{
	check();
}

Numeric::Numeric(PtWidget_t *wdg):
	Compound(wdg),
	resource(this)
{
	check();
}

Numeric::Numeric(const Numeric & other) :
	Compound(other),
	resource(this)
{
}

Numeric &Numeric::operator=(const Numeric &other)
{
	static_cast<Compound&>(*this) = static_cast<const Compound&>(other);
	
	return *this;
}


