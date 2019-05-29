#include "Compound.h"

#include <stdexcept>


using namespace PhWidgets;

void Compound::check()
{
	if(PtWidgetIsClassMember( widget(), PtCompound ) != true)
		throw(std::invalid_argument("Compound: widget is not PtCompound."));
}


Compound::Compound(int abn):
	Container(abn)
{
	check();
}

Compound::Compound(PtWidget_t *wdg):
	Container(wdg)
{
	check();
}


