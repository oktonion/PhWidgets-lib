#ifndef PHWIDGETS_TESTSUIT_H
#define PHWIDGETS_TESTSUIT_H

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

#endif // PHWIDGETS_TESTSUIT_H