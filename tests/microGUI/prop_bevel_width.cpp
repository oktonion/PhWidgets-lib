#include "./1phwidgets_init.cpp"

#include "./testsuit/testsuit.h"

#include <Widget.h>
#include <photon/PtWindow.h>


TEST_CASE("Testing Widget::BevelWidth property"){
    REQUIRE(PhWidgetsGetWidget<&PtButton>());

    using namespace PhWidgets;
    
    Button button(PhWidgetsGetWidget<&PtButton>());

    REQUIRE(button.WidgetFlags.has(Widget::Flags::Highlighted) == true);

    unsigned short bw = button.BevelWidth;

    bw++;

    CHECK(button.BevelWidth != bw);

    button.BevelWidth = bw;

    CHECK(bw == button.BevelWidth);
}