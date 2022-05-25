

#include "./testsuit/testsuit.h"

#include <Window.h>

#ifndef PH_WIDGETS_INIT_COMPLETED
static const int PhWidgetsPtInit = PtInit(NULL);
#define PH_WIDGETS_INIT_COMPLETED
#endif


TEST_CASE("Testing Widget::AllowDrop property") {
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtWindow>());
    
    using namespace PhWidgets;

    Window window(PhWidgetsGetWidget<&PtWindow>());
    
    CHECK(false == window.AllowDrop);
    window.AllowDrop = true;
    CHECK(false == window.AllowDrop);
    window.Realize();
    CHECK(true == window.AllowDrop);
    window.AllowDrop = false;
    CHECK(window.AllowDrop == false);
}