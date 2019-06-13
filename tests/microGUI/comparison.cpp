#include "./phwidgets_init.cpp"

#include "./testsuit.h"

#include <Widget.h>
#include <photon/PtWindow.h>
#include <photon/PtButton.h>


TEST_CASE("Testing comparison of two Widgets") {
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

    CHECK(w1 < w2);
    CHECK(w2 > w1);
}