#include "Font.h"

#include <map>

namespace PhWidgets
{
    typedef std::vector<FontDetails> font_families_collection_type;

    std::map<GenericFontFamilies::eGenericFontFamilies, std::string> & GetGenericFontFamilyName()
    {
        static std::map<GenericFontFamilies::eGenericFontFamilies, std::string> gffname;
        return gffname;
    }

    static const font_families_collection_type GetFontFamilies()
    {
        font_families_collection_type families;
        int count = PfQueryFonts(PHFONT_ALL_SYMBOLS, PHFONT_ALL_FONTS, NULL, 0);

        families.resize(count);
        FontDetails *data = &families.front();

        PfQueryFonts(PHFONT_ALL_SYMBOLS, PHFONT_ALL_FONTS, data, count);

        for(font_families_collection_type::size_type i = 0; i < families.size(); ++i)
        {
            switch(families[i].flags)
            {
            case GenericFontFamilies::Monospace:
                GetGenericFontFamilyName()[GenericFontFamilies::Monospace] = families[i].stem;
                break;
            case GenericFontFamilies::SansSerif:
                GetGenericFontFamilyName()[GenericFontFamilies::SansSerif] = families[i].stem;
                break;      
            case GenericFontFamilies::Serif:
                GetGenericFontFamilyName()[GenericFontFamilies::Serif] = families[i].stem;
                break;           
            }
        }

        return families;
    }

    const std::vector<FontDetails> FontCollection::Families = GetFontFamilies();
}

using namespace PhWidgets;

FontFamily::FontFamily(GenericFontFamilies::eGenericFontFamilies ffamily):
    Name(GetGenericFontFamilyName()[ffamily])
{

}

FontFamily::FontFamily(std::string name):
    Name(name)
{

}

FontFamily::FontFamily(std::string name, FontCollection fcollection):
    Name(name)
{

}
