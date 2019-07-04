#include "NumericInteger.h"

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

CHECK_WIDGET(NumericInteger);


NumericInteger::NumericInteger(int abn):
	Numeric(abn),
	resource(this),
	//properties:
	Value(this),
	MaxValue(this),
	MinValue(this),
	//callbacks:
	NumericChanged(this)
	
{
	check();
}

NumericInteger::NumericInteger(PtWidget_t *wdg):
	Numeric(wdg),
	resource(this),
	//properties:
	Value(this),
	MaxValue(this),
	MinValue(this),
	//callbacks:
	NumericChanged(this)

{
	check();
}

NumericInteger::NumericInteger(const NumericInteger &rhs):
	Numeric(rhs),
	resource(this),
	//properties:
	Value(this),
	MaxValue(this),
	MinValue(this),
	//callbacks:
	NumericChanged(this)

{
}

NumericInteger &NumericInteger::operator=(const NumericInteger &rhs)
{
	static_cast<Numeric&>(*this) = static_cast<const Numeric&>(rhs);
	
	return *this;
}



