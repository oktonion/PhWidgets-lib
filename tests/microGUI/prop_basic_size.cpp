#include "./phwidgets_init.cpp"

#include "./testsuit.h"

#include <Widget.h>
#include <photon/PtWindow.h>


TEST_CASE("Testing Widget basic size properties"){

    using namespace PhWidgets;
    
    Widget widget(PhWidgetsGetWidget<&PtWindow>());

    PHWIDGETS_PROPERTY_TEST_SUBCASE(widget.Height);
    PHWIDGETS_PROPERTY_TEST_SUBCASE(widget.Width);
    PHWIDGETS_PROPERTY_TEST_SUBCASE(widget.Left);
    PHWIDGETS_PROPERTY_TEST_SUBCASE(widget.Top);

    SUBCASE("Testing Widget::Bottom property") {
        widget.Top = 120;
        widget.Height = 30;
        CHECK(widget.Bottom == widget.Top + widget.Height);
    }
}