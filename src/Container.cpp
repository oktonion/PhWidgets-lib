#include "Container.h"
#include "./service/mystd/my_exception.h"


using namespace PhWidgets;

void Container::check()
{
	if(PtWidgetIsClassMember( widget(), PtContainer ) != true)
		throw(std::mystd::exception("Container: widget is not PtContainer."));
}


Container::Container(int abn):
	Basic(abn)
{
	check();
}

Container::Container(PtWidget_t *wdg):
	Basic(wdg)
{
	check();
}


