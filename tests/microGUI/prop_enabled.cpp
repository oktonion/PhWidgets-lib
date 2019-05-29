#include "./phwidgets_init.cpp"

#include "./testsuit.h"

#include <Widget.h>
#include <photon/PtWindow.h>


TEST_CASE("Testing Widget::Enabled property"){

    using namespace PhWidgets;
    
    SUBCASE("Windows Enabled test"){
        REQUIRE(PhWidgetsGetWidget<&PtWindow>());

        Widget widget(PhWidgetsGetWidget<&PtWindow>());
        
        CHECK(widget.Enabled == false);
        widget.Enabled = true;
        CHECK(true == widget.Enabled);
    }

    SUBCASE("Button Enabled test"){
        REQUIRE(PhWidgetsGetWidget<&PtButton>());
        
        Button button(PhWidgetsGetWidget<&PtButton>());
        
        CHECK(button.Enabled == false);
        button.Enabled = true;
        CHECK(true == button.Enabled);
    }
}