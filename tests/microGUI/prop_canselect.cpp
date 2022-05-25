

#include "./testsuit/testsuit.h"

#include <Widget.h>
#include <photon/PtWindow.h>

#ifndef PH_WIDGETS_INIT_COMPLETED
static const int PhWidgetsPtInit = PtInit(NULL);
#define PH_WIDGETS_INIT_COMPLETED
#endif

TEST_CASE("Testing Widget::CanSelect property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtWindow>());

    using namespace PhWidgets;
    
    Widget widget(PhWidgetsGetWidget<&PtWindow>());

    CHECK(widget.CanSelect == false);
}