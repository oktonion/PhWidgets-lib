#include <map>
#include <string>
#include <set>
#include <vector>

#include <Ap.h>
#include <photon/PtWindow.h>

#include "Widget.h"

#include "./service/PhWidgetsFunc.h"
#include "./service/PhWidgetsTypes.h"


#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <utility>


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
			throw(std::invalid_argument("Widget::widget: invalid widget pointer"));
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
			throw(std::invalid_argument((std::string("Widget::widget: can not find widget with ABN ") + std::to_string(_abn)).c_str()));
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
		throw(std::invalid_argument("Widget: widget is not PtWidget."));
}


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
	Enabled(this),
	Focused(this),
	HasChildren(this),
	Height(this),
	HelpTopic(this),
	IsRealized(this),
	Left(this),
	Location(this),
	Position(this),
	Right(this),
	Size(this),
	Tag(this),
	Top(this),
	Visible(this),
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
		throw(std::invalid_argument("Widget::Widget: invalid ABN is passed"));
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
	Enabled(this),
	Focused(this),
	HasChildren(this),
	Height(this),
	HelpTopic(this),
	IsRealized(this),
	Left(this),
	Location(this),
	Position(this),
	Right(this),
	Size(this),
	Tag(this),
	Top(this),
	Visible(this),
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
		throw(std::invalid_argument("Widget::Widget: nullptr passed"));

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
	Enabled(this),
	Focused(this),
	HasChildren(this),
	Height(this),
	HelpTopic(this),
	IsRealized(this),
	Left(this),
	Location(this),
	Position(this),
	Right(this),
	Size(this),
	Tag(this),
	Top(this),
	Visible(this),
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
	
	return std::less<PtWidget_t*>()(widget(), other.widget());
}

bool Widget::operator<=(const Widget &other) const
{
	if(&other == this)
		return true;
	
	return std::less_equal<PtWidget_t*>()(widget(), other.widget());
}

bool Widget::operator>(const Widget &other) const
{
	if(&other == this)
		return false;
	
	return std::greater<PtWidget_t*>()(widget(), other.widget());
}

bool Widget::operator>=(const Widget &other) const
{
	if(&other == this)
		return true;
	
	return std::greater_equal<PtWidget_t*>()(widget(), other.widget());
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
	Unrealize(); // TODO::redone to move widget
}

void Widget::Show()
{
	Realize(); // TODO::redone to move widget
}

//for properties:
void Widget::setAllowDrop(bool val)
{
	resource.argument[Arguments::flags].set(Flags::Selectable, val);
}

bool Widget::getAllowDrop() const
{
	return resource.argument[Arguments::flags].get(Flags::Selectable);
}

void Widget::setEnabled(bool val)
{
	if(resource.argument[Arguments::flags].set(Flags::Blocked | Flags::Ghost, !val) != 0)
		throw(std::invalid_argument("Widget::setEnabled: Can not set flags of a widget."));
}

bool Widget::getEnabled() const
{
	return resource.argument[Arguments::flags].get(Flags::Blocked) == false;
}

void PhWidgets::Widget::setHelpTopic(std::string val)
{
	resource.argument[Arguments::help_topic].set(val.c_str());
}

std::string PhWidgets::Widget::getHelpTopic() const
{
	return resource.argument[Arguments::help_topic].get();
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

void PhWidgets::Widget::setCursor(PhWidgets::CursorDef cursor)
{
	if(cursor._def)
	{
		resource.argument[Arguments::cursor_type].set(Flags::Cursor::bitmap);	

		resource.argument[Arguments::bitmap_cursor].set(*cursor._def);
		return;
	}

	resource.argument[Arguments::cursor_type].set(cursor._cursor);
}	

PhWidgets::CursorDef PhWidgets::Widget::getCursor() const
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
		disabled = resource.argument[Arguments::flags].get(Flags::Blocked),
		obscured = resource.argument[Arguments::flags].get(Flags::Obscured),
		gets_focus = resource.argument[Arguments::flags].get(Flags::GetsFocus);

	return !(disabled || obscured) && gets_focus;
}

bool Widget::getCanSelect() const
{
	bool 
		disabled = resource.argument[Arguments::flags].get(Flags::Blocked),
		obscured = resource.argument[Arguments::flags].get(Flags::Obscured),
		highlighted = resource.argument[Arguments::flags].get(Flags::Highlighted),
		selectable = resource.argument[Arguments::flags].get(Flags::Selectable),
		has_parent = (PtWidgetParent(widget()) != nullptr);
		//autohighlight = resource.argument[Arguments::flags].get(Flags::Autohighlight);

	return (!disabled && !obscured && highlighted && has_parent && selectable);
}

bool Widget::getContainsFocus() const
{
	return PtIsFocused( widget() ) != 0;
}

bool Widget::getFocused() const
{
	return PtIsFocused( widget() ) == 2;
}

bool Widget::hasChildren() const
{
	return (PtWidgetChildFront(widget()) != NULL);
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

PhWidgets::typedefs::anchor_flags_bitmask operator|(const PhWidgets::Widget::Flags::Anchor::eAnchorFlags & flag1, const PhWidgets::Widget::Flags::Anchor::eAnchorFlags & flag2)
{
	PhWidgets::typedefs::anchor_flags_bitmask bm(flag1);
	return bm | flag2;
}

PhWidgets::typedefs::anchor_flags_bitmask operator&(const PhWidgets::Widget::Flags::Anchor::eAnchorFlags & flag1, const PhWidgets::Widget::Flags::Anchor::eAnchorFlags & flag2)
{
	PhWidgets::typedefs::anchor_flags_bitmask bm(flag1);
	return bm & flag2;
}

PhWidgets::typedefs::anchor_flags_bitmask operator^(const PhWidgets::Widget::Flags::Anchor::eAnchorFlags & flag1, const PhWidgets::Widget::Flags::Anchor::eAnchorFlags & flag2)
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
