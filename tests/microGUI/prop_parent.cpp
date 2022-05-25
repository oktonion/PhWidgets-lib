

#include "./testsuit/testsuit.h"

#include <Button.h>
#include <Window.h>

#ifndef PH_WIDGETS_INIT_COMPLETED
static const int PhWidgetsPtInit = PtInit(NULL);
#define PH_WIDGETS_INIT_COMPLETED
#endif

TEST_CASE("Testing Widget::Parent property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    

    using namespace PhWidgets;
    

    SUBCASE("Button Parent test"){

        if (!PhWidgetsGetWidget<&PtWindow>())
            PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
        if (!PhWidgetsGetWidget<&PtButton>())
            PhWidgetsCreateWidget<&PtButton>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
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

        Button button2(PtCreateWidget(PtButton, window, 0, NULL));

        CHECK(button2.Parent == window);
        CHECK(window == button2.Parent);
        CHECK(button2.Parent);

        std::set<Widget> widgets = window.Widgets;

        CHECK(widgets.find(button2) != widgets.end());

        CHECK_THROWS({
            button2.Parent = nullptr;
        });

        CHECK((nullptr != button2.Parent()));

        Window window2(PtCreateWidget(PtWindow, window, 0, NULL));

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