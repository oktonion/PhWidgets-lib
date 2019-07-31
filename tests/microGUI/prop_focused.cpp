#include "./1phwidgets_init.cpp"

#include "./testsuit.h"

#include <Widget.h>
#include <Window.h>


TEST_CASE("Testing Widget::Focused property"){

    using namespace PhWidgets;
    
    SUBCASE("Window Focused test"){
        REQUIRE(PhWidgetsGetWidget<&PtWindow>());

        Window window(PhWidgetsGetWidget<&PtWindow>());

        REQUIRE(window.CanFocus);
        
        CHECK(window.Focused == false);
        CHECK(window.Focus() == true);
        CHECK_EQ(true, window.Focused);
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