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
	resource(this),
    //properties:
    DropDownStyle(this),
    DroppedDown(this)
{
	check();
}

ComboBox::ComboBox(PtWidget_t *wdg):
	Compound(wdg),
	resource(this),
    //properties:
    DropDownStyle(this),
    DroppedDown(this)
{
	check();
}

ComboBox::ComboBox(const ComboBox & other) :
	Compound(other),
	resource(this),
    //properties:
    DropDownStyle(this),
    DroppedDown(this)
{
}

ComboBox &ComboBox::operator=(const ComboBox &other)
{
	static_cast<Compound&>(*this) = static_cast<const Compound&>(other);
	
	return *this;
}

PhWidgets::ComboBoxStyle::eComboBoxStyle ComboBox::getDropDownStyle() const // TODO: BS, need to be tested and redone
{
    bool 
        is_static_list = resource.argument[Arguments::cbox_flags].get(Flags::StaticList),
        is_editable = Enabled;
    
    if(is_static_list)
        return ComboBoxStyle::Simple;
    if(is_editable)
        return ComboBoxStyle::DropDown;
    
    return ComboBoxStyle::DropDownList;
}

void ComboBox::setDropDownStyle(PhWidgets::ComboBoxStyle::eComboBoxStyle val) // TODO: BS, need to be tested and redone
{
    int result = 0;
    switch (val)
    {
    case ComboBoxStyle::Simple:
        result = resource.argument[Arguments::cbox_flags].set(Flags::StaticList, true);
        break;
    case ComboBoxStyle::DropDown:
        result = resource.argument[Arguments::cbox_flags].set(Flags::StaticList, false);
        break;
    case ComboBoxStyle::DropDownList:
        result = resource.argument[Arguments::cbox_flags].set(Flags::StaticList, false);
        break;
    default:
        break;
    }

	if(result != 0)
		throw(
			std::invalid_argument(std::string("PhWidets::ComboBox::DropDownStyle: \'") + WidgetClassName(widget()) + "\' - cannot set flags of a widget."));
}

bool ComboBox::getDroppedDown() const
{
    return resource.argument[Arguments::cbox_flags].get(Flags::IsOpened);
}

void ComboBox::setDroppedDown(bool val)
{
    if(val)
        PtComboBoxListOpen(widget());
    else
        PtComboBoxListClose(widget());
}

void ComboBox::AddItem(std::string item, unsigned int pos)
{
    const char *item_cstr = item.c_str();
    PtListAddItems(widget(), &item_cstr, 1, pos);
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