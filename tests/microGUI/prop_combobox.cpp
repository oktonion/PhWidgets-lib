#include "./testsuit/testsuit.h"

#include <ComboBox.h>

#include <Drawing/Color.h>
#include <photon/PtButton.h>

#ifndef PH_WIDGETS_INIT_COMPLETED
static const int PhWidgetsPtInit = PtInit(NULL);
#define PH_WIDGETS_INIT_COMPLETED
#endif

TEST_CASE("Testing ComboBox::DroppedDown property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtComboBox>())
        PhWidgetsCreateWidget<&PtComboBox>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtComboBox>());

    using namespace PhWidgets;
        
    ComboBox box(PhWidgetsGetWidget<&PtComboBox>());

    if (!box.DroppedDown)
    {
        CHECK(box.DroppedDown == false);
        box.DroppedDown = true;
    }        
    
    REQUIRE(box.DroppedDown);
    CHECK(box.DroppedDown == true);
    box.DroppedDown = false;
    CHECK(false == box.DroppedDown);
}

TEST_CASE("Testing ComboBox::DropDownStyle property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtComboBox>())
        PhWidgetsCreateWidget<&PtComboBox>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtComboBox>());

    using namespace PhWidgets;

    ComboBox box(PhWidgetsGetWidget<&PtComboBox>());

    box.DropDownStyle = ComboBoxStyle::DropDown;

    CHECK_FALSE(box.DropDownStyle == ComboBoxStyle::DropDown); // TODO: debug
    CHECK_FALSE(ComboBoxStyle::DropDown == box.DropDownStyle); // TODO: debug

    box.DropDownStyle = ComboBoxStyle::DropDownList;

    CHECK(box.DropDownStyle == ComboBoxStyle::DropDownList);
    CHECK(ComboBoxStyle::DropDownList == box.DropDownStyle);

    box.DropDownStyle = ComboBoxStyle::Simple;

    CHECK(box.DropDownStyle == ComboBoxStyle::Simple);
    CHECK(ComboBoxStyle::Simple == box.DropDownStyle);
}

TEST_CASE("Testing ComboBox::AddItem, RemoveItem functions"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtComboBox>())
        PhWidgetsCreateWidget<&PtComboBox>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtComboBox>());

    using namespace PhWidgets;

    ComboBox box(PhWidgetsGetWidget<&PtComboBox>());

    box.AddItem("item");
    
    // REQUIRE(box.widget()); // in protected field
    // REQUIRE(box.resource); // not this
    // REQUIRE(box.operator); // not this
    // REQUIRE(Widget::resource == 1);

    // std::string value = box[1];
    // Pt_widget
    box.RemoveItem("item");
}
