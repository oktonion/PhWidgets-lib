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
        
        CHECK_THROWS({
            window.Parent = window;
        });
        
        CHECK((window.Parent() == nullptr));
        CHECK(!window.Parent);

        REQUIRE(button.Parent);
        
        CHECK_NOTHROW({
            button.Parent = window;
        });
        
        
        CHECK(button.Parent == window);
        CHECK(button.Parent);

        Button button2 = PtCreateWidget(PtButton, window, 0, NULL);

        CHECK(button2.Parent == window);
        CHECK(window == button2.Parent);
        CHECK(button2.Parent);

        std::set<Widget> widgets = window.Widgets;

        CHECK(widgets.find(button2) != widgets.end());

        CHECK_THROWS({
            button2.Parent = nullptr;
        });

        CHECK((nullptr != button2.Parent()));

        Window window2 = PtCreateWidget(PtWindow, window, 0, NULL);

        CHECK((window == window2.Parent()));

        CHECK_NOTHROW({
            button2.Parent = window2;
        });

        widgets = window.Widgets;

        CHECK(widgets.find(button2) == widgets.end());

        CHECK_NOTHROW({
            button2.Parent = window;
        });

        CHECK((nullptr != button2.Parent()));

        widgets = window.Widgets;

        CHECK(widgets.find(button2) != widgets.end());

        PtDestroyWidget(button2);

        widgets = window.Widgets;

        CHECK_THROWS({
            widgets.find(button2) == widgets.end();
        });

        PtDestroyWidget(window2);
    }

}