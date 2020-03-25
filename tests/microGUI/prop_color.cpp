#include "./1phwidgets_init.cpp"

#include "./testsuit/testsuit.h"

#include <Basic.h>
#include <Drawing/Color.h>
#include <photon/PtButton.h>


TEST_CASE("Testing Basic::Color property"){
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