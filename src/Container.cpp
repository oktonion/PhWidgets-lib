#include "Container.h"

#include <stdexcept>


using namespace PhWidgets;

namespace PhWidgets
{
    const char * WidgetClassName(PtWidget_t *wdg);
}

#define FORM_THROW_MESSAGE(xxx) (std::string(#xxx": wrong class of photon widget - got \'") + WidgetClassName(widget()) + "\' instead of \'Pt"#xxx"\'").c_str()
#define WIDGET_IS_CLASS_MEMBER(xxx) \
	if(PtWidgetIsClassMember( widget(), Pt##xxx ) != true)\
		throw(std::invalid_argument(FORM_THROW_MESSAGE(xxx)));

#define CHECK_WIDGET(xxx) \
void xxx::check() \
{ \
	WIDGET_IS_CLASS_MEMBER(xxx); \
}

CHECK_WIDGET(Container);


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

PhWidgets::Container::Container(const Container & other):
	Basic(other),
	resource(this),
	//callbacks:
	ChildAddedRemoved(this),
	ChildGettingFocus(this),
	ChildLosingFocus(this),
	LayoutChanged(this),
	Resize(this)
{
}

Container &Container::operator=(const Container &other)
{
	static_cast<Basic&>(*this) = static_cast<const Basic&>(other);
	
	return *this;
}


