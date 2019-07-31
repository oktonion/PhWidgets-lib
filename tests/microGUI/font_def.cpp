#include "./phwidgets_init.cpp"

#include "./testsuit.h"

#include <Font.h>


TEST_CASE("Testing Font class"){

    using namespace PhWidgets::Drawing;
    
    CHECK_THROWS(Font fd(0)); // should throw std::invalid_argument

    Font fd(GenericFontFamilies::Serif, 10);

    CHECK(fd.Name != "");
    CHECK(fd.Size == 10);
    CHECK(fd.Italic == false);
    CHECK(fd.Bold == false);
    CHECK(fd.Family == GenericFontFamilies::Serif);

    SUBCASE("Testing copy of Font"){

        Font fd2 = fd;

        CHECK("" != fd2.Name);
        CHECK(10 == fd2.Size);
        CHECK(false == fd2.Italic);
        CHECK(false == fd2.Bold);
        CHECK(GenericFontFamilies::Serif == fd2.Family);
        CHECK(fd2 == fd);
        CHECK((fd < fd2) == false);
    }

    SUBCASE("Testing other Font"){

        Font fd2(GenericFontFamilies::Serif, 13, FontStyle::Bold | FontStyle::Italic);

        CHECK("" != fd2.Name);
        CHECK(13 == fd2.Size);
        CHECK(true == fd2.Italic);
        CHECK(true == fd2.Bold);
        CHECK(GenericFontFamilies::Serif == fd2.Family);
        CHECK(fd2 != fd);
        CHECK((fd < fd2) == true);
    }
}