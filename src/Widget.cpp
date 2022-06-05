#include <map>
#include <string>
#include <set>
#include <vector>

#include <Ap.h>
#include <photon/PtWindow.h>

#include "Widget.h"

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <utility>
#include <cassert>

namespace PhWidgets
{
    const char * WidgetClassName(PtWidget_t *wdg);
	const char * WidgetName(PtWidget_t *wdg);

	namespace internal
	{
		struct enable_ABW;

		template<class T>
		PtWidget_t* GetABW_n(int n)
		{
			return 0;
		}

		template<class T>
		std::vector<PtWidget_t*> GetABW()
		{
			return std::vector<PtWidget_t*>();
		}

		template<class T>
		std::size_t GetABWCount()
		{
			return 0;
		}

		typedef PtWidget_t* (*GetABW_n_impl_type)(int);
		typedef std::vector<PtWidget_t*>  (*GetABW_impl_type)();
		typedef std::size_t (*GetABWCount_impl_type)();


		GetABW_n_impl_type &GetABW_n_impl() {
			static GetABW_n_impl_type value = 0;
			return value;
		}
		GetABW_impl_type &GetABW_impl() {
			static GetABW_impl_type value = 0;
			return value;
		}
		GetABWCount_impl_type &GetABWCount_impl() {
			static GetABWCount_impl_type value = 0;
			return value;
		}
	}

	PtWidget_t* GetABW(int n)
	{
		if (internal::GetABW_n_impl())
			return internal::GetABW_n_impl()(n);
		return internal::GetABW_n<internal::enable_ABW>(n);
	}

	std::vector<PtWidget_t*> GetABW()
	{
		if (internal::GetABW_impl())
			return internal::GetABW_impl()();
		return internal::GetABW<internal::enable_ABW>();
	}

	std::size_t GetABWCount()
	{
		if (internal::GetABWCount_impl())
			return internal::GetABWCount_impl()();
		return internal::GetABWCount<internal::enable_ABW>();
	}
};

using namespace PhWidgets;

static std::map<PtWidget_t*, int> &ABW()
{
	static std::map<PtWidget_t*, int> widgets;
	
	return widgets;
}

static std::vector< std::set<PtWidget_t*> > &ABN()
{
	static std::vector< std::set<PtWidget_t*> > widgets(PhWidgets::GetABWCount());
	
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
	PtAddCallback(wdg, Widget::Callbacks<>::Destroyed, callback, nullptr);
}

PtWidget_t *Widget::widget() const
{
	if(-1 == _abn)
	{
		PtWidget_t *instance = ApGetInstance(_widget);
		if(nullptr == instance)
			throw(
				std::logic_error("PhWidgets::Widget::widget(): invalid widget pointer."));
		int abn = ApName(_widget);
		if(-1 != abn)
			return ApGetWidgetPtr(instance, abn);
		else if(ValidWidgets().end() != ValidWidgets().find(_widget))
		{
			return _widget;
		}
		
	}

	static std::map<PtWidget_t*, int> &abws = ABW();
	static std::vector< std::set<PtWidget_t*> > &abns = ABN();
	
	PtWidget_t *wdg = PhWidgets::GetABW(_abn);

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
			throw(
				std::logic_error(std::string("PhWidgets::Widget::widget(): can not find widget with ABN ") + std::to_string(_abn) + "."));
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

#define FORM_THROW_MESSAGE(xxx) (std::string("PhWidgets::") + std::string(#xxx": wrong class of photon widget - got \'") + WidgetClassName(widget()) + "\' instead of \'Pt"#xxx"\'.").c_str()
#define WIDGET_IS_CLASS_MEMBER(xxx) \
	if(PtWidgetIsClassMember( widget(), Pt##xxx ) != true)\
		throw(std::invalid_argument(FORM_THROW_MESSAGE(xxx)));

#define CHECK_WIDGET(xxx) \
void xxx::check() \
{ \
	WIDGET_IS_CLASS_MEMBER(xxx); \
}

CHECK_WIDGET(Widget);


Widget::Widget(int abn):
	_abn(abn),
	_widget(nullptr),
	resource(this),
	//properties:
	AllowDrop(this),
	Anchor(this), // flag
	BevelWidth(this),
	Bottom(this),
	Bounds(this),
	CanFocus(this),
	CanSelect(this),
	ContainsFocus(this),
	Cursor(this),
	CursorColor(this),
	Enabled(this),
	Focused(this),
	HasChildren(this),
	HasParent(this),
	Height(this),
	HelpTopic(this),
	IsRealized(this),
	Left(this),
	Location(this),
	Parent(this),
	Position(this),
	Right(this),
	Size(this),
	Tag(this),
	Top(this),
	Visible(this),
	Widgets(this),
	Width(this),
	//flags:
	ExtendedFlags(this),
	WidgetFlags(this),
	ResizeFlags(this),
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
		throw(std::invalid_argument("PhWidgets::Widget::Widget: invalid ABN is passed."));
	check();
}

Widget::Widget(PtWidget_t* wdg):
	_abn(-1), 
	_widget(wdg),
	resource(this),
	//properties:
	AllowDrop(this),
	Anchor(this), // flag
	BevelWidth(this),
	Bottom(this),
	Bounds(this),
	CanFocus(this),
	CanSelect(this),
	ContainsFocus(this),
	Cursor(this),
	CursorColor(this),
	Enabled(this),
	Focused(this),
	HasChildren(this),
	HasParent(this),
	Height(this),
	HelpTopic(this),
	IsRealized(this),
	Left(this),
	Location(this),
	Parent(this),
	Position(this),
	Right(this),
	Size(this),
	Tag(this),
	Top(this),
	Visible(this),
	Widgets(this),
	Width(this),
	//flags:
	ExtendedFlags(this),
	WidgetFlags(this),
	ResizeFlags(this),
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
		throw(std::invalid_argument("PhWidgets::Widget::Widget: nullptr passed."));

	static std::map<PtWidget_t*, int> &abws = ABW();
	static std::vector< std::set<PtWidget_t*> > &abns = ABN();
	
	std::map<PtWidget_t*, int>::iterator it = abws.find(wdg);
	
	if(it != abws.end())
	{
		_abn = it->second;
	}
	else
	{
		std::vector<PtWidget_t*> widgets = PhWidgets::GetABW();
		
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

Widget::Widget(const Widget &other):
	_abn(other._abn),
	_widget(other._widget),
	resource(this),
	//properties:
	AllowDrop(this),
	Anchor(this), // flag
	BevelWidth(this),
	Bottom(this),
	Bounds(this),
	CanFocus(this),
	CanSelect(this),
	ContainsFocus(this),
	Cursor(this),
	CursorColor(this),
	Enabled(this),
	Focused(this),
	HasChildren(this),
	HasParent(this),
	Height(this),
	HelpTopic(this),
	IsRealized(this),
	Left(this),
	Location(this),
	Parent(this),
	Position(this),
	Right(this),
	Size(this),
	Tag(this),
	Top(this),
	Visible(this),
	Widgets(this),
	Width(this),
	//flags:
	ExtendedFlags(this),
	WidgetFlags(this),
	ResizeFlags(this),
	
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

void Widget::swap(Widget &other)
{
	if(&other == this)
		return;

	using std::swap;

	swap(_abn, other._abn);
	swap(_widget, other._widget);
}

Widget &Widget::operator=(const Widget &other)
{
	if(&other != this)
	{	
		_abn = other._abn;
		_widget = other._widget;
	}
	
	return *this;
}

Widget &Widget::operator=(PtWidget_t *wdg)
{
	Widget tmp(wdg);

	tmp.swap(*this);
	
	return *this;
}

bool Widget::operator==(const Widget &other) const
{
	if(&other == this)
		return true;
	
	return widget() == other.widget();
}

bool Widget::operator!=(const Widget &other) const
{
	return !(*this == other);
}

bool Widget::operator<(const Widget &other) const
{
	if(&other == this)
		return false;
	
	const PtWidget_t 
		*this_widget = widget(),
		*other_widget = other.widget();
	
	if(this_widget == other_widget)
		return false;
	
	std::ptrdiff_t
		this_widget_address = this_widget - static_cast<PtWidget_t*>(nullptr),
		other_widget_address = other_widget - static_cast<PtWidget_t*>(nullptr);
	
	return std::less<std::ptrdiff_t>()(this_widget_address, other_widget_address);
}

bool Widget::operator<=(const Widget &other) const
{
	if(&other == this)
		return true;

	const PtWidget_t 
		*this_widget = widget(),
		*other_widget = other.widget();
	
	if(this_widget == other_widget)
		return true;
	
	std::ptrdiff_t
		this_widget_address = this_widget - static_cast<PtWidget_t*>(nullptr),
		other_widget_address = other_widget - static_cast<PtWidget_t*>(nullptr);
	
	return std::less_equal<std::ptrdiff_t>()(this_widget_address, other_widget_address);
}

bool Widget::operator>(const Widget &other) const
{
	if(&other == this)
		return false;

	const PtWidget_t 
		*this_widget = widget(),
		*other_widget = other.widget();
	
	if(this_widget == other_widget)
		return false;
	
	std::ptrdiff_t
		this_widget_address = this_widget - static_cast<PtWidget_t*>(nullptr),
		other_widget_address = other_widget - static_cast<PtWidget_t*>(nullptr);

	return std::greater<std::ptrdiff_t>()(this_widget_address, other_widget_address);
}

bool Widget::operator>=(const Widget &other) const
{
	if(&other == this)
		return true;

	const PtWidget_t 
		*this_widget = widget(),
		*other_widget = other.widget();
	
	if(this_widget == other_widget)
		return true;
	
	std::ptrdiff_t
		this_widget_address = this_widget - static_cast<PtWidget_t*>(nullptr),
		other_widget_address = other_widget - static_cast<PtWidget_t*>(nullptr);
	
	return std::greater_equal<std::ptrdiff_t>()(this_widget_address, other_widget_address);
}

PtWidget_t* Widget::get() const
{
	return widget();
}

Widget::operator PtWidget_t*()
{
	return widget();
}

Widget::operator const PtWidget_t*() const
{
	return widget();
}

void Widget::OnDestroyed( PtCallbackInfo_t * info)
{
	resource.callback[Callback::destroyed].raise(info);
}

void PhWidgets::Widget::OnBlocked( PtCallbackInfo_t * info)
{
	resource.callback[Callback::blocked].raise(info);
}

void PhWidgets::Widget::OnDragDrop( PtCallbackInfo_t * info)
{
	resource.callback[Callback::dnd].raise(info);
}

void PhWidgets::Widget::OnOutbound( PtCallbackInfo_t * info)
{
	resource.callback[Callback::outbound].raise(info);
}

void PhWidgets::Widget::OnRealized( PtCallbackInfo_t * info)
{
	resource.callback[Callback::realized].raise(info);
}

void PhWidgets::Widget::OnUnrealized( PtCallbackInfo_t * info)
{
	resource.callback[Callback::unrealized].raise(info);
}

void Widget::BringToFront()
{
	PtWidgetToFront(widget());
}

bool Widget::Contains(const Widget &widget)
{
	PtWidget_t *this_widget = this->widget();

	if(false == PtIsContainer(this_widget))
		return false;
	
	PtWidget_t *front = PtWidgetChildFront(this_widget);

	if(NULL == front)
		return false;
	
	PtWidget_t *other_widget = widget.widget();

	for(PtWidget_t *next = front; next != NULL; next = PtWidgetBrotherBehind(next))
	{
		if(next == other_widget)
			return true;
	}

	return false;
}

void Widget::SetBounds(short x, short y, unsigned short width, unsigned short height)
{
	PhDim_t size;

	size.w = width;
	size.h = height;

	SetBounds(x, y);
	resource.argument[Arguments::dim].set(size);
}

void Widget::SetBounds(short x, short y)
{
	PhPoint_t position;

	position.x = x;
	position.y = y;

	setLocation(position);
}

bool Widget::Focus()
{
	if(PtWidgetIsClassMember(widget(), PtWindow) == true)
		return PtWindowFocus(widget()) == 0;

	return PtGiveFocus(widget(), nullptr) != nullptr;
}

Widget Widget::GetNextWidget(const Widget &widget, bool forward) const
{
	PtWidget_t *this_widget = this->widget();

	PtWidget_t *result = 
		forward ? 
			PtWidgetBrotherInFront(this_widget):
			PtWidgetBrotherBehind(this_widget);
	
	if(NULL == result)
	{
		result = 
		forward ? 
			PtWidgetBrotherBehind(this_widget):
			PtWidgetBrotherInFront(this_widget);
	}

	if(NULL == result)
		return *this;

	return Widget(result);
}

void Widget::Invalidate(PhRect_t rc, bool invalidateChildren)
{
	PtWidget_t *this_widget = this->widget();

	PtDamageExtent(this_widget, &rc);

	if(invalidateChildren)
	{
		PtWidget_t *front = PtWidgetChildFront(this_widget);

		if(NULL == front)
			return;
		
		for(PtWidget_t *next = front; next != NULL; next = PtWidgetBrotherBehind(next))
		{
			PtDamageExtent(next, &rc);
		}
	}
}

void Widget::Invalidate(bool invalidateChildren)
{
	PtWidget_t *this_widget = this->widget();

	PtDamageWidget(this_widget);

	if(invalidateChildren)
	{
		PtWidget_t *front = PtWidgetChildFront(this_widget);

		if(NULL == front)
			return;
		
		for(PtWidget_t *next = front; next != NULL; next = PtWidgetBrotherBehind(next))
		{
			PtDamageWidget(next);
		}
	}
}

void Widget::Refresh()
{
	Invalidate(true);
	Update();
}

void Widget::SendToBack()
{
	PtWidgetToBack(widget());
}

void Widget::Select()
{
	Focus(); // TODO: check the actual difference
}

bool Widget::Realize()
{
	return PtRealizeWidget( widget() ) == 0;
}

bool Widget::Unrealize()
{
	return PtUnrealizeWidget( widget() ) == 0;
}

void Widget::Hide()
{
	PtWidget_t *ptr = widget();
	if (PtWidgetIsClassMember(ptr, PtWindow))
	{
		struct lambdas
		{
			static int PtWindowHide( PtWidget_t *widget )
			{
				PhWindowEvent_t WE;
				using namespace std;

				memset( &WE, 0, sizeof (WE));
				WE.event_f = Ph_WM_HIDE;
				WE.rid     = PtWidgetRid( widget );
				WE.event_state =  Ph_WM_EVSTATE_HIDE;
				return PtForwardWindowEvent( &WE );
			}
		};

		int err = lambdas::PtWindowHide(ptr);

		(void)(err);

		return;
	}
	Unrealize(); // TODO::redone to move widget
}

void Widget::Show()
{
	PtWidget_t *ptr = widget();
	if (PtWidgetIsClassMember(ptr, PtWindow))
	{
		struct lambdas
		{
			static int PtWindowShow( PtWidget_t *widget )
			{
				PhWindowEvent_t WE;
				using namespace std;

				memset( &WE, 0, sizeof (WE));
				WE.event_f = Ph_WM_RESTORE;
				WE.rid     = PtWidgetRid( widget );
				WE.event_state =  Ph_WM_EVSTATE_UNHIDE;
				return PtForwardWindowEvent( &WE );
			}
		};

		int err = lambdas::PtWindowShow(ptr);

		(void)(err);

		return;
	}

	Realize(); // TODO::redone to move widget
}

void Widget::Update()
{
	PtFlush();
}

//for properties:
void Widget::setAllowDrop(bool val)
{
	resource.argument[Arguments::flags].set(Flags::Selectable, val);
}

bool Widget::getAllowDrop() const
{
	bool 
		realized = resource.argument[Arguments::flags].get(Flags::Realized),
		selectable = resource.argument[Arguments::flags].get(Flags::Selectable);
	return (realized && selectable);
}

void Widget::setEnabled(bool val)
{
	if(resource.argument[Arguments::flags].set(Flags::Blocked | Flags::Ghost, !val) != 0)
		throw(
			std::invalid_argument(std::string("PhWidets::Widget::Enabled: \'") + WidgetClassName(widget()) + "\' - cannot set flags of a widget."));
}

bool Widget::getEnabled() const
{
	bool
	    realized = resource.argument[Arguments::flags].get(Flags::Realized),
		blocked = resource.argument[Arguments::flags].get(Flags::Blocked);

	return (realized && !blocked);
}

void PhWidgets::Widget::setHelpTopic(std::string val)
{
	resource.argument[Arguments::help_topic].set(val.c_str());
}

std::string PhWidgets::Widget::getHelpTopic() const
{
	const char *help_topic =
		resource.argument[Arguments::help_topic].get();
	if (help_topic) return help_topic;
	return "";
}

void PhWidgets::Widget::setLocation(PhPoint_t location)
{
	PhPoint_t offset, position;

	if (PtWidgetOffset(this->widget(), &offset))
	{
		position.x = location.x - offset.x;
		position.y = location.y - offset.y;

		resource.argument[Arguments::pos].set(position);
	}

}

PhPoint_t PhWidgets::Widget::getLocation() const
{
	PhPoint_t offset, position, location;
	location.x = 0;
	location.y = 0;

	if (PtWidgetOffset(this->widget(), &offset))
	{
		position = resource.argument[Arguments::pos].get();

		location.x = position.x + offset.x;
		location.y = position.y + offset.y;
	}

	return location;
}

void PhWidgets::Widget::setBounds(PhArea_t bounds)
{
	setLocation(bounds.pos);
	resource.argument[Arguments::dim].set(bounds.size);
}

PhArea_t PhWidgets::Widget::getBounds() const
{
	PhArea_t bounds;

	bounds.pos = getLocation();
	bounds.size = resource.argument[Arguments::dim].get();

	return bounds;
}

short PhWidgets::Widget::getBottom() const
{
	return getLocation().y + Height;
}

void PhWidgets::Widget::setCursor(PhWidgets::Cursor cursor)
{
	if(cursor._def)
	{
		resource.argument[Arguments::cursor_type].set(Flags::Cursor::bitmap);	

		resource.argument[Arguments::bitmap_cursor].set(*cursor._def);
		return;
	}

	resource.argument[Arguments::cursor_type].set(cursor._cursor);
}	

PhWidgets::Cursor PhWidgets::Widget::getCursor() const
{
	const unsigned short cursor = resource.argument[Arguments::cursor_type].get();

	if(cursor == Flags::Cursor::bitmap_no_inherit || cursor == Flags::Cursor::bitmap_inherit)
	{
		return resource.argument[Arguments::bitmap_cursor].get();
	}

	return Cursors::eCursors(cursor);
}

bool Widget::getCanFocus() const
{
	bool 
	    realized = resource.argument[Arguments::flags].get(Flags::Realized),
		disabled = resource.argument[Arguments::flags].get(Flags::Blocked),
		obscured = resource.argument[Arguments::flags].get(Flags::Obscured),
		gets_focus = resource.argument[Arguments::flags].get(Flags::GetsFocus);

	return !(disabled || obscured || !realized) && gets_focus;
}

bool Widget::getCanSelect() const
{
	bool 
	    realized = resource.argument[Arguments::flags].get(Flags::Realized),
		disabled = resource.argument[Arguments::flags].get(Flags::Blocked),
		obscured = resource.argument[Arguments::flags].get(Flags::Obscured),
		highlighted = resource.argument[Arguments::flags].get(Flags::Highlighted),
		selectable = resource.argument[Arguments::flags].get(Flags::Selectable),
		has_parent = (PtWidgetParent(widget()) != nullptr);
		//autohighlight = resource.argument[Arguments::flags].get(Flags::Autohighlight);

	return (realized && !disabled && !obscured && highlighted && has_parent && selectable);
}

bool Widget::getContainsFocus() const
{
	return PtIsFocused( widget() ) != 0;
}

bool Widget::getFocused() const
{
	PtWidget_t *ptr = widget();

	if (PtWidgetIsClassMember(ptr, PtWindow))
		return PtWindowGetState(ptr) == Ph_WM_STATE_ISFOCUS;
	return PtIsFocused( ptr ) == 2;
}

bool Widget::hasChildren() const
{
	return (PtWidgetChildFront(widget()) != NULL);
}

bool Widget::hasParent() const
{
	return Parent() != nullptr;
}

short PhWidgets::Widget::getRight() const
{
	return getLocation().x + Width;
}

void PhWidgets::Widget::setLeft(short x)
{
	PhPoint_t location = getLocation();

	if (location.x != x)
	{
		location.x = x;
		setLocation(location); 
	}
}

short PhWidgets::Widget::getLeft() const
{
	return getLocation().x;
}

void Widget::setParent(PtWidget_t *parent)
{
	if(!parent)
		parent = Pt_NO_PARENT;
	
	PtWidget_t *this_widget = widget();

	int err = PtReparentWidget(this_widget, parent);
	if(0 == err)
		return;

	// error handling

	std::string err_mesage = 
		std::string("PhWidgets::Widget::Parent: cannot set \'") +
		((Pt_NO_PARENT == parent) ? "nullptr" : WidgetName(parent)) +
		"\' as a parent for \'" + 
		WidgetName(this_widget) + 
		"\' - ";
	
	if(Pt_NO_PARENT == parent)
	{
		throw(
		std::logic_error(
			err_mesage + "\'" + WidgetClassName(this_widget) + "\' widget should have a parent."));
	}

	if(false == PtIsContainer(parent))
	{
		throw(
		std::invalid_argument(
			err_mesage + "\'" + WidgetClassName(parent) + "\' widget passed is not a container."));
	}

	throw(
	std::logic_error(
		err_mesage + "\'" + WidgetClassName(this_widget) + "\' widget couldn't be reparented."));
}

PtWidget_t * Widget::getParent() const
{

	PtWidget_t *wdg = widget();
	PtWidget_t *result = PtValidParent(wdg, PtWidgetClass(wdg));
	if(result == wdg)
		result = PtWidgetParent(wdg);

	return ( (result == Pt_NO_PARENT) ? nullptr : result );
}

void Widget::setTag(const void *tag, std::size_t size)
{
	resource.argument[Widget::Arguments::user_data].set(tag, size);
}

const void * Widget::getTag() const
{
	return resource.argument[Widget::Arguments::user_data].get();
}


void PhWidgets::Widget::setTop(short y)
{
	PhPoint_t location = getLocation();

	if (location.y != y)
	{
		location.y = y;
		setLocation(location);
	}
}

short PhWidgets::Widget::getTop() const
{
	return getLocation().y;
}

void Widget::setVisible(bool value)
{
	if(value)
		Show();
	else
		Hide();
}

bool Widget::getVisible() const
{
	if(getIsRealized())
	{
		PhPoint_t location = getLocation();

		if(location.x > (0 - Width) && location.y > (0 - Height))
			return true;
	}

	return false;
}

bool Widget::getIsRealized() const
{
	return PtWidgetIsRealized ( widget() ) != 0;
}

std::set<Widget> Widget::getWidgets() const
{
	std::set<Widget> result;
	PtWidget_t *this_widget = widget();

	PtWidget_t *front = PtWidgetChildFront(this_widget);

	if(NULL == front)
		return result;
	
	for(PtWidget_t *next = front; next != NULL; next = PtWidgetBrotherBehind(next))
	{
		result.insert(Widget(next));
	}

	return result;
}

cppbitmasks::bitmask<unsigned long, PhWidgets::Widget::Flags::Extended::eExFlags> operator|(const PhWidgets::Widget::Flags::Extended::eExFlags &flag1, const PhWidgets::Widget::Flags::Extended::eExFlags &flag2)
{
	cppbitmasks::bitmask<unsigned long, PhWidgets::Widget::Flags::Extended::eExFlags> bm(flag1);
	return bm | flag2;
}

cppbitmasks::bitmask<unsigned long, PhWidgets::Widget::Flags::Extended::eExFlags> operator&(const PhWidgets::Widget::Flags::Extended::eExFlags &flag1, const PhWidgets::Widget::Flags::Extended::eExFlags &flag2)
{
	cppbitmasks::bitmask<unsigned long, PhWidgets::Widget::Flags::Extended::eExFlags> bm(flag1);
	return bm & flag2;
}

cppbitmasks::bitmask<unsigned long, PhWidgets::Widget::Flags::Extended::eExFlags> operator^(const PhWidgets::Widget::Flags::Extended::eExFlags &flag1, const PhWidgets::Widget::Flags::Extended::eExFlags &flag2)
{
	cppbitmasks::bitmask<unsigned long, PhWidgets::Widget::Flags::Extended::eExFlags> bm(flag1);
	return bm ^ flag2;
}

cppbitmasks::bitmask<long, PhWidgets::Widget::Flags::eFlags> operator|(const PhWidgets::Widget::Flags::eFlags &flag1, const PhWidgets::Widget::Flags::eFlags &flag2)
{
	cppbitmasks::bitmask<long, PhWidgets::Widget::Flags::eFlags> bm(flag1);
	return bm | flag2;
}

cppbitmasks::bitmask<long, PhWidgets::Widget::Flags::eFlags> operator&(const PhWidgets::Widget::Flags::eFlags &flag1, const PhWidgets::Widget::Flags::eFlags &flag2)
{
	cppbitmasks::bitmask<long, PhWidgets::Widget::Flags::eFlags> bm(flag1);
	return bm & flag2;
}

cppbitmasks::bitmask<long, PhWidgets::Widget::Flags::eFlags> operator^(const PhWidgets::Widget::Flags::eFlags &flag1, const PhWidgets::Widget::Flags::eFlags &flag2)
{
	cppbitmasks::bitmask<long, PhWidgets::Widget::Flags::eFlags> bm(flag1);
	return bm ^ flag2;
}

cppbitmasks::bitmask<long, PhWidgets::Widget::Flags::Resize::eResizeFlags> operator|(const PhWidgets::Widget::Flags::Resize::eResizeFlags & flag1, const PhWidgets::Widget::Flags::Resize::eResizeFlags & flag2)
{
	cppbitmasks::bitmask<long, PhWidgets::Widget::Flags::Resize::eResizeFlags> bm(flag1);
	return bm | flag2;
}

cppbitmasks::bitmask<long, PhWidgets::Widget::Flags::Resize::eResizeFlags> operator&(const PhWidgets::Widget::Flags::Resize::eResizeFlags & flag1, const PhWidgets::Widget::Flags::Resize::eResizeFlags & flag2)
{
	cppbitmasks::bitmask<long, PhWidgets::Widget::Flags::Resize::eResizeFlags> bm(flag1);
	return bm & flag2;
}

cppbitmasks::bitmask<long, PhWidgets::Widget::Flags::Resize::eResizeFlags> operator^(const PhWidgets::Widget::Flags::Resize::eResizeFlags & flag1, const PhWidgets::Widget::Flags::Resize::eResizeFlags & flag2)
{
	cppbitmasks::bitmask<long, PhWidgets::Widget::Flags::Resize::eResizeFlags> bm(flag1);
	return bm ^ flag2;
}

PhWidgets::typedefs::anchor_flags_bitmask operator|(const PhWidgets::Widget::Flags::Anchor::eAnchorStyles & flag1, const PhWidgets::Widget::Flags::Anchor::eAnchorStyles & flag2)
{
	PhWidgets::typedefs::anchor_flags_bitmask bm(flag1);
	return bm | flag2;
}

PhWidgets::typedefs::anchor_flags_bitmask operator&(const PhWidgets::Widget::Flags::Anchor::eAnchorStyles & flag1, const PhWidgets::Widget::Flags::Anchor::eAnchorStyles & flag2)
{
	PhWidgets::typedefs::anchor_flags_bitmask bm(flag1);
	return bm & flag2;
}

PhWidgets::typedefs::anchor_flags_bitmask operator^(const PhWidgets::Widget::Flags::Anchor::eAnchorStyles & flag1, const PhWidgets::Widget::Flags::Anchor::eAnchorStyles & flag2)
{
	PhWidgets::typedefs::anchor_flags_bitmask bm(flag1);
	return bm ^ flag2;
}

bool operator==(const PhArea_t &lhs, const PhArea_t &rhs)
{
	return 0 == std::memcmp(&lhs, &rhs, sizeof(PhArea_t));
}
bool operator!=(const PhArea_t &lhs, const PhArea_t &rhs)
{
	return 0 != std::memcmp(&lhs, &rhs, sizeof(PhArea_t));
}
