#include "./1phwidgets_init.cpp"

#include "./testsuit/testsuit.h"

#include <Window.h>


TEST_CASE("Testing Widget::AllowDrop property") {
    REQUIRE(PhWidgetsGetWidget<&PtWindow>());
    
    using namespace PhWidgets;

    Window window(PhWidgetsGetWidget<&PtWindow>());
    
    CHECK(false == window.AllowDrop);
    window.AllowDrop = true;
    CHECK(true == window.AllowDrop);
    window.AllowDrop = false;
    CHECK(window.AllowDrop == false);
}