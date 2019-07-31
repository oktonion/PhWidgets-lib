#include "./1phwidgets_init.cpp"

#include "./testsuit.h"

#include <Widget.h>
#include <photon/PtWindow.h>


TEST_CASE("Testing Widget::AllowDrop property") {
    REQUIRE(PhWidgetsGetWidget<&PtWindow>());
    
    using namespace PhWidgets;

    Widget widget(PhWidgetsGetWidget<&PtWindow>());
    
    CHECK(false == widget.AllowDrop);
    widget.AllowDrop = true;
    CHECK(true == widget.AllowDrop);
    widget.AllowDrop = false;
    CHECK(widget.AllowDrop == false);
}