#include "./phwidgets_init.cpp"

#include "./testsuit.h"

#include <Font.h>


TEST_CASE("Testing FontDef class"){

    using namespace PhWidgets;
    
    CHECK_THROWS(FontDef fd(0)); // should throw std::invalid_argument

    FontDef fd(GenericFontFamilies::Serif, 10);

    CHECK(fd.Name != "");
    CHECK(fd.Size == 10);
    CHECK(fd.Italic == false);
    CHECK(fd.Bold == false);
    CHECK(fd.Family == GenericFontFamilies::Serif);
}