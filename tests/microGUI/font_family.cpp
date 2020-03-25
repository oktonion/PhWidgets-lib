#include "./1phwidgets_init.cpp"

#include "./testsuit.h"

#include <Drawing/Font.h>

#include <algorithm>
#include <vector>


TEST_CASE("Testing FontFamily class"){

    using namespace PhWidgets::Drawing;
    
    REQUIRE(FontCollection::Families().size() != 0);

    SUBCASE("Generic Font Family constructor"){

        FontFamily ff_sans(GenericFontFamilies::SansSerif);

        CHECK(ff_sans.Name.length());

        std::string 
            ff_name(ff_sans.Name),
            check_name("verdana");
        CHECK(LevensteinDistance(ff_name, check_name) / (ff_name.length() + check_name.length()) < 0.1);

        FontFamily ff_mono(GenericFontFamilies::Monospace);

        ff_name = std::string(ff_mono.Name);
        check_name = "courier";
        CHECK(LevensteinDistance(ff_name, check_name) / (ff_name.length() + check_name.length()) < 0.1);

        FontFamily ff_serif(GenericFontFamilies::Serif);

        ff_name = std::string(ff_serif.Name);
        check_name = "times";
        CHECK(LevensteinDistance(ff_name, check_name) / (ff_name.length() + check_name.length()) < 0.1);
    }

    SUBCASE("Font Family constructor from name"){
        
        CHECK_THROWS(FontFamily ff("NLH")); // should throw std::invalid_argument
        
        InstalledFontCollection ifc;
        CHECK_NOTHROW(FontFamily ff(ifc.Families()[0].desc));

        FontFamily ff(ifc.Families()[0].desc);

        REQUIRE(ff.Name == "arial");
        CHECK(ff.IsStyleAvailable(FontStyle::Bold) == true);
        CHECK(ff.IsStyleAvailable(FontStyle::Italic) == true);
        CHECK(ff.IsStyleAvailable(FontStyle::Antialias) == false);
    }
}