#include "Container.h"

#include <stdexcept>
#include <algorithm>


using namespace PhWidgets;

namespace PhWidgets
{
    const char * WidgetClassName(PtWidget_t *wdg);
}

#define FORM_THROW_MESSAGE(xxx) (std::string("PhWidgets::") + std::string(#xxx": wrong class of photon widget - got \'") + WidgetClassName(widget()) + "\' instead of \'Pt"#xxx"\'").c_str()
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
	//properties:
	ActiveWidget(this),
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
	//properties:
	ActiveWidget(this),
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
	//properties:
	ActiveWidget(this),
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

namespace
{
	struct predicate
	{
		bool operator()(const Widget &widget) const
		{
			return widget.Focused;
		}
	};
}


Widget Container::getActiveWidget() const
{
	typedef std::set<Widget>::const_iterator const_iterator;

	std::set<Widget> widgets = Widgets;

	const_iterator it = std::find_if(widgets.begin(), widgets.end(), predicate());

	if(it == widgets.end())
		return *this;

	return *it;
}

void Container::setActiveWidget(Widget widget)
{
	typedef std::set<Widget>::iterator iterator;

	std::set<Widget> widgets = Widgets;

	iterator it = widgets.find(widget);

	if(it == widgets.end())
		throw(std::invalid_argument("PhWidgets::Containter::ActiveWidget: cannot set widget passed as active"));
	
	Widget &result = const_cast<Widget&>(*it);

	result.Select();
}


