

#include "./testsuit/testsuit.h"

#include <Widget.h>
#include <photon/PtWindow.h>
#include <photon/PtButton.h>

#ifndef PH_WIDGETS_INIT_COMPLETED
static const int PhWidgetsPtInit = PtInit(NULL);
#define PH_WIDGETS_INIT_COMPLETED
#endif


TEST_CASE("Testing comparison of two Widgets") {
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");

    if (!PhWidgetsGetWidget<&PtWindow>())
        PhWidgetsCreateWidget<&PtWindow>(Pt_NO_PARENT, 0, NULL);

    if (!PhWidgetsGetWidget<&PtButton>())
        PhWidgetsCreateWidget<&PtButton>(PhWidgetsGetWidget<&PtWindow>(), 0, NULL);

    REQUIRE(PhWidgetsGetWidget<&PtWindow>());
    REQUIRE(PhWidgetsGetWidget<&PtButton>());
    
    using namespace PhWidgets;

    Widget 
        w1(PhWidgetsGetWidget<&PtWindow>()),
        w2(PhWidgetsGetWidget<&PtButton>());

    Widget w1_ = w1;

    CHECK(w1_ == w1);
    CHECK(w1 == w1_);
    CHECK(w1 != w2);
    CHECK(w2 != w1);

    CHECK_FALSE(w1_ != w1);
    CHECK_FALSE(w1 != w1_);
    CHECK_FALSE(w1 == w2);
    CHECK_FALSE(w2 == w1);

    CHECK_FALSE(w1 > w1);
    CHECK_FALSE(w2 > w2);
    CHECK_FALSE(w1 < w1);
    CHECK_FALSE(w2 < w2);

    CHECK(w1 >= w1);
    CHECK(w2 >= w2);
    CHECK(w1 <= w1);
    CHECK(w2 <= w2);

    if(w1 <= w2)
    {
        CHECK(w1 <= w2);
        CHECK(w2 >= w1);
    }
    if(w1 >= w2)
    {
        CHECK(w1 >= w2);
        CHECK(w2 <= w1);
    }

    if(w1 < w2)
    {
        CHECK_MESSAGE(((w1 <= w2) && (w1 < w2)), "(w1 <= w2) && (w1 < w2)");
        CHECK_MESSAGE(((w2 >= w1) && (w2 > w1)), "(w2 >= w1) && (w2 > w1)");
        CHECK_FALSE(w1 > w2);
        CHECK_FALSE(w2 == w1);
    }
    if(w1 > w2)
    {
        CHECK_MESSAGE(((w1 >= w2) && (w1 > w2)), "(w1 >= w2) && (w1 > w2)");
        CHECK_MESSAGE(((w2 <= w1) && (w2 < w1)), "(w2 <= w1) && (w2 < w1)");
        CHECK_FALSE(w1 < w2);
        CHECK_FALSE(w1 == w2);
    }
}