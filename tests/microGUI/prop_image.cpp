#include "./1phwidgets_init.cpp"

#include "./testsuit.h"

#include <Label.h>
#include <photon/PxImage.h>


TEST_CASE("Testing Label::Image property") {
    REQUIRE(PhWidgetsGetWidget<&PtLabel>());
    
    using namespace PhWidgets;
    using Drawing::Image;

    Label label(PhWidgetsGetWidget<&PtLabel>());

    //label.Type = LabelType::Image;

    //REQUIRE(label.Type == LabelType::Image);

    CHECK_THROWS(Image::FromFile("there/is/no/such/file.porn"));

    SUBCASE("BMP image test: Trying to load beautiful Lenna into PhWidgets::Drawing::Image"){

        CHECK_NOTHROW({
        	
        	label.Image = Image::FromFile("./tests/service/resources/lenna.bmp");
        });

        CHECK(label.Image());

        CHECK(label.Image().Width == 512);
        CHECK(512 == label.Image().Height);
    }

    SUBCASE("PNG image test: Trying to load beautiful Lenna into PhWidgets::Drawing::Image"){

        CHECK_NOTHROW({

            label.Image = Image::FromFile("./tests/service/resources/lenna.png");
        });

        CHECK(label.Image());

        CHECK(label.Image().Width == 746);
        CHECK(900 == label.Image().Height);
    }

    SUBCASE("JPG image test: Trying to load sexy banana into PhWidgets::Drawing::Image"){

        CHECK_NOTHROW({

            label.Image = Image::FromFile("./tests/service/resources/banana.jpg");
        });

        CHECK(label.Image());

        CHECK(label.Image().Width == 800);
        CHECK(448 == label.Image().Height);
    }

    SUBCASE("GIF image test: Trying to load sexy banana into PhWidgets::Drawing::Image"){

        CHECK_NOTHROW({
            
            label.Image = Image::FromFile("./tests/service/resources/banana.gif");
        });

        CHECK(label.Image());
        
        CHECK(label.Image().Width == 800);
        CHECK(448 == label.Image().Height);
    }

    SUBCASE("PCX image test: Trying to load colorful marbles into PhWidgets::Drawing::Image"){

        CHECK_NOTHROW({

            label.Image = Image::FromFile("./tests/service/resources/marbles.pcx");
        });

        CHECK(label.Image());
        
        CHECK(label.Image().Width == 1419);
        CHECK(1001 == label.Image().Height);
    }

    SUBCASE("SGI image test: Trying to load gorgeous girl into PhWidgets::Drawing::Image"){

        CHECK_NOTHROW({

            label.Image = Image::FromFile("./tests/service/resources/girl.sgi");
        });

        CHECK(label.Image());
        
        CHECK(label.Image().Width == 768);
        CHECK(1024 == label.Image().Height);
    }
}