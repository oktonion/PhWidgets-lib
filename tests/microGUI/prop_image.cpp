#include "./phwidgets_init.cpp"

#include "./testsuit.h"

#include <Label.h>
#include <photon/PtWindow.h>


TEST_CASE("Testing Label::Image property") {
    REQUIRE(PhWidgetsGetWidget<&PtLabel>());
    
    using namespace PhWidgets;
    using Drawing::Image;

    Label label(PhWidgetsGetWidget<&PtLabel>());

    label.Image = Image::LoadFromFile("resources/img.bmp");
}