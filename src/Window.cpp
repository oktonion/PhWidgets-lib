#include "Window.h"

#include <stdexcept>


using namespace PhWidgets;

void Window::check()
{
	if(PtWidgetIsClassMember( widget(), PtWindow ) != true)
		throw(std::invalid_argument("Window: widget is not PtWindow."));
}


Window::Window(int abn):
	Disjoint(abn),
	resource(this),
	//callbacks:
	Closing(this),
    Opening(this)
{
	check();
}

Window::Window(PtWidget_t *wdg):
	Disjoint(wdg),
	resource(this),
	//callbacks:
	Closing(this),
    Opening(this)
{
	check();
}

Window::Window(const Window & rhs):
	Disjoint(rhs),
	resource(this),
	//callbacks:
	Closing(this),
    Opening(this)
{
}

Window &Window::operator=(const Window &rhs)
{
	static_cast<Disjoint&>(*this) = static_cast<const Disjoint&>(rhs);
	
	return *this;
}


