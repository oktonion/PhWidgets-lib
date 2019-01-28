#include "./phwidgets_init.cpp"

#include "./testsuit.h"

#include <Font.h>


TEST_CASE("Testing FontCollection class"){

    using namespace PhWidgets;
    
    CHECK(FontCollection::Families().size() != 0);
}