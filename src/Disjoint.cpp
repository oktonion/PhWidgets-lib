#include "Disjoint.h"

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

CHECK_WIDGET(Disjoint);


Disjoint::Disjoint(int abn):
	Container(abn),
	resource(this),
	//callbacks:
	SysInfo(this)
{
	check();
}

Disjoint::Disjoint(PtWidget_t *wdg):
	Container(wdg),
	resource(this),
	//callbacks:
	SysInfo(this)
{
	check();
}

Disjoint::Disjoint(const Disjoint & rhs):
	Container(rhs),
	resource(this),
	//callbacks:
	SysInfo(this)
{
}

Disjoint &Disjoint::operator=(const Disjoint &rhs)
{
	static_cast<Container&>(*this) = static_cast<const Container&>(rhs);
	
	return *this;
}


