

#include "./testsuit/testsuit.h"

#include <Button.h>
#include <photon/PtWindow.h>

#ifndef PH_WIDGETS_INIT_COMPLETED
static const int PhWidgetsPtInit = PtInit(NULL);
#define PH_WIDGETS_INIT_COMPLETED
#endif


TEST_CASE("Testing Widget::Cursor property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    

    using namespace PhWidgets;
    
    SUBCASE("Windows Cursor test"){
        
        if (!PhWidgetsGetWidget<&PtWindow>())
            PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
        
        REQUIRE(PhWidgetsGetWidget<&PtWindow>());

        Widget widget(PhWidgetsGetWidget<&PtWindow>());
        
        CHECK(widget.Cursor == Cursors::Inherit);
        widget.Cursor = Cursors::Finger;
        CHECK(Cursors::Finger == widget.Cursor);
    }

    SUBCASE("Button Cursor test"){
        
        if (!PhWidgetsGetWidget<&PtWindow>())
            PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
        if (!PhWidgetsGetWidget<&PtButton>())
            PhWidgetsCreateWidget<&PtButton>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
        REQUIRE(PhWidgetsGetWidget<&PtButton>());
        
        Button button(PhWidgetsGetWidget<&PtButton>());
        
        CHECK(button.Cursor == Cursors::Inherit);
        button.Cursor = Cursors::Finger;
        CHECK(Cursors::Finger == button.Cursor);
    }
}