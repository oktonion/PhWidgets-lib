#include "./testsuit/testsuit.h"

#include <Timer.h>

#include <Drawing/Color.h>
#include <photon/PtButton.h>

#ifndef PH_WIDGETS_INIT_COMPLETED
static const int PhWidgetsPtInit = PtInit(NULL);
#define PH_WIDGETS_INIT_COMPLETED
#endif

TEST_CASE("Testing Timer::Initial property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtTimer>())
        PhWidgetsCreateWidget<&PtTimer>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtTimer>());

    using namespace PhWidgets;
    
    Timer timer(PhWidgetsGetWidget<&PtTimer>());

    timer.Initial = 14;
    
    CHECK(timer.Initial == 14);
    CHECK(14 == timer.Initial);

    timer.Initial = 12;

    CHECK(timer.Initial == 12);
    CHECK(12 == timer.Initial);
}

TEST_CASE("Testing Timer::Interval property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtTimer>())
        PhWidgetsCreateWidget<&PtTimer>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtTimer>());

    using namespace PhWidgets;
    
    Timer timer(PhWidgetsGetWidget<&PtTimer>());

    timer.Interval = 14;
    
    CHECK(timer.Interval == 14);
    CHECK(14 == timer.Interval);

    timer.Interval = 12;

    CHECK(timer.Interval == 12);
    CHECK(12 == timer.Interval);
}