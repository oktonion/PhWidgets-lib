

#include "./testsuit/testsuit.h"

#include <Basic.h>
#include <Button.h>
#include <ComboBox.h>
#include <ImageArea.h>
#include <Label.h>

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

TEST_CASE("Testing Basic::BevelColor property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtButton>())
        PhWidgetsCreateWidget<&PtButton>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtButton>());

    using namespace PhWidgets;
    
    Basic widget(PhWidgetsGetWidget<&PtButton>());

    widget.BevelColor = Drawing::Colors::Blue;
    
    CHECK(widget.BevelColor == Drawing::Colors::Blue);
    CHECK(Drawing::Colors::Blue == widget.BevelColor);

    widget.BevelColor = Pg_BLACK;

    CHECK(widget.BevelColor == Pg_BLACK);
    CHECK(Pg_BLACK == widget.BevelColor);
}

TEST_CASE("Testing Basic::DarkBevelColor property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtButton>())
        PhWidgetsCreateWidget<&PtButton>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtButton>());

    using namespace PhWidgets;
    
    Basic widget(PhWidgetsGetWidget<&PtButton>());

    widget.DarkBevelColor = Drawing::Colors::Blue;
    
    CHECK(widget.DarkBevelColor == Drawing::Colors::Blue);
    CHECK(Drawing::Colors::Blue == widget.DarkBevelColor);

    widget.DarkBevelColor = Pg_BLACK;

    CHECK(widget.DarkBevelColor == Pg_BLACK);
    CHECK(Pg_BLACK == widget.DarkBevelColor);
}

TEST_CASE("Testing Basic::DarkFillColor property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtButton>())
        PhWidgetsCreateWidget<&PtButton>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtButton>());

    using namespace PhWidgets;
    
    Basic widget(PhWidgetsGetWidget<&PtButton>());

    widget.DarkFillColor = Drawing::Colors::Blue;
    
    CHECK(widget.DarkFillColor == Drawing::Colors::Blue);
    CHECK(Drawing::Colors::Blue == widget.DarkFillColor);

    widget.DarkFillColor = Pg_BLACK;

    CHECK(widget.DarkFillColor == Pg_BLACK);
    CHECK(Pg_BLACK == widget.DarkFillColor);
}

TEST_CASE("Testing Basic::LightBevelColor property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtButton>())
        PhWidgetsCreateWidget<&PtButton>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtButton>());

    using namespace PhWidgets;
    
    Basic widget(PhWidgetsGetWidget<&PtButton>());

    widget.LightBevelColor = Drawing::Colors::Blue;
    
    CHECK(widget.LightBevelColor == Drawing::Colors::Blue);
    CHECK(Drawing::Colors::Blue == widget.LightBevelColor);

    widget.LightBevelColor = Pg_BLACK;

    CHECK(widget.LightBevelColor == Pg_BLACK);
    CHECK(Pg_BLACK == widget.LightBevelColor);
}

TEST_CASE("Testing Basic::LightFillColor property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtButton>())
        PhWidgetsCreateWidget<&PtButton>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtButton>());

    using namespace PhWidgets;
    
    Basic widget(PhWidgetsGetWidget<&PtButton>());

    widget.LightFillColor = Drawing::Colors::Blue;
    
    CHECK(widget.LightFillColor == Drawing::Colors::Blue);
    CHECK(Drawing::Colors::Blue == widget.LightFillColor);

    widget.LightFillColor = Pg_BLACK;

    CHECK(widget.LightFillColor == Pg_BLACK);
    CHECK(Pg_BLACK == widget.LightFillColor);
}

TEST_CASE("Testing Basic::OutlineColor property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtButton>())
        PhWidgetsCreateWidget<&PtButton>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtButton>());

    using namespace PhWidgets;
    
    Basic widget(PhWidgetsGetWidget<&PtButton>());

    widget.OutlineColor = Drawing::Colors::Blue;
    
    CHECK(widget.OutlineColor == Drawing::Colors::Blue);
    CHECK(Drawing::Colors::Blue == widget.OutlineColor);

    widget.OutlineColor = Pg_BLACK;

    CHECK(widget.OutlineColor == Pg_BLACK);
    CHECK(Pg_BLACK == widget.OutlineColor);
}

TEST_CASE("Testing Basic::MarginHeight property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtButton>())
        PhWidgetsCreateWidget<&PtButton>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtButton>());

    using namespace PhWidgets;
    
    Basic widget(PhWidgetsGetWidget<&PtButton>());

    unsigned short wh = widget.MarginHeight;

    wh++;

    CHECK(widget.MarginHeight != wh);

    widget.MarginHeight = wh;

    CHECK(wh == widget.MarginHeight);
}

TEST_CASE("Testing Basic::MarginWidth property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtButton>())
        PhWidgetsCreateWidget<&PtButton>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtButton>());

    using namespace PhWidgets;
    
    Basic widget(PhWidgetsGetWidget<&PtButton>());

    unsigned short ww = widget.MarginWidth;

    ww++;

    CHECK(widget.MarginWidth != ww);

    widget.MarginWidth = ww;

    CHECK(ww == widget.MarginWidth);
}

TEST_CASE("Testing Basic::BasicFlags property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtButton>())
        PhWidgetsCreateWidget<&PtButton>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtButton>());

    using namespace PhWidgets;
    
    Basic widget(PhWidgetsGetWidget<&PtButton>());

    REQUIRE(widget.BasicFlags.has(Basic::Flags::Basic::all) == true);
}


TEST_CASE("Testing Button::ArmColor property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtButton>())
        PhWidgetsCreateWidget<&PtButton>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtButton>());

    using namespace PhWidgets;
    
    Button button(PhWidgetsGetWidget<&PtButton>());

    button.ArmColor = Drawing::Colors::Blue;
    
    CHECK(button.ArmColor == Drawing::Colors::Blue);
    CHECK(Drawing::Colors::Blue == button.ArmColor);

    button.ArmColor = Pg_BLACK;

    CHECK(button.ArmColor == Pg_BLACK);
    CHECK(Pg_BLACK == button.ArmColor);
}

TEST_CASE("Testing Button::ArmFill property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtButton>())
        PhWidgetsCreateWidget<&PtButton>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtButton>());

    using namespace PhWidgets;
        
    Button button(PhWidgetsGetWidget<&PtButton>());

    if (!button.ArmFill)
    {
        CHECK(button.ArmFill == false);
        button.ArmColor = Drawing::Colors::Blue;    
        button.ArmFill = true;
        CHECK(button.ArmColor == Drawing::Colors::Blue);
    }        
    
    REQUIRE(button.ArmFill);
    CHECK(button.ArmFill == true);
    button.ArmFill = false;
    CHECK(false == button.ArmFill);
}


TEST_CASE("Testing ImageArea::GridColor property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtImageArea>())
        PhWidgetsCreateWidget<&PtImageArea>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtImageArea>());

    using namespace PhWidgets;
    
    ImageArea ia(PhWidgetsGetWidget<&PtImageArea>());

    ia.GridColor = Drawing::Colors::Blue;
    
    CHECK(ia.GridColor == Drawing::Colors::Blue);
    CHECK(Drawing::Colors::Blue == ia.GridColor);

    ia.GridColor = Pg_BLACK;

    CHECK(ia.GridColor == Pg_BLACK);
    CHECK(Pg_BLACK == ia.GridColor);
}


TEST_CASE("Testing Label::BalloonColor property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtLabel>())
        PhWidgetsCreateWidget<&PtLabel>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtLabel>());

    using namespace PhWidgets;
    
    Label label(PhWidgetsGetWidget<&PtLabel>());

    label.BalloonColor = Drawing::Colors::Blue;
    
    CHECK(label.BalloonColor == Drawing::Colors::Blue);
    CHECK(Drawing::Colors::Blue == label.BalloonColor);

    label.BalloonColor = Pg_BLACK;

    CHECK(label.BalloonColor == Pg_BLACK);
    CHECK(Pg_BLACK == label.BalloonColor);
}

TEST_CASE("Testing Label::BalloonFillColor property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtLabel>())
        PhWidgetsCreateWidget<&PtLabel>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtLabel>());

    using namespace PhWidgets;
    
    Label label(PhWidgetsGetWidget<&PtLabel>());

    label.BalloonFillColor = Drawing::Colors::Blue;
    
    CHECK(label.BalloonFillColor == Drawing::Colors::Blue);
    CHECK(Drawing::Colors::Blue == label.BalloonFillColor);

    label.BalloonFillColor = Pg_BLACK;

    CHECK(label.BalloonFillColor == Pg_BLACK);
    CHECK(Pg_BLACK == label.BalloonFillColor);
}

TEST_CASE("Testing Label::BalloonFillColor property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtLabel>())
        PhWidgetsCreateWidget<&PtLabel>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtLabel>());

    using namespace PhWidgets;

    Label label(PhWidgetsGetWidget<&PtLabel>());

    label.BalloonPosition = BalloonPosition::Inplace;
    CHECK(label.BalloonPosition == BalloonPosition::Inplace);
    CHECK(BalloonPosition::Inplace == label.BalloonPosition);

    label.BalloonPosition = BalloonPosition::Top;
    CHECK(label.BalloonPosition == BalloonPosition::Top);
    CHECK(BalloonPosition::Top == label.BalloonPosition);

    label.BalloonPosition = BalloonPosition::Left;
    CHECK(label.BalloonPosition == BalloonPosition::Left);
    CHECK(BalloonPosition::Left == label.BalloonPosition);

    label.BalloonPosition = BalloonPosition::Right;
    CHECK(label.BalloonPosition == BalloonPosition::Right);
    CHECK(BalloonPosition::Right == label.BalloonPosition);

    label.BalloonPosition = BalloonPosition::Bottom;
    CHECK(label.BalloonPosition == BalloonPosition::Bottom);
    CHECK(BalloonPosition::Bottom == label.BalloonPosition);
}

TEST_CASE("Testing Label::UnderlineColor1 property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtLabel>())
        PhWidgetsCreateWidget<&PtLabel>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtLabel>());

    using namespace PhWidgets;
    
    Label label(PhWidgetsGetWidget<&PtLabel>());

    label.UnderlineColor1 = Drawing::Colors::Blue;
    
    CHECK(label.UnderlineColor1 == Drawing::Colors::Blue);
    CHECK(Drawing::Colors::Blue == label.UnderlineColor1);

    label.UnderlineColor1 = Pg_BLACK;

    CHECK(label.UnderlineColor1 == Pg_BLACK);
    CHECK(Pg_BLACK == label.UnderlineColor1);
}

TEST_CASE("Testing Label::UnderlineColor2 property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtLabel>())
        PhWidgetsCreateWidget<&PtLabel>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtLabel>());

    using namespace PhWidgets;
    
    Label label(PhWidgetsGetWidget<&PtLabel>());

    label.UnderlineColor2 = Drawing::Colors::Blue;
    
    CHECK(label.UnderlineColor2 == Drawing::Colors::Blue);
    CHECK(Drawing::Colors::Blue == label.UnderlineColor2);

    label.UnderlineColor2 = Pg_BLACK;

    CHECK(label.UnderlineColor2 == Pg_BLACK);
    CHECK(Pg_BLACK == label.UnderlineColor2);
}

TEST_CASE("Testing Label::UnderlineType property"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    
    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtLabel>())
        PhWidgetsCreateWidget<&PtLabel>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);
        
    REQUIRE(PhWidgetsGetWidget<&PtLabel>());

    using namespace PhWidgets;

    Label label(PhWidgetsGetWidget<&PtLabel>());

    label.UnderlineType = UnderlineType::NoUline;
    CHECK(label.UnderlineType == UnderlineType::NoUline);
    CHECK(UnderlineType::NoUline == label.UnderlineType);

    label.UnderlineType = UnderlineType::DoubleUline;
    CHECK(label.UnderlineType == UnderlineType::DoubleUline);
    CHECK(UnderlineType::DoubleUline == label.UnderlineType);

    label.UnderlineType = UnderlineType::SingleUline;
    CHECK(label.UnderlineType == UnderlineType::SingleUline);
    CHECK(UnderlineType::SingleUline == label.UnderlineType);

    label.UnderlineType = UnderlineType::UlineEtchedIn;
    CHECK(label.UnderlineType == UnderlineType::UlineEtchedIn);
    CHECK(UnderlineType::UlineEtchedIn == label.UnderlineType);

    label.UnderlineType = UnderlineType::UlineEtchedOut;
    CHECK(label.UnderlineType == UnderlineType::UlineEtchedOut);
    CHECK(UnderlineType::UlineEtchedOut == label.UnderlineType);
}