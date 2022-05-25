

#include "./testsuit/testsuit.h"

#include <Widget.h>
#include <photon/PtWindow.h>

#ifndef PH_WIDGETS_INIT_COMPLETED
static const int PhWidgetsPtInit = PtInit(NULL);
#define PH_WIDGETS_INIT_COMPLETED
#endif


TEST_CASE("Testing Widget basic size properties"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtWindow>());

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

    SUBCASE("Testing Widget::Right property") {
        widget.Left = 120;
        widget.Width = 42;
        CHECK(widget.Right == widget.Left + widget.Width);
    }
}