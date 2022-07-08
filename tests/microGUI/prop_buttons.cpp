#include "./testsuit/testsuit.h"

#include <OnOffButton.h>
#include <ToggleButton.h>

#include <Drawing/Color.h>
#include <photon/PtButton.h>

#ifndef PH_WIDGETS_INIT_COMPLETED
static const int PhWidgetsPtInit = PtInit(NULL);
#define PH_WIDGETS_INIT_COMPLETED
#endif

TEST_CASE("Testing OnOffButton::IsChecked property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtOnOffButton>())
        PhWidgetsCreateWidget<&PtOnOffButton>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtOnOffButton>());

    using namespace PhWidgets;
        
    OnOffButton button(PhWidgetsGetWidget<&PtOnOffButton>());

    if (!button.IsChecked)
    {
        CHECK(button.IsChecked == false);
        button.IsChecked = true;
    }        
    
    REQUIRE(button.IsChecked);
    CHECK(button.IsChecked == true);
    button.IsChecked = false;
    CHECK(false == button.IsChecked);
}

TEST_CASE("Testing ToggleButton::IsChecked property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtToggleButton>())
        PhWidgetsCreateWidget<&PtToggleButton>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtToggleButton>());

    using namespace PhWidgets;
        
    ToggleButton button(PhWidgetsGetWidget<&PtToggleButton>());

    if (!button.IsChecked)
    {
        CHECK(button.IsChecked == false);
        button.IsChecked = true;
    }        
    
    REQUIRE(button.IsChecked);
    CHECK(button.IsChecked == true);
    button.IsChecked = false;
    CHECK(false == button.IsChecked);
}

TEST_CASE("Testing ToggleButton::IndicatorType property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtToggleButton>())
        PhWidgetsCreateWidget<&PtToggleButton>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtToggleButton>());

    using namespace PhWidgets;
        
    ToggleButton button(PhWidgetsGetWidget<&PtToggleButton>());

    button.IndicatorType = ToggleIndicatorType::Radio;
    CHECK(button.IndicatorType == ToggleIndicatorType::Radio);
    CHECK(ToggleIndicatorType::Radio == button.IndicatorType);

    button.IndicatorType = ToggleIndicatorType::Outline;
    CHECK(button.IndicatorType == ToggleIndicatorType::Outline);
    CHECK(ToggleIndicatorType::Outline == button.IndicatorType);

    button.IndicatorType = ToggleIndicatorType::Check;
    CHECK(button.IndicatorType == ToggleIndicatorType::Check);
    CHECK(ToggleIndicatorType::Check == button.IndicatorType);
}

TEST_CASE("Testing ToggleButton::IndicatorColor property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtToggleButton>())
        PhWidgetsCreateWidget<&PtToggleButton>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtToggleButton>());

    using namespace PhWidgets;
        
    ToggleButton button(PhWidgetsGetWidget<&PtToggleButton>());

    button.IndicatorColor = Drawing::Colors::Blue;
    
    CHECK(button.IndicatorColor == Drawing::Colors::Blue);
    CHECK(Drawing::Colors::Blue == button.IndicatorColor);

    button.IndicatorColor = Pg_BLACK;

    CHECK(button.IndicatorColor == Pg_BLACK);
    CHECK(Pg_BLACK == button.IndicatorColor);
}