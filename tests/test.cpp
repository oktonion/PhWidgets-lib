#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "./doctest/doctest.h"

#include <Pt.h>
#include <Widget.h>
#include <photon/PtWindow.h>

#include <vector>
#include <iostream>

namespace PhWidgets
{
	PtWidget_t* GetABW(int n)
	{
	    return nullptr;
	}

	std::vector<PtWidget_t*> GetABW()
	{
        std::vector<PtWidget_t*> tmp;
		return tmp;
	}

	size_t GetABWCount()
	{
		return 0;
	}
}

static const int pt_init = PtInit(NULL);

template<class PropertyT>
void property_test_subcase(PropertyT &property, const char *prop_name)
{
    typedef typename PropertyT::value_type property_value_type;
    SUBCASE(prop_name) {
        property_value_type
            v = property,
            vv = static_cast<property_value_type>(v * 1.5) + property_value_type(100);
        CHECK_MESSAGE(property == v, prop_name);
        property = vv;
        CHECK_MESSAGE(v != property, prop_name);
        CHECK_MESSAGE(vv == property, prop_name);
    }
}

#define PROPERTY_TEST_SUBCASE(prop) property_test_subcase(prop, #prop)

TEST_CASE("Testing Widget"){

    using namespace PhWidgets;

    REQUIRE_MESSAGE(0 == pt_init, "Photon App requires connection to Photon server.");
    
    PtWidget_t *ptwidget_ptr = PtCreateWidget(PtWindow, Pt_NO_PARENT, 0, NULL);
    
    REQUIRE((ptwidget_ptr != nullptr));

    SUBCASE("Creating Widget") {
        CHECK_NOTHROW_MESSAGE(Widget w(ptwidget_ptr), "Constructor of Widget from PtWidget_t failed");
    }

    SUBCASE("Testing Widget properties and arguments") {
        Widget widget(ptwidget_ptr);

        SUBCASE("Testing Widget::AllowDrop property") {
            CHECK(false == widget.AllowDrop);
            widget.AllowDrop = true;
            CHECK(true == widget.AllowDrop);
            widget.AllowDrop = false;
            CHECK(widget.AllowDrop == false);
        }

        SUBCASE("Testing Widget::Anchor property") {
            CHECK(widget.Anchor == AnchorStyles::None);
            widget.Anchor = AnchorStyles::Left;
            CHECK(widget.Anchor == AnchorStyles::Left);
            CHECK(widget.Anchor != (AnchorStyles::Left | AnchorStyles::Top));
            widget.Anchor = AnchorStyles::Bottom;
            CHECK(AnchorStyles::Bottom == widget.Anchor);
            CHECK(AnchorStyles::Left != widget.Anchor);
        }

        PROPERTY_TEST_SUBCASE(widget.Height);
        PROPERTY_TEST_SUBCASE(widget.Width);
        PROPERTY_TEST_SUBCASE(widget.Left);
        PROPERTY_TEST_SUBCASE(widget.Top);
    }

    PtDestroyWidget(ptwidget_ptr);
}