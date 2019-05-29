#include "NumericInteger.h"

#include <stdexcept>


using namespace PhWidgets;

void NumericInteger::check()
{
	if(PtWidgetIsClassMember( widget(), PtNumericInteger ) != true)
		throw(std::invalid_argument("NumericInteger: widget is not PtNumericInteger."));
}


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



