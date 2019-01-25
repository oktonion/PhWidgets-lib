#include "./phwidgets_init.cpp"

#include "./testsuit.h"

#include <Widget.h>
#include <photon/PtWindow.h>


TEST_CASE("Testing Widget::Anchor property") {
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