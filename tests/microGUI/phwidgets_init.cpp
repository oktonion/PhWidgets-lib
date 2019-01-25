#ifndef PHWIDGETS_INIT_TEST
#define PHWIDGETS_INIT_TEST

#include "testsuit.h"

#include <Pt.h>

#include <vector>

#include <Widget.h>

namespace PhWidgets
{
	PtWidget_t* GetABW(int n)
	{
	    return 0;
	}

	std::vector<PtWidget_t*> GetABW()
	{
        std::vector<PtWidget_t*> tmp;
		return tmp;
	}

	std::size_t GetABWCount()
	{
		return 0;
	}
}

static const int PhWidgetsPtInit = PtInit(NULL);

TEST_CASE("Testing photon microGUI library initialization"){

    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");

	PtWidget_t *ptwidget_ptr = PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);

    REQUIRE(ptwidget_ptr);

    CHECK_NOTHROW_MESSAGE(PhWidgets::Widget w(ptwidget_ptr), "Constructor of Widget from PtWidget_t failed");
}

#endif // PHWIDGETS_INIT_TEST