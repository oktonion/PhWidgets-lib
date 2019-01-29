#include "./phwidgets_init.cpp"

#include "./testsuit.h"

#include <Font.h>


TEST_CASE("Testing FontDef class"){

    using namespace PhWidgets;
    
    CHECK_THROWS(FontDef fd(0)); // should throw std::invalid_argument

    FontDef fd(0);
}