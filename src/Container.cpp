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
	//callbacks:
	ChildAddedRemoved(this),
	ChildGettingFocus(this),
	ChildLosingFocus(this),
	LayoutChanged(this),
	Resize(this)
{
}

void PhWidgets::Container::addChildAddedRemovedCallback(callback_t callback)
{
	resource.callback[ThisCallbacks::Callback::child_added_removed].add(callback);
}

void PhWidgets::Container::addChildGettingFocusCallback(callback_t callback)
{
	resource.callback[ThisCallbacks::Callback::child_getting_focus].add(callback);
}

void PhWidgets::Container::addChildLosingFocusCallback(callback_t callback)
{
	resource.callback[ThisCallbacks::Callback::child_losing_focus].add(callback);
}

void PhWidgets::Container::addLayoutChangedCallback(callback_t callback)
{
	resource.callback[ThisCallbacks::Callback::layout].add(callback);
}

void PhWidgets::Container::addResizeCallback(callback_t callback)
{
	resource.callback[ThisCallbacks::Callback::resize].add(callback);
}


