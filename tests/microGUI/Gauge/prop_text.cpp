

#include "./../testsuit/testsuit.h"

#include <Gauge.h>

#ifndef PH_WIDGETS_INIT_COMPLETED
static const int PhWidgetsPtInit = PtInit(NULL);
#define PH_WIDGETS_INIT_COMPLETED
#endif

TEST_CASE("Testing Gauge properties"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    

    using namespace PhWidgets;
    

    SUBCASE("Gauge Prefix property"){

        if (!PhWidgetsGetWidget<&PtWindow>())
            PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
        if (!PhWidgetsGetWidget<&PtGauge>())
            PhWidgetsCreateWidget<&PtGauge>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);

        REQUIRE(PhWidgetsGetWidget<&PtGauge>());
        
        Gauge gauge(PhWidgetsGetWidget<&PtGauge>());

        gauge.Prefix = "";

        CHECK(gauge.Prefix() == std::string(""));

        gauge.Prefix = "Missisipi 1";
        CHECK(gauge.Prefix() == std::string("Missisipi 1"));

        gauge.Prefix = "Missisipi 2";
        CHECK(std::string("Missisipi 2") == gauge.Prefix());
    }

    SUBCASE("Gauge Suffix property"){

        if (!PhWidgetsGetWidget<&PtWindow>())
            PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);
        if (!PhWidgetsGetWidget<&PtGauge>())
            PhWidgetsCreateWidget<&PtGauge>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);

        REQUIRE(PhWidgetsGetWidget<&PtGauge>());
        
        Gauge gauge(PhWidgetsGetWidget<&PtGauge>());

        gauge.Suffix = "";

        CHECK(gauge.Suffix() == std::string(""));

        gauge.Suffix = "Missisipi 1";
        CHECK(gauge.Suffix() == std::string("Missisipi 1"));

        gauge.Suffix = "Missisipi 2";
        CHECK(std::string("Missisipi 2") == gauge.Suffix());
    }
}