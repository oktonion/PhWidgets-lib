#include "Font.h"



#include <cctype>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <cstring>

using namespace PhWidgets;

typedef std::vector<FontDetails> font_families_collection_type;


template<class T>
const typename T::size_type LevensteinDistance(const T &source,
                                         const T &target) {
    if (source.size() > target.size()) {
        return LevensteinDistance(target, source);
    }

    typedef typename T::size_type TSizeType;
    const TSizeType min_size = source.size(), max_size = target.size();
    std::vector<TSizeType> lev_dist(min_size + 1);

    for (TSizeType i = 0; i <= min_size; ++i) {
        lev_dist[i] = i;
    }

    for (TSizeType j = 1; j <= max_size; ++j) {
        TSizeType previous_diagonal = lev_dist[0], previous_diagonal_save;
        ++lev_dist[0];

        for (TSizeType i = 1; i <= min_size; ++i) {
            previous_diagonal_save = lev_dist[i];
            if (source[i - 1] == target[j - 1]) {
                lev_dist[i] = previous_diagonal;
            } else {
                lev_dist[i] = std::min(std::min(lev_dist[i - 1], lev_dist[i]), previous_diagonal) + 1;
            }
            previous_diagonal = previous_diagonal_save;
        }
    }

    return lev_dist[min_size];
}

FontDetails GetAnyFontFamily(const char *cname, int FontFamilyID)
{
    static font_families_collection_type families;
    int count = PfQueryFonts(PHFONT_ALL_SYMBOLS, FontFamilyID, NULL, 0);
    if(-1 == count)
        return FontDetails();

    if(families.size() != 1)
    {
        families.resize(count);
        FontDetails *data = &families.front();

        PfQueryFonts(PHFONT_ALL_SYMBOLS, FontFamilyID, data, count);

        std::string name = cname;
        
        {
            using namespace std;
            transform(name.begin(), name.end(), name.begin(), tolower);
        }

        std::map<font_families_collection_type::size_type, int> distance_map;

        for(font_families_collection_type::size_type i = 0; i < families.size(); ++i)
        {
            std::string ff_name(families[i].desc);
            
            {
                using namespace std;
                transform(ff_name.begin(), ff_name.end(), ff_name.begin(), tolower);
            }
            font_families_collection_type::size_type distance = LevensteinDistance(name, ff_name);
            distance_map[distance] = i;
        }

        if(distance_map.size())
        {
            FontDetails ff = families[distance_map.begin()->second];
            families.resize(1);
            families[0] = ff;
        }
    }
    
    return families[0];
}

static std::map<GenericFontFamilies::eGenericFontFamilies, FontDetails> & GetGenericFontFamily()
{
    static std::map<GenericFontFamilies::eGenericFontFamilies, FontDetails> gffname;
    if(gffname.size() == 0)
    {
        gffname[GenericFontFamilies::Monospace] = 
            GetAnyFontFamily("Courier", GenericFontFamilies::Monospace);
        gffname[GenericFontFamilies::SansSerif] = 
            GetAnyFontFamily("Arial Verdana", GenericFontFamilies::SansSerif);
        gffname[GenericFontFamilies::Serif] = 
            GetAnyFontFamily("Times", GenericFontFamilies::Serif);
    }
    return gffname;
}

const property<const std::vector<FontDetails>&>::
        bind_static<&FontCollection::FontCollectionDetail::getFamilies> FontCollection::Families;

const std::vector<FontDetails> & FontCollection::FontCollectionDetail::getFamilies()
{
        static font_families_collection_type families;
        int count = PfQueryFonts(PHFONT_ALL_SYMBOLS, PHFONT_ALL_FONTS, NULL, 0);
        if(-1 == count)
            return families;
        
        families.resize(count);
        FontDetails *data = &families.front();

        PfQueryFonts(PHFONT_ALL_SYMBOLS, PHFONT_ALL_FONTS, data, count);

        return families;
}

InstalledFontCollection::InstalledFontCollection():
    FontCollection()
{}

static FontDetails FindFontFamily(std::string name, font_families_collection_type ffamilies)
{
    if(name.length() == 0)
        throw(std::invalid_argument("FontFamily::Name is an empty string (\"\")."));

    typedef font_families_collection_type::size_type size_type;
    for(size_type i = 0; i < ffamilies.size(); ++i)
    {
        if(ffamilies[i].desc == name)
            return ffamilies[i];
    }

    throw(std::invalid_argument(name + " specifies a font that is not installed on the computer running the application."));
}


FontFamily::FontFamily(GenericFontFamilies::eGenericFontFamilies ffamily):
    _fdetails(GetGenericFontFamily()[ffamily]),
    Name(_fdetails.desc)
{
    if(Name.length() == 0)
        throw(std::invalid_argument("FontFamily::Name is an empty string (\"\")."));
}

FontFamily::FontFamily(const FontDetails &fdetails):
    _fdetails(fdetails),
    Name(_fdetails.desc)
{
    if(Name.length() == 0)
        throw(std::invalid_argument("FontFamily::Name is an empty string (\"\")."));
}

FontFamily::FontFamily(std::string name):
    _fdetails(FindFontFamily(name, InstalledFontCollection::Families)),
    Name(_fdetails.desc)
{
}

FontFamily::FontFamily(std::string name, const FontCollection &fcollection):
    _fdetails(FindFontFamily(name, FontCollection::Families)),
    Name(_fdetails.desc)
{
}

int FontFamily::GetLineSpacing(typedefs::font_style_bitmask fstyle) const
{
    return 0;//_fdetails.hisize - _fdetails.losize;
}

bool FontFamily::IsStyleAvailable(typedefs::font_style_bitmask fstyle) const
{
    return 0 != (_fdetails.flags & fstyle);
}

FontFamily::operator FontDetails() const
{
    return _fdetails;
}

FontDef::FontDef(const FontDef &other, typedefs::font_style_bitmask fstyle):
    _ffamily(other._ffamily)
{

}