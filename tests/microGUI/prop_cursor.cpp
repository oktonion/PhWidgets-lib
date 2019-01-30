#include "./phwidgets_init.cpp"

#include "./testsuit.h"

#include <Widget.h>
#include <photon/PtWindow.h>


TEST_CASE("Testing Widget::Cursor property"){

    using namespace PhWidgets;
    
    SUBCASE("Windows Cursor test"){
        REQUIRE(PhWidgetsGetWidget<&PtWindow>());

        Widget widget(PhWidgetsGetWidget<&PtWindow>());
        
        CHECK(widget.Cursor() == Cursors::None);
    }

    SUBCASE("Button Cursor test"){
        REQUIRE(PhWidgetsGetWidget<&PtButton>());
        
        Button button(PhWidgetsGetWidget<&PtButton>());
        
        CHECK(button.Cursor() == Cursors::None);
    }
}