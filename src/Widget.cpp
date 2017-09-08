#include <map>
#include <string>
#include <set>
#include <vector>

#include <Ap.h>

#include "Widget.h"

#include "./service/PhWidgetsFunc.h"
#include "./service/mystd/my_exception.h"
#include "./service/PhWidgetsTypes.h"


#include <iostream>


using namespace PhWidgets;

std::map<PtWidget_t*, int> &ABW()
{
	static std::map<PtWidget_t*, int> widgets;
	
	return widgets;
}

std::vector< std::set<PtWidget_t*> > &ABN()
{
	static std::vector< std::set<PtWidget_t*> > widgets(GetABWCount());
	
	return widgets;
}

std::set<PtWidget_t*> &ValidWidgets()
{
	static std::set<PtWidget_t*> valid_w;
	
	return valid_w;
}

int RemoveValidWidget(PtWidget_t *wdg, void *, PtCallbackInfo_t *)
{
	ValidWidgets().erase(wdg);
	
	return (Pt_CONTINUE);
}

void AddDestroyedLink(PtWidget_t *wdg, int(*callback)( PtWidget_t *, void *, PtCallbackInfo_t * ))
{
	PtAddCallback(wdg, Widget::Callbacks::destroyed, callback, nullptr);
}

PtWidget_t *Widget::widget() const
{
	if(-1 == _abn)
	{
		PtWidget_t *instance = ApGetInstance(_widget);
		if(nullptr == instance)
			throw(std::mystd::exception("Widget::widget: invalid widget pointer"));
		return ApGetWidgetPtr(instance, ApName(_widget));
	}

	static std::map<PtWidget_t*, int> &abws = ABW();
	static std::vector< std::set<PtWidget_t*> > &abns = ABN();
	
	PtWidget_t *wdg = GetABW(_abn);

	if(nullptr == wdg || _widget != wdg)
	{
		if(nullptr != _widget && ValidWidgets().end() != ValidWidgets().find(_widget))
		{
			PtWidget_t *instance = ApGetInstance(_widget);
				
			if(nullptr != instance)
			{
				int ap_name = ApName(_widget);
				
				if(-1 != ap_name)
				{
					wdg = ApGetWidgetPtr(instance, ap_name);
				}
				else
				{
					wdg = ApGetWidgetPtr(instance, _abn);
				}
			}
		}

		if(nullptr == wdg)
		{
			throw(std::mystd::exception((std::string("Widget::widget: can not find widget with ABN ") + std::to_string(_abn)).c_str()));
		}
	}
	
	
	_widget = wdg;
	
	abns[_abn].insert(wdg);
	abws[wdg] = _abn;
	
	if(ValidWidgets().end() == ValidWidgets().find(_widget))
	{
		ValidWidgets().insert(_widget);
	
		AddDestroyedLink(_widget, &RemoveValidWidget);
	}

	return wdg;
}

void Widget::check()
{
	if(PtWidgetIsClassMember( widget(), PtWidget ) != true)
		throw(std::mystd::exception("Widget: widget is not PtWidget."));
}


Widget::Widget(int abn):
	_abn(abn),
	_widget(nullptr),
	resource(this),
	//properties:
	Enabled(this),
	Width(this),
	Height(this),
	Size(this),
	BevelWidth(this),
	HelpTopic(this),
	Location(this),
	//callbacks:
	Destroyed(this),
	Blocked(this),
	DragDrop(this),
	IsDestroyed(this),
	Outbound(this),
	Realized(this),
	Unrealized(this)

{
	if(abn < 0)
		throw(std::mystd::exception("Widget::Widget: invalid ABN is passed"));
	check();
}

Widget::Widget(PtWidget_t* wdg):
	_abn(-1), 
	_widget(wdg),
	resource(this),
	//properties:
	Enabled(this),
	Width(this),
	Height(this),
	Size(this),
	BevelWidth(this),
	HelpTopic(this),
	Location(this),
	//callbacks:
	Destroyed(this),
	Blocked(this),
	DragDrop(this),
	IsDestroyed(this),
	Outbound(this),
	Realized(this),
	Unrealized(this)

{
	if(nullptr == wdg)
		throw(std::mystd::exception("Widget::Widget: nullptr passed"));

	static std::map<PtWidget_t*, int> &abws = ABW();
	static std::vector< std::set<PtWidget_t*> > &abns = ABN();
	
	std::map<PtWidget_t*, int>::iterator it = abws.find(wdg);
	
	if(it != abws.end())
	{
		_abn = it->second;
	}
	else
	{
		std::vector<PtWidget_t*> widgets = GetABW();
		
		abws.clear();
			
		for(size_t i = 0; i < widgets.size(); ++i)
		{
			if(wdg == widgets[i])
				_abn = i;
				
			abws[widgets[i]] = i;
			abns[i].insert(widgets[i]);
		}
	}

	if(-1 == _abn)
	{
		_abn = ApName(_widget);
	}
	
	if(ValidWidgets().end() == ValidWidgets().find(_widget))
	{
		ValidWidgets().insert(_widget);
	
		AddDestroyedLink(_widget, &RemoveValidWidget);
	}

}

Widget::Widget(const Widget &rhs):
	_abn(ApName(rhs.widget())),
	_widget(nullptr),
	resource(this),
	//properties:
	Enabled(this),
	Width(this),
	Height(this),
	Size(this),
	BevelWidth(this),
	HelpTopic(this),
	Location(this),
	//callbacks:
	Destroyed(this),
	Blocked(this),
	DragDrop(this),
	IsDestroyed(this),
	Outbound(this),
	Realized(this),
	Unrealized(this)
{
}

Widget &Widget::operator=(const Widget &rhs)
{
	if(&rhs != this)
	{	
		_abn = ApName(rhs.widget());
		_widget = nullptr;
	}
	
	return *this;
}

bool Widget::operator==(const Widget &rhs)
{
	if(&rhs == this)
		return true;
	
	return widget() == rhs.widget();
}

bool Widget::operator<(const Widget &rhs)
{
	if(&rhs == this)
		return false;
	
	return std::less<PtWidget_t*>()(widget(), rhs.widget());
}






Widget::operator const PtWidget_t*() const
{
	return widget();
}

void Widget::onEvent(PtCallbackList_t *cl, PtCallbackInfo_t * info)
{

	if (nullptr == cl)
		return;

	PtWidget_t *w = widget();

	PtInvokeCallbackList(cl, w, info);
}

void Widget::OnDestroyed( PtCallbackInfo_t * info)
{
	onEvent( resource.callback[Callback::destroyed].get(), info);
}

void PhWidgets::Widget::OnBlocked( PtCallbackInfo_t * info)
{
	onEvent(resource.callback[Callback::blocked].get(), info);
}

void PhWidgets::Widget::OnDragDrop( PtCallbackInfo_t * info)
{
	onEvent(resource.callback[Callback::dnd].get(), info);
}

void PhWidgets::Widget::OnOutbound( PtCallbackInfo_t * info)
{
	onEvent(resource.callback[Callback::outbound].get(), info);
}

void PhWidgets::Widget::OnRealized( PtCallbackInfo_t * info)
{
	onEvent(resource.callback[Callback::realized].get(), info);
}

void PhWidgets::Widget::OnUnrealized( PtCallbackInfo_t * info)
{
	onEvent(resource.callback[Callback::unrealized].get(), info);
}

//for properties:
void Widget::setEnabled(bool val)
{
	resource.argument[Arguments::flags].set(Pt_BLOCKED | Pt_GHOST, !val);
}

bool Widget::getEnabled() const
{
	return resource.argument[Arguments::flags].get(Pt_BLOCKED);
}

void Widget::setWidth(unsigned short val)
{
	resource.argument[Arguments::width].set(val);
}

unsigned short Widget::getWidth() const
{
	return resource.argument[Arguments::width].get();
}

void Widget::setHeight(unsigned short val)
{
	resource.argument[Arguments::height].set(val);
}

unsigned short Widget::getHeight() const
{
	return resource.argument[Arguments::height].get();
}

void Widget::setDim(PhDim_t val)
{
	resource.argument[Arguments::dim].set(val);
}

PhDim_t Widget::getDim() const
{
	return resource.argument[Arguments::dim].get();
}

void Widget::setBevelWidth(unsigned short val)
{
	resource.argument[Arguments::bevel_width].set(val);
}

unsigned short Widget::getBevelWidth() const
{
	return resource.argument[Arguments::bevel_width].get();
}

void Widget::setHelpTopic(std::string val)
{
	resource.argument[Arguments::help_topic].set(val.c_str());
}

std::string Widget::getHelpTopic() const
{
	return resource.argument[Arguments::help_topic].get();
}

void Widget::setLocation(PhPoint_t val)
{
	resource.argument[Arguments::pos].set(val);
}


PhPoint_t Widget::getLocation() const
{
	return resource.argument[Arguments::pos].get();
}



Widget::operator PtWidget_t*()
{
	return widget();
}