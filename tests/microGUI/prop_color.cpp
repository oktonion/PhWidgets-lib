

#include "./testsuit/testsuit.h"

#include <Basic.h>
#include <Drawing/Color.h>
#include <photon/PtButton.h>

#ifndef PH_WIDGETS_INIT_COMPLETED
static const int PhWidgetsPtInit = PtInit(NULL);
#define PH_WIDGETS_INIT_COMPLETED
#endif

TEST_CASE("Testing Basic::Color property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtButton>())
        PhWidgetsCreateWidget<&PtButton>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtButton>());

    using namespace PhWidgets;
    
    Basic widget(PhWidgetsGetWidget<&PtButton>());

    widget.Color = Drawing::Colors::Blue;
    
    CHECK(widget.Color == Drawing::Colors::Blue);
    CHECK(Drawing::Colors::Blue == widget.Color);

    widget.Color = Pg_BLACK;

    CHECK(widget.Color == Pg_BLACK);
    CHECK(Pg_BLACK == widget.Color);
}