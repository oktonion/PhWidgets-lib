#include "./1phwidgets_init.cpp"

#include "./testsuit.h"

#include <Label.h>
#include <photon/PtWindow.h>


TEST_CASE("Testing Label::Image property") {
    REQUIRE(PhWidgetsGetWidget<&PtLabel>());
    
    using namespace PhWidgets;
    using Drawing::Image;

    Label label(PhWidgetsGetWidget<&PtLabel>());

    MESSAGE("Trying to load beautiful Lenna into PhWidgets::Drawing::Image");
    Image lenna = Image::FromFile("./../service/resources/lenna1.bmp");

    CHECK_NOTHROW(label.Image = lenna);

    CHECK(label.Image().Width == 512);
    CHECK(512 == label.Image().Height);
}