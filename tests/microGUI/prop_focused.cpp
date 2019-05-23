#include "./phwidgets_init.cpp"

#include "./testsuit.h"

#include <Widget.h>
#include <photon/PtWindow.h>


TEST_CASE("Testing Widget::Focused property"){

    using namespace PhWidgets;
    
    SUBCASE("Windows Focused test"){
        REQUIRE(PhWidgetsGetWidget<&PtWindow>());

        Widget widget(PhWidgetsGetWidget<&PtWindow>());
        
        CHECK(widget.Focused == false);
        CHECK(widget.Focus() == true);
        CHECK(true = widget.Focused);
    }

    SUBCASE("Button Focused test"){
        REQUIRE(PhWidgetsGetWidget<&PtButton>());
        
        Button button(PhWidgetsGetWidget<&PtButton>());
        
        CHECK(button.Focused == false);
        CHECK(button.Focus() == true);
        CHECK(true = button.Focused);
    }

}