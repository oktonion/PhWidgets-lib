#include "Disjoint.h"

#include <stdexcept>


using namespace PhWidgets;

void Disjoint::check()
{
	if(PtWidgetIsClassMember( widget(), PtDisjoint ) != true)
		throw(std::invalid_argument("Disjoint: widget is not PtDisjoint."));
}


Disjoint::Disjoint(int abn):
	Container(abn),
	resource(this),
	//callbacks:
	SysInfo(this)
{
	check();
}

Disjoint::Disjoint(PtWidget_t *wdg):
	Container(wdg),
	resource(this),
	//callbacks:
	SysInfo(this)
{
	check();
}

Disjoint::Disjoint(const Disjoint & rhs):
	Container(rhs),
	resource(this),
	//callbacks:
	SysInfo(this)
{
}

Disjoint &Disjoint::operator=(const Disjoint &rhs)
{
	static_cast<Container&>(*this) = static_cast<const Container&>(rhs);
	
	return *this;
}


