#include "./1phwidgets_init.cpp"

#include "./testsuit.h"

#include <Widget.h>
#include <photon/PtWindow.h>


TEST_CASE("Testing Widget::Focused property"){

    using namespace PhWidgets;
    
    SUBCASE("Window Focused test"){
        REQUIRE(PhWidgetsGetWidget<&PtWindow>());

        Widget widget(PhWidgetsGetWidget<&PtWindow>());

        REQUIRE(widget.CanFocus);
        
        CHECK(widget.Focused == false);
        CHECK(widget.Focus() == true);
        CHECK_EQ(true, widget.Focused);
    }

    SUBCASE("Button Focused test"){
        REQUIRE(PhWidgetsGetWidget<&PtButton>());
        
        Button button(PhWidgetsGetWidget<&PtButton>());

        REQUIRE(button.CanFocus);
        
        CHECK(button.Focused == false);
        CHECK(button.Focus() == true);
        CHECK_EQ(true, button.Focused);
    }

}