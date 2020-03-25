#include "./1phwidgets_init.cpp"

#include "./testsuit/testsuit.h"

#include <Widget.h>
#include <photon/PtWindow.h>


TEST_CASE("Testing Widget::Bounds property"){
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