#include "./1phwidgets_init.cpp"

#include "./testsuit/testsuit.h"

#include <Widget.h>
#include <photon/PtWindow.h>


TEST_CASE("Testing Widget::Enabled property"){

    using namespace PhWidgets;
    
    SUBCASE("Windows Enabled test"){
        REQUIRE(PhWidgetsGetWidget<&PtWindow>());

        Widget widget(PhWidgetsGetWidget<&PtWindow>());
        
        CHECK(widget.Enabled == true);
        widget.Enabled = false;
        CHECK(false == widget.Enabled);
    }

    SUBCASE("Button Enabled test"){
        REQUIRE(PhWidgetsGetWidget<&PtButton>());
        
        Button button(PhWidgetsGetWidget<&PtButton>());
        
        CHECK(button.Enabled == true);
        button.Enabled = false;
        CHECK(false == button.Enabled);
    }
}