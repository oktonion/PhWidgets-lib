#include "Graphic.h"

#include <stdexcept>


using namespace PhWidgets;

void Graphic::check()
{
	if(PtWidgetIsClassMember( widget(), PtGraphic ) != true)
		throw(std::invalid_argument("Graphic: widget is not PtGraphic."));
}


Graphic::Graphic(int abn):
	Basic(abn),
	resource(this),
	//callbacks:
	Rescale(this)
{
	check();
}

Graphic::Graphic(PtWidget_t *wdg):
	Basic(wdg),
	resource(this),
	//callbacks:
	Rescale(this)
{
	check();
}

PhWidgets::Graphic::Graphic(const Graphic & rhs):
	Basic(rhs),
	resource(this),
	//callbacks:
	Rescale(this)
{
}

Graphic &Graphic::operator=(const Graphic &rhs)
{
	static_cast<Basic&>(*this) = static_cast<const Basic&>(rhs);
	
	return *this;
}


