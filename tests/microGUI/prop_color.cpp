#include "./phwidgets_init.cpp"

#include "./testsuit.h"

#include <Basic.h>
#include <Color.h>
#include <photon/PtButton.h>


TEST_CASE("Testing Basic::Color property"){
    REQUIRE(PhWidgetsGetWidget<&PtButton>());

    using namespace PhWidgets;
    
    Basic widget(PhWidgetsGetWidget<&PtButton>());

    widget.Color = Colors::Blue;
    
    CHECK(widget.Color == Colors::Blue);
    CHECK(Colors::Blue == widget.Color);
}