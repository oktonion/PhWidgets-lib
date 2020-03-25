#ifndef PHWIDGETS_INIT_TEST
#define PHWIDGETS_INIT_TEST

#include "testsuit.h"

#include <Pt.h>

#include <vector>

#include <Window.h>
#include <Button.h>
#include <Label.h>
#include <Text.h>
#include <ComboBox.h>

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

    REQUIRE_NOTHROW_MESSAGE(PhWidgets::Window w(ptwidget_ptr), "Constructor of Window from PtWidget_t failed");

	ptwidget_ptr = PhWidgetsCreateWidget<&PtButton>(ptwidget_ptr, 0, NULL);

    REQUIRE(ptwidget_ptr);

    REQUIRE_NOTHROW_MESSAGE(PhWidgets::Button b(ptwidget_ptr), "Constructor of Button from PtWidget_t failed");

	ptwidget_ptr = PhWidgetsCreateWidget<&PtLabel>(ptwidget_ptr, 0, NULL);

    REQUIRE(ptwidget_ptr);

    REQUIRE_NOTHROW_MESSAGE(PhWidgets::Label l(ptwidget_ptr), "Constructor of Label from PtWidget_t failed");

	ptwidget_ptr = PhWidgetsCreateWidget<&PtText>(ptwidget_ptr, 0, NULL);

    REQUIRE(ptwidget_ptr);

    REQUIRE_NOTHROW_MESSAGE(PhWidgets::Text t(ptwidget_ptr), "Constructor of Text from PtWidget_t failed");

	ptwidget_ptr = PhWidgetsCreateWidget<&PtComboBox>(ptwidget_ptr, 0, NULL);

    REQUIRE(ptwidget_ptr);

    REQUIRE_NOTHROW_MESSAGE(PhWidgets::ComboBox cb(ptwidget_ptr), "Constructor of ComboBox from PtWidget_t failed");
}

#endif // PHWIDGETS_INIT_TEST