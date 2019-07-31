#include "./1phwidgets_init.cpp"

#include "./testsuit.h"

#include <Widget.h>
#include <photon/PtWindow.h>


TEST_CASE("Testing Widget::Cursor property"){

    using namespace PhWidgets;
    
    SUBCASE("Windows Cursor test"){
        REQUIRE(PhWidgetsGetWidget<&PtWindow>());

        Widget widget(PhWidgetsGetWidget<&PtWindow>());
        
        CHECK(widget.Cursor == Cursors::Inherit);
        widget.Cursor = Cursors::Finger;
        CHECK(Cursors::Finger == widget.Cursor);
    }

    SUBCASE("Button Cursor test"){
        REQUIRE(PhWidgetsGetWidget<&PtButton>());
        
        Button button(PhWidgetsGetWidget<&PtButton>());
        
        CHECK(button.Cursor == Cursors::Inherit);
        button.Cursor = Cursors::Finger;
        CHECK(Cursors::Finger == button.Cursor);
    }
}