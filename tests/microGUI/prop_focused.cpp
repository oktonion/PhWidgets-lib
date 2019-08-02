#include "./1phwidgets_init.cpp"

#include "./testsuit.h"

#include <Widget.h>
#include <Window.h>


TEST_CASE("Testing Widget::Focused property"){

    using namespace PhWidgets;
    
    SUBCASE("Window Focused test"){
        REQUIRE(PhWidgetsGetWidget<&PtWindow>());

        Window window(PhWidgetsGetWidget<&PtWindow>());

        window.Enabled = true;
        window.resource.argument[Window::Arguments::flags].set(Widget::Flags::GetsFocus, true);

        REQUIRE(window.Enabled);
        REQUIRE(window.CanFocus);

        CHECK(false == window.Focused);
        CHECK(window.Focus() == true);
        CHECK_EQ(window.Focused, true);
    }

    SUBCASE("Button Focused test"){
        REQUIRE(PhWidgetsGetWidget<&PtButton>());
        
        Button button(PhWidgetsGetWidget<&PtButton>());

        button.Enabled = true;

        REQUIRE(button.Enabled);
        REQUIRE(button.CanFocus);
        
        CHECK(button.Focused == false);
        CHECK(button.Focus() == true);
        CHECK_EQ(true, button.Focused);
    }

}