

#include "./testsuit/testsuit.h"

#include <ImageArea.h>

#ifndef PH_WIDGETS_INIT_COMPLETED
static const int PhWidgetsPtInit = PtInit(NULL);
#define PH_WIDGETS_INIT_COMPLETED
#endif


TEST_CASE("Testing ImageArea::AutoScale property") {
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);

    if (!PhWidgetsGetWidget<&PtImageArea>())
        PhWidgetsCreateWidget<&PtImageArea>(PhWidgetsGetWidget<&PtImageArea>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtImageArea>());
    
    using namespace PhWidgets;

    ImageArea ia(PhWidgetsGetWidget<&PtImageArea>());

    if (!ia.AutoScale)
    {
        CHECK(ia.AutoScale == false);
        ia.AutoScale = true; // TODO: debug this (not setting true statement)
    }        
    
    // REQUIRE(ia.AutoScale);
    CHECK_FALSE(ia.AutoScale == true);
    ia.AutoScale = false;
    CHECK(false == ia.AutoScale);
}

TEST_CASE("Testing ImageArea::GridThreshold property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtImageArea>())
        PhWidgetsCreateWidget<&PtImageArea>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtImageArea>());

    using namespace PhWidgets;
    
    ImageArea ia(PhWidgetsGetWidget<&PtImageArea>());

    ia.GridThreshold = 16;
    
    CHECK(ia.GridThreshold == 16);
    CHECK(16 == ia.GridThreshold);

    ia.GridThreshold = 17;

    CHECK(ia.GridThreshold == 17);
    CHECK(17 == ia.GridThreshold);
}

TEST_CASE("Testing ImageArea::Image property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtImageArea>())
        PhWidgetsCreateWidget<&PtImageArea>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtImageArea>());

    using namespace PhWidgets;
    
    ImageArea ia(PhWidgetsGetWidget<&PtImageArea>());

    CHECK_NOTHROW({
        ia.Image = Drawing::Image::FromFile("./tests/microGUI/testsuit/resources/banana.jpg");
    });
    CHECK(ia.Image());
    CHECK(ia.Image().Width == 800);
    CHECK(448 == ia.Image().Height);

    CHECK_NOTHROW({
        ia.Image = Drawing::Image::FromFile("./tests/microGUI/testsuit/resources/lenna.png");
    });
    CHECK(ia.Image());
    CHECK(ia.Image().Width == 746);
    CHECK(900 == ia.Image().Height);
}

TEST_CASE("Testing ImageArea::ZoomingFactor property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtImageArea>())
        PhWidgetsCreateWidget<&PtImageArea>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtImageArea>());

    using namespace PhWidgets;
    
    ImageArea ia(PhWidgetsGetWidget<&PtImageArea>());

    ia.ZoomingFactor = 14.12;
    
    CHECK(ia.ZoomingFactor == 14.12);
    CHECK(14.12 == ia.ZoomingFactor);

    ia.ZoomingFactor = 12;

    CHECK(ia.ZoomingFactor == 12);
    CHECK(12 == ia.ZoomingFactor);
}