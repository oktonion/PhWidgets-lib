

#include "./testsuit/testsuit.h"

#include <Widget.h>
#include <Button.h>
#include <photon/PtWindow.h>
#include <photon/PtButton.h>

#ifndef PH_WIDGETS_INIT_COMPLETED
static const int PhWidgetsPtInit = PtInit(NULL);
#define PH_WIDGETS_INIT_COMPLETED
#endif

TEST_CASE("Testing swap idiom of Widget") {
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");

    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtButton>())
        PhWidgetsCreateWidget<&PtButton>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
    
    REQUIRE(PhWidgetsGetWidget<&PtWindow>());
    REQUIRE(PhWidgetsGetWidget<&PtButton>());
    
    using namespace PhWidgets;

    Widget 
        widget1(PhWidgetsGetWidget<&PtWindow>());
    Button
        widget2(PhWidgetsGetWidget<&PtButton>());

    Widget tmp = widget1;

    tmp = widget1;
    tmp = widget1.get();

    CHECK(tmp == widget1);
    CHECK(widget1 == tmp);
    CHECK(widget2 != tmp);
    CHECK(tmp != widget2);
    CHECK(widget2 != widget1);
    CHECK(widget1 != widget2);

    widget2.swap(widget1);

    CHECK(tmp != widget1);
    CHECK(widget1 != tmp);
    CHECK(widget2 == tmp);
    CHECK(tmp == widget2);
    CHECK(widget2 != widget1);
    CHECK(widget1 != widget2);
}