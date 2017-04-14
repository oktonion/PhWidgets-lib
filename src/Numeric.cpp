#include "Numeric.h"
#include "./service/mystd/my_exception.h"


using namespace PhWidgets;

void Numeric::check()
{
	if(PtWidgetIsClassMember( widget(), PtNumeric ) != true)
		throw(std::mystd::exception("Numeric: widget is not PtNumeric."));
}


Numeric::Numeric(int abn):
	Compound(abn)
{
	check();
}

Numeric::Numeric(PtWidget_t *wdg):
	Compound(wdg)
{
	check();
}


