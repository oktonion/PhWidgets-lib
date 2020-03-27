#include "Text.h"

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
void TextWidget::check() \
{ \
	WIDGET_IS_CLASS_MEMBER(xxx); \
}

CHECK_WIDGET(Text);


TextWidget::TextWidget(int abn):
	Label(abn),
	resource(this),
	//callbacks:
	ModifyNotify(this),
	ModifyVerify(this),
	MotionNotify(this),
	MotionVerify(this),
	TextChanged(this)

{
	check();
}

TextWidget::TextWidget(PtWidget_t *wdg):
	Label(wdg),
	resource(this),
	//callbacks:
	ModifyNotify(this),
	ModifyVerify(this),
	MotionNotify(this),
	MotionVerify(this),
	TextChanged(this)
{
	check();
}

TextWidget::TextWidget(const TextWidget & other):
	Label(other),
	resource(this),
	//callbacks:
	ModifyNotify(this),
	ModifyVerify(this),
	MotionNotify(this),
	MotionVerify(this),
	TextChanged(this)
{
}

TextWidget &TextWidget::operator=(const TextWidget &other)
{
	static_cast<Label&>(*this) = static_cast<const Label&>(other);
	
	return *this;
}

