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
	//properties:
	Value(this),
	MaxValue(this),
	MinValue(this),
	//callbacks:
	NumericChanged(this)

{
	check();
}

NumericFloat::NumericFloat(const NumericFloat &rhs):
	Numeric(rhs),
	//properties:
	Value(this),
	MaxValue(this),
	MinValue(this),
	//callbacks:
	NumericChanged(this)
{
}

double NumericFloat::getValue() const
{
	return *(resource.argument[Arguments::numeric_value].get());
}

void NumericFloat::setValue(double val)
{
	resource.argument[Arguments::numeric_value].set(&val);
}

double NumericFloat::getMaxValue() const
{
	return *(resource.argument[Arguments::numeric_max].get());
}

void NumericFloat::setMaxValue(double val)
{
	resource.argument[Arguments::numeric_max].set(&val);
}

double NumericFloat::getMinValue() const
{
	return *(resource.argument[Arguments::numeric_min].get());
}

void NumericFloat::setMinValue(double val)
{
	resource.argument[Arguments::numeric_min].set(&val);
}

void PhWidgets::NumericFloat::addNumericChangedCallback(callback_t callback)
{
	resource.callback[ThisCallbacks::Callback::numeric_changed].add(callback);
}



