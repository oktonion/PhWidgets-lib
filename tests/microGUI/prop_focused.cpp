

#include "./testsuit/testsuit.h"

#include <Button.h>
#include <Window.h>

#ifndef PH_WIDGETS_INIT_COMPLETED
static const int PhWidgetsPtInit = PtInit(NULL);
#define PH_WIDGETS_INIT_COMPLETED
#endif

TEST_CASE("Testing Widget::Focused property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    

    using namespace PhWidgets;

    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtButton>())
        PhWidgetsCreateWidget<&PtButton>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
    
    SUBCASE("Window Focused test"){
        
        REQUIRE(PhWidgetsGetWidget<&PtWindow>());

        Window window(PhWidgetsGetWidget<&PtWindow>());

        if (!window.IsRealized)
        {
            CHECK(true == window.Realize());
        }

        window.Enabled = true;
        window.resource.argument[Window::Arguments::flags].set(Widget::Flags::GetsFocus, true);


        REQUIRE(window.Enabled);
        REQUIRE(window.CanFocus);

        if (!window.Focused)
        {
            CHECK(false == window.Focused);         
        }

        CHECK(window.Focus() == true);
        CHECK(window.Focused == true);  
    }

    SUBCASE("Button Focused test"){

        REQUIRE(PhWidgetsGetWidget<&PtButton>());
        
        Button button(PhWidgetsGetWidget<&PtButton>());

        if (!button.IsRealized)
        {
            CHECK(true == button.Realize());
        }

        button.Enabled = true;

        REQUIRE(button.Enabled);
        REQUIRE(button.CanFocus);
        
        CHECK(button.Focused == false);
        CHECK(button.Focus() == true);
        CHECK(button.Focused == true);
    }

}