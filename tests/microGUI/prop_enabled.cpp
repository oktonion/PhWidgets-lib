

#include "./testsuit/testsuit.h"

#include <Button.h>
#include <photon/PtWindow.h>

#ifndef PH_WIDGETS_INIT_COMPLETED
static const int PhWidgetsPtInit = PtInit(NULL);
#define PH_WIDGETS_INIT_COMPLETED
#endif

TEST_CASE("Testing Widget::Enabled property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    

    using namespace PhWidgets;
    
    SUBCASE("Windows Enabled test"){

        if (!PhWidgetsGetWidget<&PtWindow>())
            PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
        
    
        REQUIRE(PhWidgetsGetWidget<&PtWindow>());

        Widget widget(PhWidgetsGetWidget<&PtWindow>());

        if (!widget.IsRealized)
        {
            CHECK(widget.Enabled == false);
            widget.Enabled = true;
            CHECK(false == widget.Enabled);
            CHECK(true == widget.Realize());
        }

        REQUIRE(widget.IsRealized);

        CHECK(widget.Enabled == true);
        widget.Enabled = false;
        CHECK(false == widget.Enabled);
    
    }

    SUBCASE("Button Enabled test"){

        if (!PhWidgetsGetWidget<&PtWindow>())
            PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
        if (!PhWidgetsGetWidget<&PtButton>())
            PhWidgetsCreateWidget<&PtButton>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    
        REQUIRE(PhWidgetsGetWidget<&PtButton>());
        
        Button button(PhWidgetsGetWidget<&PtButton>());
        
        if (!button.IsRealized)
        {
            CHECK(button.Enabled == false);
            button.Enabled = true;
            CHECK(false == button.Enabled);
            CHECK(true == button.Realize());
        }

        REQUIRE(button.IsRealized);

        CHECK(button.Enabled == true);
        button.Enabled = false;
        CHECK(false == button.Enabled);
    }
}