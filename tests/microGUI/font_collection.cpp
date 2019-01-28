#include "./phwidgets_init.cpp"

#include "./testsuit.h"

#include <Font.h>


TEST_CASE("Testing FontCollections classes"){

    using namespace PhWidgets;
    
    InstalledFontCollection ifc;

    CHECK(ifc.Families().size() != 0);
}