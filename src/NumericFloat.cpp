#include "NumericFloat.h"
#include "./service/mystd/my_exception.h"


using namespace PhWidgets;

void NumericFloat::check()
{
	if(PtWidgetIsClassMember( widget(), PtNumericFloat ) != true)
		throw(std::mystd::exception("NumericFloat: widget is not PtNumericFloat."));
}


NumericFloat::NumericFloat(int abn):
	Numeric(abn),
	Value(this),
	MaxValue(this),
	MinValue(this)

{
	check();
}

NumericFloat::NumericFloat(PtWidget_t *wdg):
	Numeric(wdg),
	Value(this),
	MaxValue(this),
	MinValue(this)

{
	check();
}

NumericFloat::NumericFloat(const NumericFloat &rhs):
	Numeric(rhs),
	Value(this),
	MaxValue(this),
	MinValue(this)

{
}

double NumericFloat::getValue() const
{
	return *(argument.resource[Arguments::numeric_value].get());
}

void NumericFloat::setValue(double val)
{
	argument.resource[Arguments::numeric_value].set(&val);
}

double NumericFloat::getMaxValue() const
{
	return *(argument.resource[Arguments::numeric_max].get());
}

void NumericFloat::setMaxValue(double val)
{
	argument.resource[Arguments::numeric_max].set(&val);
}

double NumericFloat::getMinValue() const
{
	return *(argument.resource[Arguments::numeric_min].get());
}

void NumericFloat::setMinValue(double val)
{
	argument.resource[Arguments::numeric_min].set(&val);
}



