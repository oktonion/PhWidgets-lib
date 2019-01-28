#include "Font.h"

#include <cctype>
#include <map>
#include <algorithm>

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

template<GenericFontFamilies::eGenericFontFamilies FontFamilyID>
FontDetails GetGenericFontFamily(const char *cname)
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
            std::string ff_name(families[i].stem);
            
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

static std::map<GenericFontFamilies::eGenericFontFamilies, std::string> & GetGenericFontFamilyName()
{
    static std::map<GenericFontFamilies::eGenericFontFamilies, std::string> gffname;
    if(gffname.size() == 0)
    {
        gffname[GenericFontFamilies::Monospace] = 
            GetGenericFontFamily<GenericFontFamilies::Monospace>("Courier").stem;
        gffname[GenericFontFamilies::SansSerif] = 
            GetGenericFontFamily<GenericFontFamilies::SansSerif>("Arial Verdana").stem;
        gffname[GenericFontFamilies::Serif] = 
            GetGenericFontFamily<GenericFontFamilies::Serif>("Times").stem;
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
