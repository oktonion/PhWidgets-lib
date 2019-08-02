#include "./1phwidgets_init.cpp"

#include "./testsuit.h"

#include <Button.h>
#include <Window.h>


TEST_CASE("Testing Widget::Parent property"){

    using namespace PhWidgets;
    

    SUBCASE("Button Parent test"){
        REQUIRE(PhWidgetsGetWidget<&PtButton>());
        REQUIRE(PhWidgetsGetWidget<&PtWindow>());
        
        Button button(PhWidgetsGetWidget<&PtButton>());
        Window window(PhWidgetsGetWidget<&PtWindow>());

        REQUIRE(!window.Parent);
        
        window.Parent = window;
        
        CHECK(window.Parent == window);
        CHECK(window.Parent);

        REQUIRE(button.Parent);
        
        button.Parent = window;
        
        CHECK(button.Parent == window);
        CHECK(button.Parent);
    }

}