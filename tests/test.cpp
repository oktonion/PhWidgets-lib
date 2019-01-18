#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "./doctest/doctest.h"

#include <Widget.h>
#include <photon/PtWindow.h>

#include <vector>

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


TEST_CASE("Testing Widget"){
    REQUIRE_MESSAGE(-1 != PtInit(NULL), "Photon App failed to init.");
    
    PtWidget_t *ptwidget_ptr = PtCreateWidget(PtWindow, Pt_NO_PARENT, 0, NULL);
    PhWidgets::Widget *widget_ptr = nullptr;

    REQUIRE((ptwidget_ptr != nullptr));

    SUBCASE("Creating Widget") {
        CHECK_NOTHROW_MESSAGE((widget_ptr = new PhWidgets::Widget(ptwidget_ptr)), "Constructor of Widget from PtWidget_t failed");
    }

    REQUIRE((widget_ptr != nullptr));

    PhWidgets::Widget &widget = *widget_ptr;

    SUBCASE("Widget properties") {
        CHECK(widget.Height == 0);
    }
}