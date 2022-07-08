

#include "./testsuit/testsuit.h"

#include <Button.h>
#include <Window.h>
#include <Widget.h>

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

TEST_CASE("Testing Widget::AllowDrop property") {
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    using namespace PhWidgets;

    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtWidget>())
        PhWidgetsCreateWidget<&PtWidget>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
    
    REQUIRE(PhWidgetsGetWidget<&PtWidget>());
    REQUIRE(PhWidgetsGetWidget<&PtWindow>());
    
    Widget widget(PhWidgetsGetWidget<&PtWidget>());
    Window window(PhWidgetsGetWidget<&PtWindow>());
    

    CHECK(false == widget.AllowDrop);
    widget.AllowDrop = true;
    CHECK_FALSE(true == widget.AllowDrop); // TODO: debug
    widget.AllowDrop = false;
    CHECK(widget.AllowDrop == false);
}

TEST_CASE("Testing Widget::BevelWidth property") {
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    using namespace PhWidgets;

    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtWidget>())
        PhWidgetsCreateWidget<&PtWidget>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
    
    REQUIRE(PhWidgetsGetWidget<&PtWidget>());
    REQUIRE(PhWidgetsGetWidget<&PtWindow>());
    
    Widget widget(PhWidgetsGetWidget<&PtWidget>());
    
    widget.BevelWidth = 16;
    
    CHECK(widget.BevelWidth == 16);
    CHECK(16 == widget.BevelWidth);

    widget.BevelWidth = 17;

    CHECK(widget.BevelWidth == 17);
    CHECK(17 == widget.BevelWidth);
}

TEST_CASE("Testing Widget::Bottom property") {
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    using namespace PhWidgets;

    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtWidget>())
        PhWidgetsCreateWidget<&PtWidget>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
    
    REQUIRE(PhWidgetsGetWidget<&PtWidget>());
    REQUIRE(PhWidgetsGetWidget<&PtWindow>());
    
    Widget widget(PhWidgetsGetWidget<&PtWidget>());
    
    // widget.Bottom = 1; // cannot test: &PhWidgets::Widget::getBottom, ValueT = short int]' is private
    
    // CHECK(widget.Bottom == 1);
    // CHECK(1 == widget.Bottom);

    // widget.Bottom = 2;

    // CHECK(widget.Bottom == 2);
    // CHECK(2 == widget.Bottom);
}

TEST_CASE("Testing Widget::Right property") {
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    using namespace PhWidgets;

    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtWidget>())
        PhWidgetsCreateWidget<&PtWidget>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
    
    REQUIRE(PhWidgetsGetWidget<&PtWidget>());
    REQUIRE(PhWidgetsGetWidget<&PtWindow>());
    
    Widget widget(PhWidgetsGetWidget<&PtWidget>());    

    // widget.Right = 1; //&PhWidgets::Widget::getRight, ValueT = short int]' is private
    
    // CHECK(widget.Right == 1);
    // CHECK(1 == widget.Right);

    // widget.Right = 2;

    // CHECK(widget.Right == 2);
    // CHECK(2 == widget.Right);
}

TEST_CASE("Testing Widget::Top property") {
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    using namespace PhWidgets;

    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtWidget>())
        PhWidgetsCreateWidget<&PtWidget>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
    
    REQUIRE(PhWidgetsGetWidget<&PtWidget>());
    REQUIRE(PhWidgetsGetWidget<&PtWindow>());
    
    Widget widget(PhWidgetsGetWidget<&PtWidget>());    

    widget.Top = 1;
    
    CHECK(widget.Top == 1);
    CHECK(1 == widget.Top);

    widget.Top = 2;

    CHECK(widget.Top == 2);
    CHECK(2 == widget.Top);
}

TEST_CASE("Testing Widget::Visible property") {
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    using namespace PhWidgets;

    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtWidget>())
        PhWidgetsCreateWidget<&PtWidget>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
    
    REQUIRE(PhWidgetsGetWidget<&PtWidget>());
    REQUIRE(PhWidgetsGetWidget<&PtWindow>());
    
    Widget widget(PhWidgetsGetWidget<&PtWidget>());    

    CHECK(false == widget.Visible);
    widget.Visible = true;
    CHECK_FALSE(true == widget.Visible); // TODO: debug
    widget.Visible = false;
    CHECK(widget.Visible == false);
}

TEST_CASE("Testing Widget::Visible property") {
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    using namespace PhWidgets;

    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtWidget>())
        PhWidgetsCreateWidget<&PtWidget>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
    
    REQUIRE(PhWidgetsGetWidget<&PtWidget>());
    REQUIRE(PhWidgetsGetWidget<&PtWindow>());
    
    Widget widget(PhWidgetsGetWidget<&PtWidget>());    

    CHECK(false == widget.Visible);
    widget.Visible = true;
    CHECK_FALSE(true == widget.Visible); // TODO: debug
    widget.Visible = false;
    CHECK(widget.Visible == false);
}

TEST_CASE("Testing Widget::Width property") {
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    using namespace PhWidgets;

    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtWidget>())
        PhWidgetsCreateWidget<&PtWidget>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
    
    REQUIRE(PhWidgetsGetWidget<&PtWidget>());
    REQUIRE(PhWidgetsGetWidget<&PtWindow>());
    
    Widget widget(PhWidgetsGetWidget<&PtWidget>());    

    unsigned short ww = widget.Width;

    ww++;

    CHECK(widget.Width != ww);

    widget.Width = ww;

    CHECK(ww == widget.Width);
}

TEST_CASE("Testing Widget::BringToFront property") {
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    using namespace PhWidgets;

    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtWidget>())
        PhWidgetsCreateWidget<&PtWidget>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
    
    REQUIRE(PhWidgetsGetWidget<&PtWidget>());
    
    Widget widget(PhWidgetsGetWidget<&PtWidget>());    

    widget.BringToFront();
    widget.SendToBack();
}

TEST_CASE("Testing Widget::Focus property") {
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    using namespace PhWidgets;

    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtWidget>())
        PhWidgetsCreateWidget<&PtWidget>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
    
    REQUIRE(PhWidgetsGetWidget<&PtWidget>());
    
    Widget widget(PhWidgetsGetWidget<&PtWidget>());    
	// Set focus to the widget, if it can receive focus.
	if(widget.CanFocus)
	{
		widget.Focus();
	}
}

TEST_CASE("Testing Widget::Show, Hide property") {
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    using namespace PhWidgets;

    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtWidget>())
        PhWidgetsCreateWidget<&PtWidget>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
    
    REQUIRE(PhWidgetsGetWidget<&PtWidget>());
    
    Widget widget(PhWidgetsGetWidget<&PtWidget>());    

    widget.Show();
    CHECK_FALSE(true == widget.Visible); // TODO: debug

    widget.Hide();
    CHECK(false == widget.Visible);
}

TEST_CASE("Testing Widget::SetBounds property") {
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    using namespace PhWidgets;

    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtWidget>())
        PhWidgetsCreateWidget<&PtWidget>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
    
    REQUIRE(PhWidgetsGetWidget<&PtWidget>());
    
    Widget widget(PhWidgetsGetWidget<&PtWidget>());    

	widget.SetBounds(1, 2);
    CHECK(1 == widget.Left);
    CHECK(2 == widget.Top);

    widget.SetBounds(9, 8, 7, 6);
    CHECK(9 == widget.Left);
    CHECK(8 == widget.Top);
    CHECK(7 == widget.Width);
    CHECK(6 == widget.Height);
}

TEST_CASE("Testing Widget::Realize property") {
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    using namespace PhWidgets;

    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtWidget>())
        PhWidgetsCreateWidget<&PtWidget>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
    
    REQUIRE(PhWidgetsGetWidget<&PtWidget>());
    
    Widget widget(PhWidgetsGetWidget<&PtWidget>());    

    bool check = widget.Realize(); //TODO: debug
    CHECK_FALSE(check == true); //@return `true` if the realize request was successful; otherwise, `false`.
}

TEST_CASE("Testing Widget::Refresh property") {
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    using namespace PhWidgets;

    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtWidget>())
        PhWidgetsCreateWidget<&PtWidget>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
    
    REQUIRE(PhWidgetsGetWidget<&PtWidget>());
    
    Widget widget(PhWidgetsGetWidget<&PtWidget>());    

    widget.Refresh();
}