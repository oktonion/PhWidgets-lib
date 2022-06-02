

#include "./../testsuit/testsuit.h"

#include <Gauge.h>

#ifndef PH_WIDGETS_INIT_COMPLETED
static const int PhWidgetsPtInit = PtInit(NULL);
#define PH_WIDGETS_INIT_COMPLETED
#endif

TEST_CASE("Testing Gauge properties"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    

    using namespace PhWidgets;

    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
    if (!PhWidgetsGetWidget<&PtGauge>())
        PhWidgetsCreateWidget<&PtGauge>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);

    REQUIRE(PhWidgetsGetWidget<&PtGauge>());

    SUBCASE("Gauge::Value property"){

        Gauge gauge(PhWidgetsGetWidget<&PtGauge>());

        CHECK(0 == gauge.Value.get());

        CHECK(gauge.Value == 0);

        gauge.Value = 20;
        CHECK(gauge.Value == 20);

        gauge.Value++;;
        CHECK(gauge.Value == 21);
    }

    SUBCASE("Gauge::Prefix property"){

        Gauge gauge(PhWidgetsGetWidget<&PtGauge>());

        gauge.Prefix = "";

        CHECK(gauge.Prefix() == std::string(""));

        gauge.Prefix = "Missisipi 1";
        CHECK(gauge.Prefix() == std::string("Missisipi 1"));

        gauge.Prefix = "Missisipi 2";
        CHECK(std::string("Missisipi 2") == gauge.Prefix());
    }

    SUBCASE("Gauge::Suffix property"){
        
        Gauge gauge(PhWidgetsGetWidget<&PtGauge>());

        gauge.Suffix = "";

        CHECK(gauge.Suffix() == std::string(""));

        gauge.Suffix = "Missisipi 1";
        CHECK(gauge.Suffix() == std::string("Missisipi 1"));

        gauge.Suffix = "Missisipi 2";
        CHECK(std::string("Missisipi 2") == gauge.Suffix());
    }

    SUBCASE("Gauge::Font property"){

        using PhWidgets::Drawing::Font;
        using PhWidgets::Drawing::GenericFontFamilies;

        Gauge gauge(PhWidgetsGetWidget<&PtGauge>());

        Font serif_font_10(GenericFontFamilies::Serif, 10); 
        Font original_font = gauge.Font;

        CHECK_MESSAGE(
            gauge.Font == original_font,
            gauge.Font().Name + " != " + original_font.Name
        );

        gauge.Font = serif_font_10;
        CHECK_MESSAGE(
            gauge.Font != original_font,
            gauge.Font().Name + " == " + original_font.Name
        );
        CHECK_MESSAGE(
            gauge.Font == serif_font_10,
            gauge.Font().Name + " != " + serif_font_10.Name
        );

        gauge.Font = original_font;
        CHECK_MESSAGE(
            gauge.Font != serif_font_10,
            gauge.Font().Name + " == " + serif_font_10.Name
        );
        CHECK_MESSAGE(
            gauge.Font == original_font,
            gauge.Font().Name + " != " + original_font.Name
        );
    }
}