#ifndef PHWIDGETS_MICROGUI_TESTSUIT_H
#define PHWIDGETS_MICROGUI_TESTSUIT_H

#ifndef DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
    #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
    #include "./../doctest/doctest.h"
#endif // DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <Pt.h>



template<PtWidgetClassRef_t **Ref>
PtWidget_t *&PhWidgetsGetWidget()
{
    static PtWidget_t *ptwidget_ptr = 0;
    return ptwidget_ptr;
}


template<PtWidgetClassRef_t **Ref>
PtWidget_t *PhWidgetsCreateWidget(PtWidget_t *parent, unsigned int flags, const PtArg_t *args)
{
    PhWidgetsGetWidget<Ref>() = PtCreateWidget(*Ref, parent, flags, args);

    return PhWidgetsGetWidget<Ref>();
}

template<class PropertyT>
void phwidgets_property_test_subcase(PropertyT &property, const char *prop_name)
{
    typedef typename PropertyT::value_type property_value_type;
    SUBCASE(prop_name) {
        property_value_type
            v = property,
            vv = static_cast<property_value_type>(v * 1.5) + property_value_type(100);
        CHECK_MESSAGE(property == v, prop_name);
        property = vv;
        CHECK_MESSAGE(v != property, prop_name);
        CHECK_MESSAGE(vv == property, prop_name);
    }
}

#define PHWIDGETS_PROPERTY_TEST_SUBCASE(prop) phwidgets_property_test_subcase(prop, #prop)

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

#endif // PHWIDGETS_MICROGUI_TESTSUIT_H
