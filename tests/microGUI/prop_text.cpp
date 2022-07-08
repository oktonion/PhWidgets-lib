

#include "./testsuit/testsuit.h"

#include <Label.h>
#include <Text.h>
#include <Window.h>

#ifndef PH_WIDGETS_INIT_COMPLETED
static const int PhWidgetsPtInit = PtInit(NULL);
#define PH_WIDGETS_INIT_COMPLETED
#endif

TEST_CASE("Testing Label::Text property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    

    using namespace PhWidgets;
    

    SUBCASE("Label Text test"){

        if (!PhWidgetsGetWidget<&PtWindow>())
            PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
        if (!PhWidgetsGetWidget<&PtLabel>())
            PhWidgetsCreateWidget<&PtLabel>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);

        REQUIRE(PhWidgetsGetWidget<&PtLabel>());
        
        Label label(PhWidgetsGetWidget<&PtLabel>());

        label.Text = "";

        CHECK(label.Text() == std::string(""));

        label.Text = "Missisipi 1";
        CHECK(label.Text() == std::string("Missisipi 1"));

        label.Text = "Missisipi 2";
        CHECK(std::string("Missisipi 2") == label.Text());
    }

    SUBCASE("Text Label::Text test"){

        if (!PhWidgetsGetWidget<&PtWindow>())
            PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
        if (!PhWidgetsGetWidget<&PtText>())
            PhWidgetsCreateWidget<&PtText>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);

        REQUIRE(PhWidgetsGetWidget<&PtText>());
        
        Text text(PhWidgetsGetWidget<&PtText>());

        text.Text = "";

        CHECK(text.Text() == std::string(""));

        text.Text = "Missisipi 3";
        CHECK(text.Text() == std::string("Missisipi 3"));

        text.Text = "Missisipi 4";
        CHECK(std::string("Missisipi 4") == text.Text());
    }

    SUBCASE("Text Label::TextClippedAlign test"){

        if (!PhWidgetsGetWidget<&PtWindow>())
            PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
        if (!PhWidgetsGetWidget<&PtLabel>())
            PhWidgetsCreateWidget<&PtLabel>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
            
        REQUIRE(PhWidgetsGetWidget<&PtLabel>());

        using namespace PhWidgets;

        Label label(PhWidgetsGetWidget<&PtLabel>());

        label.TextClippedAlign = Drawing::ContentAlignment::TopRight;
        CHECK(label.TextClippedAlign == Drawing::ContentAlignment::TopRight);
        CHECK(Drawing::ContentAlignment::TopRight == label.TextClippedAlign);

        label.TextClippedAlign = Drawing::ContentAlignment::MiddleRight;
        CHECK(label.TextClippedAlign == Drawing::ContentAlignment::MiddleRight);
        CHECK(Drawing::ContentAlignment::MiddleRight == label.TextClippedAlign);

        label.TextClippedAlign = Drawing::ContentAlignment::BottomRight;
        CHECK(label.TextClippedAlign == Drawing::ContentAlignment::BottomRight);
        CHECK(Drawing::ContentAlignment::BottomRight == label.TextClippedAlign);
    }

}

TEST_CASE("Testing Window::Title property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    using namespace PhWidgets;

    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
    
    REQUIRE(PhWidgetsGetWidget<&PtWindow>());
    
    Window window(PhWidgetsGetWidget<&PtWindow>());    

    window.Title("title");
    CHECK("title" == window.Title());
}