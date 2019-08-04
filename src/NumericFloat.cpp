#include "NumericFloat.h"

#include <stdexcept>


using namespace PhWidgets;

namespace PhWidgets
{
    const char * WidgetClassName(PtWidget_t *wdg);
}

#define FORM_THROW_MESSAGE(xxx) (std::string("PhWidgets::") + std::string(#xxx": wrong class of photon widget - got \'") + WidgetClassName(widget()) + "\' instead of \'Pt"#xxx"\'").c_str()
#define WIDGET_IS_CLASS_MEMBER(xxx) \
	if(PtWidgetIsClassMember( widget(), Pt##xxx ) != true)\
		throw(std::invalid_argument(FORM_THROW_MESSAGE(xxx)));

#define CHECK_WIDGET(xxx) \
void xxx::check() \
{ \
	WIDGET_IS_CLASS_MEMBER(xxx); \
}

CHECK_WIDGET(NumericFloat);


NumericFloat::NumericFloat(int abn):
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

NumericFloat::NumericFloat(PtWidget_t *wdg):
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

NumericFloat::NumericFloat(const NumericFloat &other):
	Numeric(other),
	resource(this),
	//properties:
	Value(this),
	MaxValue(this),
	MinValue(this),
	//callbacks:
	NumericChanged(this)
{
}

NumericFloat &NumericFloat::operator=(const NumericFloat &other)
{
	static_cast<Numeric&>(*this) = static_cast<const Numeric&>(other);
	
	return *this;
}

double NumericFloat::getValue() const
{
	return resource.argument[Arguments::numeric_value].get();
}

void NumericFloat::setValue(double val)
{
	resource.argument[Arguments::numeric_value].set(val);
}

double NumericFloat::getMaxValue() const
{
	return resource.argument[Arguments::numeric_max].get();
}

void NumericFloat::setMaxValue(double val)
{
	resource.argument[Arguments::numeric_max].set(val);
}

double NumericFloat::getMinValue() const
{
	return resource.argument[Arguments::numeric_min].get();
}

void NumericFloat::setMinValue(double val)
{
	resource.argument[Arguments::numeric_min].set(val);
}



