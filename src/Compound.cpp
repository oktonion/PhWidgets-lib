#include "Compound.h"
#include "./service/mystd/my_exception.h"


using namespace PhWidgets;

void Compound::check()
{
	if(PtWidgetIsClassMember( widget(), PtCompound ) != true)
		throw(std::mystd::exception("Compound: widget is not PtCompound."));
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


