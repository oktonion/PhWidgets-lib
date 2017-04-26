#include "Basic.h"
#include "./service/mystd/my_exception.h"


using namespace PhWidgets;

void Basic::check()
{
	if(PtWidgetIsClassMember( widget(), PtBasic ) != true)
		throw(std::mystd::exception("Basic: widget is not PtBasic."));
}


Basic::Basic(int abn):
	Widget(abn),
	Color(this),
	FillColor(this)
{
	check();
}

Basic::Basic(PtWidget_t *wdg):
	Widget(wdg),
	Color(this),
	FillColor(this)
{
	check();
}

Basic::Basic(const Basic &rhs):
	Widget(rhs),
	Color(this),
	FillColor(this)
{

}

void Basic::setColor(PgColor_t val)
{
	resource.argument[Arguments::color].set(val);
}

PgColor_t Basic::getColor() const
{
	return resource.argument[Arguments::color].get();
}

void Basic::setFillColor(PgColor_t val)
{
	resource.argument[Arguments::fill_color].set(val);
}

PgColor_t Basic::getFillColor() const
{
	return resource.argument[Arguments::fill_color].get();
}