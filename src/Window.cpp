#include "Window.h"

#include <stdexcept>


using namespace PhWidgets;

namespace PhWidgets
{
    const char * WidgetClassName(PtWidget_t *wdg);
}

#define FORM_THROW_MESSAGE(xxx) (std::string("PhWidgets::") + std::string(#xxx": wrong class of photon widget - got \'") + WidgetClassName(widget()) + "\' instead of \'Pt"#xxx"\'.").c_str()
#define WIDGET_IS_CLASS_MEMBER(xxx) \
	if(PtWidgetIsClassMember( widget(), Pt##xxx ) != true)\
		throw(std::invalid_argument(FORM_THROW_MESSAGE(xxx)));

#define CHECK_WIDGET(xxx) \
void xxx::check() \
{ \
	WIDGET_IS_CLASS_MEMBER(xxx); \
}

CHECK_WIDGET(Window);


Window::Window(int abn):
	Disjoint(abn),
	resource(this),
	//properties:
	Title(this),
	//callbacks:
	Closing(this),
    Opening(this)
{
	check();
}

Window::Window(PtWidget_t *wdg):
	Disjoint(wdg),
	resource(this),
	//properties:
	Title(this),
	//callbacks:
	Closing(this),
    Opening(this)
{
	check();
}

Window::Window(const Window & other):
	Disjoint(other),
	resource(this),
	//properties:
	Title(this),
	//callbacks:
	Closing(this),
    Opening(this)
{
}

Window &Window::operator=(const Window &other)
{
	static_cast<Disjoint&>(*this) = static_cast<const Disjoint&>(other);
	
	return *this;
}

//for properties:
void Window::setTitle(std::string value)
{
	resource.argument[Arguments::window_title].set(value.c_str());
}

std::string Window::getTitle() const
{
	const char *window_title =
		resource.argument[Arguments::window_title].get();
	
	if (window_title) return window_title;
	return "";
}


