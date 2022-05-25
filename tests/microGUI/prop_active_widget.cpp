

#include "./testsuit/testsuit.h"

#include <Container.h>
#include <Button.h>

#ifndef PH_WIDGETS_INIT_COMPLETED
static const int PhWidgetsPtInit = PtInit(NULL);
#define PH_WIDGETS_INIT_COMPLETED
#endif


TEST_CASE("Testing Container::ActiveWidget property") {
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
        
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