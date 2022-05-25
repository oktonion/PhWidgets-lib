

#include "./testsuit/testsuit.h"

#include <Drawing/Font.h>

#ifndef PH_WIDGETS_INIT_COMPLETED
static const int PhWidgetsPtInit = PtInit(NULL);
#define PH_WIDGETS_INIT_COMPLETED
#endif

TEST_CASE("Testing FontCollections classes"){
    REQUIRE_MESSAGE(0 == PhWidgetsPtInit, "Photon App requires connection to Photon server.");
    

    using PhWidgets::Drawing::InstalledFontCollection;
    
    InstalledFontCollection ifc;

    CHECK(ifc.Families.size() != 0);
    CHECK(ifc.Families().size() == ifc.Families.size());
    CHECK(ifc.Families.begin() != ifc.Families.end());
    CHECK(ifc.Families.begin() == ifc.Families().begin());
    CHECK(ifc.Families().end() == ifc.Families.end());
    CHECK(ifc.Families().end() == ifc.Families.cend());
    CHECK(ifc.Families.cbegin() == ifc.Families().begin());
}