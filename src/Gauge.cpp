#include "Gauge.h"

#include <stdexcept>
#include <cassert>

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

CHECK_WIDGET(Gauge);


Gauge::Gauge(int abn):
	Basic(abn),
	resource(this),
	//properties:
	Font(this),
    Prefix(this),
    Suffix(this),
	Value(this),
	Maximum(this),
	Minimum(this),
    GaugeFlags(this)
{
	check();
}

Gauge::Gauge(PtWidget_t *wdg):
	Basic(wdg),
	resource(this),
	//properties:
	Font(this),
    Prefix(this),
    Suffix(this),
	Value(this),
	Maximum(this),
	Minimum(this),
    GaugeFlags(this)
{
	check();
}

Gauge::Gauge(const Gauge &other):
	Basic(other),
	resource(this),
	//properties:
	Font(this),
    Prefix(this),
    Suffix(this),
	Value(this),
	Maximum(this),
	Minimum(this),
    GaugeFlags(this)
{
	
}

Gauge &Gauge::operator=(const Gauge &other)
{
	static_cast<Basic&>(*this) = static_cast<const Basic&>(other);
	
	return *this;
}


Drawing::Font Gauge::getFont() const
{
	const char *gauge_font = resource.argument[Arguments::gauge_font].get();

	FontID *fid = PfDecomposeStemToID(gauge_font);

	if(NULL == fid)
		throw(std::invalid_argument(std::string("Gauge::Font is an invalid string (\"") + gauge_font + "\")."));
	
	return fid;
}

void Gauge::setFont(Drawing::Font fdef)
{
	resource.argument[Arguments::gauge_font].set(fdef.Name.c_str());
}

std::string Gauge::getPrefix() const
{
	return resource.argument[Arguments::value_prefix].get();
}

void Gauge::setPrefix(std::string text)
{
	resource.argument[Arguments::value_prefix].set(text.c_str());
}

std::string Gauge::getSuffix() const
{
	return resource.argument[Arguments::value_suffix].get();
}

void Gauge::setSuffix(std::string text)
{
	resource.argument[Arguments::value_suffix].set(text.c_str());
}
