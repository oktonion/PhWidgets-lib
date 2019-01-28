#include "./phwidgets_init.cpp"

#include "./testsuit.h"

#include <Font.h>

#include <algorithm>
#include <vector>

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


TEST_CASE("Testing FontFamily class"){

    using namespace PhWidgets;
    
    REQUIRE(FontCollection::Families().size() != 0);

    FontFamily ff_sans(GenericFontFamilies::SansSerif);

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