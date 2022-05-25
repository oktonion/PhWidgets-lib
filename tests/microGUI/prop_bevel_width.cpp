

#include "./testsuit/testsuit.h"

#include <Button.h>
#include <photon/PtWindow.h>

#ifndef PH_WIDGETS_INIT_COMPLETED
static const int PhWidgetsPtInit = PtInit(NULL);
#define PH_WIDGETS_INIT_COMPLETED
#endif


TEST_CASE("Testing Widget::BevelWidth property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtButton>())
        PhWidgetsCreateWidget<&PtButton>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtButton>());

    using namespace PhWidgets;
    
    Button button(PhWidgetsGetWidget<&PtButton>());

    REQUIRE(button.WidgetFlags.has(Widget::Flags::Highlighted) == true);

    unsigned short bw = button.BevelWidth;

    bw++;

    CHECK(button.BevelWidth != bw);

    button.BevelWidth = bw;

    CHECK(bw == button.BevelWidth);
}