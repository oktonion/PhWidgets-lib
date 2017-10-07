#include "Container.h"
#include "./service/mystd/my_exception.h"


using namespace PhWidgets;

void Container::check()
{
	if(PtWidgetIsClassMember( widget(), PtContainer ) != true)
		throw(std::mystd::exception("Container: widget is not PtContainer."));
}


Container::Container(int abn):
	Basic(abn),
	resource(this),
	//callbacks:
	ChildAddedRemoved(this),
	ChildGettingFocus(this),
	ChildLosingFocus(this),
	LayoutChanged(this),
	Resize(this)
{
	check();
}

Container::Container(PtWidget_t *wdg):
	Basic(wdg),
	resource(this),
	//callbacks:
	ChildAddedRemoved(this),
	ChildGettingFocus(this),
	ChildLosingFocus(this),
	LayoutChanged(this),
	Resize(this)
{
	check();
}

PhWidgets::Container::Container(const Container & rhs):
	Basic(rhs),
	resource(this),
	//callbacks:
	ChildAddedRemoved(this),
	ChildGettingFocus(this),
	ChildLosingFocus(this),
	LayoutChanged(this),
	Resize(this)
{
}

Container &Container::operator=(const Container &rhs)
{
	static_cast<Basic&>(*this) = static_cast<const Basic&>(rhs);
	
	return *this;
}


