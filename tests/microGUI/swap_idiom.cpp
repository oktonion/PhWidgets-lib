#include "./1phwidgets_init.cpp"

#include "./testsuit.h"

#include <Widget.h>
#include <Button.h>
#include <photon/PtWindow.h>
#include <photon/PtButton.h>


TEST_CASE("Testing swap idiom of Widget") {
    REQUIRE(PhWidgetsGetWidget<&PtWindow>());
    REQUIRE(PhWidgetsGetWidget<&PtButton>());
    
    using namespace PhWidgets;

    Widget 
        widget1(PhWidgetsGetWidget<&PtWindow>());
    Button
        widget2(PhWidgetsGetWidget<&PtButton>());

    Widget tmp = widget1;

    CHECK(tmp == widget1);
    CHECK(widget1 == tmp);
    CHECK(widget2 != tmp);
    CHECK(tmp != widget2);
    CHECK(widget2 != widget1);
    CHECK(widget1 != widget2);

    widget2.swap(widget1);

    CHECK(tmp != widget1);
    CHECK(widget1 != tmp);
    CHECK(widget2 == tmp);
    CHECK(tmp == widget2);
    CHECK(widget2 != widget1);
    CHECK(widget1 != widget2);
}