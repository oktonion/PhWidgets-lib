#include "./1phwidgets_init.cpp"

#include "./testsuit.h"

#include <Container.h>
#include <Button.h>


TEST_CASE("Testing Container::ActiveWidget property") {
    REQUIRE(PhWidgetsGetWidget<&PtWindow>());
    
    using namespace PhWidgets;

    Container container(PhWidgetsGetWidget<&PtWindow>());
    
    Widget active_widget = container;

    Button button(PtCreateWidget(PtButton, container, 0, NULL));

    container.ActiveWidget = button;

    CHECK_NOTHROW({
        active_widget = container.ActiveWidget;
    });

    CHECK(active_widget == container.ActiveWidget);
    CHECK(container.ActiveWidget != container);
    CHECK(container.ActiveWidget == button);

    PtDestroyWidget(button);
}