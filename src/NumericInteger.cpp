#include "NumericInteger.h"
#include "./service/mystd/my_exception.h"


using namespace PhWidgets;

void NumericInteger::check()
{
	if(PtWidgetIsClassMember( widget(), PtNumericInteger ) != true)
		throw(std::mystd::exception("NumericInteger: widget is not PtNumericInteger."));
}


NumericInteger::NumericInteger(int abn):
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

NumericInteger::NumericInteger(PtWidget_t *wdg):
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

NumericInteger::NumericInteger(const NumericInteger &rhs):
	Numeric(rhs),
	//properties:
	Value(this),
	MaxValue(this),
	MinValue(this),
	//callbacks:
	NumericChanged(this)

{
}

int NumericInteger::getValue() const
{
	return resource.argument[Arguments::numeric_value].get();
}

void NumericInteger::setValue(int val)
{
	resource.argument[Arguments::numeric_value].set(val);
}

int NumericInteger::getMaxValue() const
{
	return resource.argument[Arguments::numeric_max].get();
}

void NumericInteger::setMaxValue(int val)
{
	resource.argument[Arguments::numeric_max].set(val);
}


int NumericInteger::getMinValue() const
{
	return resource.argument[Arguments::numeric_min].get();
}

void NumericInteger::setMinValue(int val)
{
	resource.argument[Arguments::numeric_min].set(val);
}

void PhWidgets::NumericInteger::addNumericChangedCallback(callback_t callback)
{
	resource.callback[ThisCallbacks::Callback::numeric_changed].add(callback);
}



