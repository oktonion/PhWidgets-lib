#include "./phwidgets_init.cpp"

#include "./testsuit.h"

#include <Widget.h>
#include <photon/PtWindow.h>


TEST_CASE("Testing swap idiom of Widget") {
    REQUIRE(PhWidgetsGetWidget<&PtWindow>());
    
    using namespace PhWidgets;

    Widget 
        widget1(PhWidgetsGetWidget<&PtWindow>()),
        widget2(PhWidgetsGetWidget<&PtWindow>());

    Widget tmp = widget1;

    CHECK(tmp == widget1);
    CHECK(widget == tmp);
    CHECK(widget2 != tmp);
    CHECK(tmp != widget2);
    CHECK(widget2 != widget1);
    CHECK(widget1 != widget2);

    widget2.swap(wiget1);

    CHECK(tmp != widget1);
    CHECK(widget != tmp);
    CHECK(widget2 == tmp);
    CHECK(tmp == widget2);
    CHECK(widget2 != widget1);
    CHECK(widget1 != widget2);
}