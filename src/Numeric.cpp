#include "Numeric.h"

#include <stdexcept>


using namespace PhWidgets;

void Numeric::check()
{
	if(PtWidgetIsClassMember( widget(), PtNumeric ) != true)
		throw(std::invalid_argument("Numeric: widget is not PtNumeric."));
}


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

PhWidgets::Numeric::Numeric(const Numeric & rhs) :
	Compound(rhs),
	resource(this)
{
}


