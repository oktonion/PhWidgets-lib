#include "Font.h"


#include <exception>
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
    _name(_fdetails.desc),
    Name(_name)
{
    if(Name.length() == 0)
        throw(std::invalid_argument("FontFamily::Name is an empty string (\"\")."));
}

FontFamily::FontFamily(const FontDetails &fdetails):
    _fdetails(fdetails),
    _name(_fdetails.desc),
    Name(_name)
{
    if(Name.length() == 0)
        throw(std::invalid_argument("FontFamily::Name is an empty string (\"\")."));
}

FontFamily::FontFamily(std::string name):
    _fdetails(FindFontFamily(name, InstalledFontCollection::Families)),
    _name(_fdetails.desc),
    Name(_name)
{
}

FontFamily::FontFamily(std::string name, const FontCollection &fcollection):
    _fdetails(FindFontFamily(name, FontCollection::Families)),
    _name(_fdetails.desc),
    Name(_name)
{
}

FontFamily::FontFamily(const FontFamily &other):
    _fdetails(other._fdetails),
    _name(other._name),
    Name(_name)
{

}

FontFamily & FontFamily::operator=(const FontFamily &other)
{
    if(&other != this)
    {
        _fdetails = other._fdetails;
        _name = other._name;
    }

    return *this;
}

bool FontFamily::operator==(const FontFamily &other) const
{
    using namespace std;
    return (0 == memcmp(&_fdetails, &other._fdetails, sizeof(FontDetails)));
}

bool FontFamily::operator!=(const FontFamily &other) const
{
    return !(*this == other);
}

bool FontFamily::operator<(const FontFamily &other) const
{
    using namespace std;
    return memcmp(&_fdetails, &other._fdetails, sizeof(FontDetails));
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
    Bold(_bold),
    Family(_ffamily),
    Height(_height),
    Italic(_italic),
    Name(_fname),
    Size(_size),
    _ffamily(other._ffamily)
{
    // get other fonts pretty name:
    const char *fdesc = PfFontDescription(other._fid);

    // get other fonts flags:
    //std::uint32_t fflags = PfFontFlags(&other._fid);

    // get other fonts point size:
    std::uint32_t fpoint_size = PfFontSize(other._fid);

    // generate new font name with new flags:
    //char fname_buf[MAX_FONT_TAG]; 
    //PfGenerateFontName(fdesc, fstyle, fpoint_size, fname_buf);

    // get new font ID
    font_id_type fid = PfFindFont(fdesc, fstyle, fpoint_size);

    if(NULL == fid)
        throw(std::invalid_argument(std::string(fdesc) + " is not a valid font description."));

    _fid = fid;
    _fname = PfConvertFontID(_fid);

    _italic = fstyle & FontStyle::Italic;
    _bold = fstyle & FontStyle::Bold;
    _size = fpoint_size;
    _height = 0;

    //const char *fname = PfConvertFontID(&other._fid);
    //const char *fstem = PfFontBaseStem(&other._fid);

    // PfDecomposeStemToID // These functions convert a complete font stem, such as helv12b, to a FontID representation.
    // PfFontFlags // These functions get the flags associated with the font ID pointed to by ptsID.
    // PfConvertFontID // These functions convert the font ID pointed to by ptsID into a font name. 
}

FontDef::FontDef(FontFamily ffamily, std::uint32_t fpoint_size, typedefs::font_style_bitmask fstyle):
    Bold(_bold),
    Family(_ffamily),
    Height(_height),
    Italic(_italic),
    Name(_fname),
    Size(_size),
    _ffamily(ffamily)
{
    const char *fdesc = ffamily.Name.c_str();

    // get new font ID
    font_id_type fid = PfFindFont(fdesc, fstyle, fpoint_size);
    if(NULL == fid)
        throw(std::invalid_argument(std::string(fdesc) + " is not a valid font family description."));
    
    _fid = fid;
    _fname = PfConvertFontID(_fid);

    _italic = fstyle & FontStyle::Italic;
    _bold = fstyle & FontStyle::Bold;
    _size = fpoint_size;
    _height = 0;
}

FontDef::FontDef(font_id_type fid):
    Bold(_bold),
    Family(_ffamily),
    Height(_height),
    Italic(_italic),
    Name(_fname),
    Size(_size),
    _fid(fid),
    _ffamily(GenericFontFamilies::Serif)
{
    if(NULL == _fid)
        throw(std::invalid_argument("FontID is NULL."));
    
    _fname = PfConvertFontID(_fid);

    std::uint32_t fflags = PfFontFlags(_fid);

    _italic = fflags & FontStyle::Italic;
    _bold = fflags & FontStyle::Bold;

    std::uint32_t fpoint_size = PfFontSize(_fid);

    _size = fpoint_size;
    _height = 0;
    
    const char *fdesc = PfFontDescription(_fid);

    _ffamily = FontFamily(fdesc);
}

FontDef::FontDef(const FontDef &other):
    Bold(_bold),
    Family(_ffamily),
    Height(_height),
    Italic(_italic),
    Name(_fname),
    Size(_size),
     _fid(other._fid),
     _fname(other._fname),
    _bold(other._bold),
    _italic(other._italic),
    _height(other._height),
    _size(other._size),
    _ffamily(other._ffamily)
{
}

FontDef & FontDef::operator=(const FontDef &other)
{
    if(&other != this)
    {
        _fid = other._fid;

        _bold = other._bold;
        _height = other._height;
        _italic = other._italic;
        _fname = other._fname;
        _size = other._size;
        _ffamily = other._ffamily;
    }

    return *this;
}

bool FontDef::operator==(const FontDef &other) const
{
    return 
        _fid == other._fid;
}

bool FontDef::operator!=(const FontDef &other) const
{
    return !(*this == other);
}

bool FontDef::operator<(const FontDef &other) const
{   
    return 
        _fid < other._fid;
}

FontDef::operator const font_id_type() const
{
    return _fid;
}

namespace PhWidgets
{
    bool operator==(const GenericFontFamilies::eGenericFontFamilies &lhs, const FontFamily &rhs)
    {
        return rhs == lhs;
    }

    bool operator!=(const GenericFontFamilies::eGenericFontFamilies &lhs, const FontFamily &rhs)
    {
        return rhs != lhs;
    }

    bool operator<(const GenericFontFamilies::eGenericFontFamilies &lhs, const FontFamily &rhs)
    {
        return FontFamily(lhs) < rhs;
    }
}

PhWidgets::typedefs::font_style_bitmask operator|(const PhWidgets::FontStyle::eFontStyle &flag1, const PhWidgets::FontStyle::eFontStyle &flag2)
{
    PhWidgets::typedefs::font_style_bitmask bm(flag1);
	return bm | flag2;
}

PhWidgets::typedefs::font_style_bitmask operator&(const PhWidgets::FontStyle::eFontStyle &flag1, const PhWidgets::FontStyle::eFontStyle &flag2)
{
	PhWidgets::typedefs::font_style_bitmask bm(flag1);
	return bm & flag2;
}

PhWidgets::typedefs::font_style_bitmask operator^(const PhWidgets::FontStyle::eFontStyle &flag1, const PhWidgets::FontStyle::eFontStyle &flag2)
{
	PhWidgets::typedefs::font_style_bitmask bm(flag1);
	return bm ^ flag2;
}