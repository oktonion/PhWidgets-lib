#include "ComboBox.h"

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

CHECK_WIDGET(ComboBox);


ComboBox::ComboBox(int abn):
	Compound(abn),
	resource(this)
{
	check();
}

ComboBox::ComboBox(PtWidget_t *wdg):
	Compound(wdg),
	resource(this)
{
	check();
}

ComboBox::ComboBox(const ComboBox & other) :
	Compound(other),
	resource(this)
{
}

ComboBox &ComboBox::operator=(const ComboBox &other)
{
	static_cast<Compound&>(*this) = static_cast<const Compound&>(other);
	
	return *this;
}


cppbitmasks::bitmask<unsigned short, PhWidgets::ComboBox::Flags::eComboBoxFlags> operator|(const PhWidgets::ComboBox::Flags::eComboBoxFlags &flag1, const PhWidgets::ComboBox::Flags::eComboBoxFlags &flag2)
{
	cppbitmasks::bitmask<unsigned short, PhWidgets::ComboBox::Flags::eComboBoxFlags> bm(flag1);
	return bm | flag2;
}

cppbitmasks::bitmask<unsigned short, PhWidgets::ComboBox::Flags::eComboBoxFlags> operator&(const PhWidgets::ComboBox::Flags::eComboBoxFlags &flag1, const PhWidgets::ComboBox::Flags::eComboBoxFlags &flag2)
{
	cppbitmasks::bitmask<unsigned short, PhWidgets::ComboBox::Flags::eComboBoxFlags> bm(flag1);
	return bm & flag2;
}

cppbitmasks::bitmask<unsigned short, PhWidgets::ComboBox::Flags::eComboBoxFlags> operator^(const PhWidgets::ComboBox::Flags::eComboBoxFlags &flag1, const PhWidgets::ComboBox::Flags::eComboBoxFlags &flag2)
{
	cppbitmasks::bitmask<unsigned short, PhWidgets::ComboBox::Flags::eComboBoxFlags> bm(flag1);
	return bm ^ flag2;
}