

#include "./testsuit/testsuit.h"

#include <Widget.h>
#include <photon/PtWindow.h>

#ifndef PH_WIDGETS_INIT_COMPLETED
static const int PhWidgetsPtInit = PtInit(NULL);
#define PH_WIDGETS_INIT_COMPLETED
#endif


TEST_CASE("Testing Widget::Bounds property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtWindow>());

    using namespace PhWidgets;
    
    Widget widget(PhWidgetsGetWidget<&PtWindow>());

    // set the widget size and location using the Bounds property.
    PhArea_t bounds;
    
    CHECK(widget.Bounds != bounds);

    bounds = widget.Bounds;

    CHECK(bounds == widget.Bounds);

    PhPoint_t pos = {20, 48};
    PhDim_t size = {12, 20};

    bounds.pos = pos; // location
    bounds.size = size; // size

    widget.Bounds = bounds;
    CHECK(bounds == widget.Bounds);
}