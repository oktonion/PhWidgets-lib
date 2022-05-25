

#include "./testsuit/testsuit.h"

#include <Widget.h>
#include <photon/PtWindow.h>

#ifndef PH_WIDGETS_INIT_COMPLETED
static const int PhWidgetsPtInit = PtInit(NULL);
#define PH_WIDGETS_INIT_COMPLETED
#endif


TEST_CASE("Testing Widget::Anchor property") {
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtWindow>());
    
    using namespace PhWidgets;

    Widget widget(PhWidgetsGetWidget<&PtWindow>());
    
    CHECK(widget.Anchor == AnchorStyles::None);
    widget.Anchor = AnchorStyles::Left;
    CHECK(widget.Anchor == AnchorStyles::Left);
    CHECK(widget.Anchor != (AnchorStyles::Left | AnchorStyles::Top));
    widget.Anchor = AnchorStyles::Bottom;
    CHECK(AnchorStyles::Bottom == widget.Anchor);
    CHECK(AnchorStyles::Left != widget.Anchor);

    widget.Anchor = (AnchorStyles::TopAnchoredBottom | AnchorStyles::LeftAnchoredRight);
    CHECK((AnchorStyles::TopAnchoredBottom | AnchorStyles::LeftAnchoredRight) == widget.Anchor);
    CHECK(AnchorStyles::TopAnchoredBottom != widget.Anchor);
    CHECK(widget.Anchor == (AnchorStyles::TopAnchoredBottom | AnchorStyles::LeftAnchoredRight));
    CHECK(widget.Anchor.has(AnchorStyles::LeftAnchoredRight));
}