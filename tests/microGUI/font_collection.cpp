#include "./phwidgets_init.cpp"

#include "./testsuit.h"

#include <Font.h>

const std::vector<int> fuuu(){return std::vector<int>();}

TEST_CASE("Testing FontCollections classes"){

    using namespace PhWidgets;
    
    InstalledFontCollection ifc;

    CHECK(ifc.Families.size() != 0);

    CHECK(ifc.Families().size() == ifc.Families.size());
}