#include "./1phwidgets_init.cpp"

#include "./testsuit.h"

#include <Button.h>
#include <Window.h>


TEST_CASE("Testing Widget::Widgets property"){

    using namespace PhWidgets;
    
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