

#include "./testsuit/testsuit.h"

#include <Button.h>
#include <Window.h>

#ifndef PH_WIDGETS_INIT_COMPLETED
static const int PhWidgetsPtInit = PtInit(NULL);
#define PH_WIDGETS_INIT_COMPLETED
#endif

TEST_CASE("Testing Widget::Widgets property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    

    using namespace PhWidgets;

    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtButton>())
        PhWidgetsCreateWidget<&PtButton>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
    
    REQUIRE(PhWidgetsGetWidget<&PtButton>());
    REQUIRE(PhWidgetsGetWidget<&PtWindow>());
    
    Button button(PhWidgetsGetWidget<&PtButton>());
    Window window(PhWidgetsGetWidget<&PtWindow>());

    CHECK(button.Widgets.size() == 0);
    CHECK(window.Widgets.size() != 0);


    typedef std::set<Widget>::iterator iterator;
    std::set<Widget> widgets = window.Widgets;

    bool button_parent_is_window = false;

    for(iterator it = widgets.begin(); it != widgets.end(); ++it)
    {
        CHECK(it->Parent == window);
        if(*it == button)
            button_parent_is_window = true;
    }

    CHECK(button_parent_is_window);
}