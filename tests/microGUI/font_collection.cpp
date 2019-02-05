#include "./phwidgets_init.cpp"

#include "./testsuit.h"

#include <Font.h>

TEST_CASE("Testing FontCollections classes"){

    using namespace PhWidgets;
    
    InstalledFontCollection ifc;

    CHECK(ifc.Families.size() != 0);
    CHECK(ifc.Families().size() == ifc.Families.size());
    CHECK(ifc.Families.begin() != ifc.Families.end());
    CHECK(ifc.Families.begin() == ifc.Families().begin());
    CHECK(ifc.Families().end() == ifc.Families.end());
    CHECK(ifc.Families().end() == ifc.Families.cend());
    CHECK(ifc.Families.cbegin() == ifc.Families().begin());
}