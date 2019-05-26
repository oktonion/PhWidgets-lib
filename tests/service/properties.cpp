#include "./testsuit.h"

#include <service/property.hpp>


template<class T>
struct convertable
{
    convertable(T value = T()):        
        _value(value) {}
    operator T() const {return _value;}

private:
    T _value;
};

template<class T>
struct property_container
{
    property_container(T value_ = T()):
        _value(value_),
        value(this),
        const_value(this),
        ro_value(this),
        wo_value(this)
    { }

private:
    T _value;
    T getter() const {return _value;}
    void setter(T value_) {_value = value_;}

public:
    typename
    cppproperties::property<T>::
        template bind<property_container, &property_container::getter, &property_container::setter> value;

    typename
    cppproperties::property<T>::
        template bind<property_container, &property_container::getter, &property_container::setter> const const_value;

    typename
    cppproperties::property<T, cppproperties::property<>::ro>::
        template bind<property_container, &property_container::getter> ro_value;

    typename
    cppproperties::property<T, cppproperties::property<>::wo>::
        template bind<property_container, &property_container::setter> wo_value;
};

template<class T>
struct property_container<const T>
{
    property_container(T value_ = T()):
        _value(value_),
        value(this),
        const_value(this),
        ro_value(this)
    { }

private:
    const T _value;
    const T getter() const {return _value;}

public:
    typename
    cppproperties::property<const T>::
        template bind<property_container, &property_container::getter> value;

    typename
    cppproperties::property<const T>::
        template bind<property_container, &property_container::getter> const const_value;

    typename
    cppproperties::property<const T, cppproperties::property<>::ro>::
        template bind<property_container, &property_container::getter> ro_value;
};

template<class PropertyT>
void property_test_subcase1(PropertyT &property, const char *message)
{
    SUBCASE(message) {

        property = 11;

        CHECK(property.get() == 11);
        CHECK(11 == property);
        CHECK(property == 11);

        int val = 42;
        property.set(val);

        CHECK(property.get() == val);
        CHECK(val == property);
        CHECK(property == val);

        CHECK_FALSE(property != val);
        CHECK_FALSE(val != property);
        CHECK_FALSE(property != property);

        CHECK_FALSE(val < property);
        CHECK_FALSE(property < val);
        CHECK_FALSE(property < property);
    }
}

template<class PropertyT>
void property_test_subcase2(PropertyT &property, const char *message)
{
    SUBCASE(message) {

        CHECK(property.get() == 42);
        CHECK(42 == property);
        CHECK(property == 42);

        CHECK_FALSE(property != 42);
        CHECK_FALSE(42 != property);
        CHECK_FALSE(property != property);

        CHECK_FALSE(42 < property);
        CHECK_FALSE(property < 42);
        CHECK_FALSE(property < property);
    }
}

template<class PropertyT>
void property_test_subcase3(PropertyT &property, const char *message)
{
    SUBCASE(message) {

        CHECK(property.get() == 42);
        CHECK(42 == property);
        CHECK(property == 42);

        CHECK_FALSE(property == convertable<int>());
        CHECK_FALSE(convertable<int>() == property);
        CHECK(property != convertable<int>());
        CHECK(convertable<int>() != property);
        CHECK_FALSE(property != property);

        CHECK(convertable<int>() < property);
        CHECK_FALSE(property < convertable<int>());
        CHECK_FALSE(property < property);
    }
}

template<class PropertyT>
void property_test_subcase4(PropertyT &property, const char *message)
{
    SUBCASE(message) {

        CHECK(property.get() == 42);
        CHECK(42 == property);
        CHECK(property == 42);

        cppproperties::property<const int> 
            prop_cint(42),
            prop_cint2(property + 1);

        CHECK(prop_cint == property);
        CHECK(property == prop_cint);
        CHECK_FALSE(property > prop_cint);

        CHECK(prop_cint2 > property);
        CHECK(prop_cint2 != property);
        CHECK(property != prop_cint2);
    }
}


TEST_CASE("Testing properties for simple types"){

    using namespace cppproperties;

    {
        property<int> prop_int;

        property_test_subcase1(prop_int, "Testing rw property");
    }

    {
        const property<int> prop_int(42);

        property_test_subcase2(prop_int, "Testing const rw property");
    }

    {
        property<const int> prop_int(42);

        property_test_subcase3(prop_int, "Testing ro property of const");
    }

    {
        property<int, property<>::ro> prop_int(42);

        property_test_subcase4(prop_int, "Testing ro property");
    }

    SUBCASE("Testing wo property") {

        property<int, property<>::wo> prop_int(10);

        prop_int.set(10);
        CHECK(prop_int == prop_int);
        //CHECK_EQ(10, property);
        CHECK(prop_int == 10);
        CHECK_EQ(prop_int, 10);
        prop_int.set(convertable<int>());
        CHECK(prop_int != 10);
    }

    SUBCASE("Testing mixed property"){

        property<int, property<>::wo> prop_wo(10);
        property<int, property<>::ro> prop_ro(10);
        property<int, property<>::rw> prop_rw(10);

        CHECK(prop_wo == prop_ro);
        CHECK(prop_wo == prop_rw);
        //CHECK(prop_ro == prop_wo);
        CHECK(prop_ro == prop_rw);
        CHECK(prop_rw == prop_ro);
        //CHECK(prop_rw == prop_wo);

        CHECK_FALSE(prop_wo != prop_ro);
        CHECK_FALSE(prop_wo != prop_rw);
        //CHECK_FALSE(prop_ro != prop_wo);
        CHECK_FALSE(prop_ro != prop_rw);
        CHECK_FALSE(prop_rw != prop_ro);
        //CHECK_FALSE(prop_rw != prop_wo);

        CHECK_FALSE(prop_wo < prop_ro);
        CHECK_FALSE(prop_wo < prop_rw);
        //CHECK_FALSE(prop_ro < prop_wo);
        CHECK_FALSE(prop_ro < prop_rw);
        CHECK_FALSE(prop_rw < prop_ro);
        //CHECK_FALSE(prop_rw < prop_wo);
    }

    SUBCASE("Testing mixed types properties"){

        property<int, property<>::wo> prop_wo(10);
        property<float, property<>::ro> prop_ro(10.0f);
        property<short, property<>::rw> prop_rw(10);

        CHECK(prop_wo == prop_ro);
        CHECK(prop_wo == prop_rw);
        //CHECK(prop_ro == prop_wo);
        CHECK(prop_ro == prop_rw);
        CHECK(prop_rw == prop_ro);
        //CHECK(prop_rw == prop_wo);

        CHECK_FALSE(prop_wo != prop_ro);
        CHECK_FALSE(prop_wo != prop_rw);
        //CHECK_FALSE(prop_ro != prop_wo);
        CHECK_FALSE(prop_ro != prop_rw);
        CHECK_FALSE(prop_rw != prop_ro);
        //CHECK_FALSE(prop_rw != prop_wo);

        CHECK_FALSE(prop_wo < prop_ro);
        CHECK_FALSE(prop_wo < prop_rw);
        //CHECK_FALSE(prop_ro < prop_wo);
        CHECK_FALSE(prop_ro < prop_rw);
        CHECK_FALSE(prop_rw < prop_ro);
        //CHECK_FALSE(prop_rw < prop_wo);

        CHECK(convertable<float>(10.f) == prop_ro);
        CHECK(prop_wo == convertable<double>(10.));
        //CHECK(prop_ro == prop_wo);
        CHECK(convertable<float>(10.f) == prop_rw);
        CHECK(prop_rw == convertable<char>(10));
        //CHECK(prop_rw == prop_wo);

        CHECK(convertable<float>(42.f) != prop_ro);
        CHECK(prop_wo != convertable<double>(42.));
        //CHECK(prop_ro != prop_wo);
        CHECK(convertable<double>(42.) != prop_rw);
        CHECK(prop_rw != convertable<double>(42.));
        //CHECK(prop_rw != prop_wo);

        CHECK_FALSE(convertable<int>(42) < prop_ro);
        CHECK(prop_wo < convertable<double>(42.));
        //CHECK(prop_ro < prop_wo);
        CHECK_FALSE(convertable<unsigned int>(42) < prop_rw);
        CHECK(prop_rw < convertable<float>(42.f));
        //CHECK(prop_rw < prop_wo);
    }

    {
        property_container<int> prop_cont;

        prop_cont.value = 11;

        property_test_subcase1(prop_cont.value, "Testing rw contained property");
    }

    {

        property_container<int> prop_cont(42);

        property_test_subcase2(prop_cont.const_value, "Testing const rw contained property");
    }

    {
        property_container<const int> prop_cont(42);

        property_test_subcase3(prop_cont.value, "Testing ro contained property of const");
    }

    {
        property_container<int> prop_cont(42);

        property_test_subcase4(prop_cont.ro_value, "Testing ro contained property");
    }

    SUBCASE("Testing wo contained property") {

        property_container<int> prop_cont(10);

        prop_cont.wo_value.set(10);
        prop_cont.wo_value.set(convertable<int>());

        prop_cont.wo_value = convertable<int>();

        
    }

    SUBCASE("Testing mixed contained property"){

        property_container<int> prop_cont(10);

        CHECK(prop_cont.value == prop_cont.ro_value);
        CHECK(prop_cont.ro_value == prop_cont.value);

        CHECK_FALSE(prop_cont.value != prop_cont.ro_value);
        CHECK_FALSE(prop_cont.ro_value != prop_cont.value);

        CHECK_FALSE(prop_cont.value < prop_cont.ro_value);
        CHECK_FALSE(prop_cont.ro_value < prop_cont.value);
    }
}

#include <vector>



TEST_CASE("Testing properties for class types"){

    using namespace cppproperties;

    SUBCASE("Testing rw property") {
        
        typedef property<std::vector<int>/**/ > property_type;
        property_type prop_vint;

        CHECK(prop_vint.get().size() == 0);

        std::vector<int> val = prop_vint.get();
        val.push_back(42);
        prop_vint = val;

        CHECK(prop_vint.get().size() == 1);

        for (std::vector<int>::iterator it = prop_vint.get().begin(); it != prop_vint.get().end(); ++it)
        {
            CHECK(*it == 42);
        }
    }
}