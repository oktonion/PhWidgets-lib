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

    SUBCASE("BMP image test"){

        CHECK_NOTHROW(label.Image = Image::FromFile("./../service/resources/lenna.bmp"));

        CHECK(label.Image().Width == 512);
        CHECK(512 == label.Image().Height);
    }

    SUBCASE("PNG image test"){

        CHECK_NOTHROW(label.Image = Image::FromFile("./../service/resources/lenna.png"));

        CHECK(label.Image().Width == 746);
        CHECK(900 == label.Image().Height);
    }

    MESSAGE("Trying to load sexy banana into PhWidgets::Drawing::Image");

    SUBCASE("JPG image test"){

        CHECK_NOTHROW(label.Image = Image::FromFile("./../service/resources/banana.jpg"));

        CHECK(label.Image().Width == 800);
        CHECK(448 == label.Image().Height);
    }

    SUBCASE("GIF image test"){

        CHECK_NOTHROW(label.Image = Image::FromFile("./../service/resources/banana.gif"));

        CHECK(label.Image().Width == 800);
        CHECK(448 == label.Image().Height);
    }

    MESSAGE("Trying to load colorful marbles into PhWidgets::Drawing::Image");

    SUBCASE("PCX image test"){

        CHECK_NOTHROW(label.Image = Image::FromFile("./../service/resources/marbles.pcx"));

        CHECK(label.Image().Width == 1419);
        CHECK(1001 == label.Image().Height);
    }

    MESSAGE("Trying to load gorgeous girl into PhWidgets::Drawing::Image");

    SUBCASE("SGI image test"){

        CHECK_NOTHROW(label.Image = Image::FromFile("./../service/resources/girl.sgi"));

        CHECK(label.Image().Width == 768);
        CHECK(1024 == label.Image().Height);
    }
}