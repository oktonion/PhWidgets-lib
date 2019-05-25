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
    typename
    cppproperties::property<T>::
        template bind<property_container, &property_container::getter, &property_container::setter> value;

    property_container(T value_ = T()):
        _value(value_),
        value(this)
    { }

private:
    T _value;
    T getter() const {return _value;}
    void setter(T value_) {_value = value_;}
};


TEST_CASE("Testing properties for simple types"){

    using namespace cppproperties;

    SUBCASE("Testing rw property"){
    
        property<int> prop_int;

        prop_int = 11;

        CHECK(prop_int.get() == 11);
        CHECK(11 == prop_int);
        CHECK(prop_int == 11);

        int val = 42;
        prop_int.set(val);

        CHECK(prop_int.get() == val);
        CHECK(val == prop_int);
        CHECK(prop_int == val);

        CHECK_FALSE(prop_int != val);
        CHECK_FALSE(val != prop_int);
        CHECK_FALSE(prop_int != prop_int);

        CHECK_FALSE(val < prop_int);
        CHECK_FALSE(prop_int < val);
        CHECK_FALSE(prop_int < prop_int);
    }

    SUBCASE("Testing const rw property"){

        const property<int> prop_int(42);

        CHECK(prop_int.get() == 42);
        CHECK(42 == prop_int);
        CHECK(prop_int == 42);

        CHECK_FALSE(prop_int != 42);
        CHECK_FALSE(42 != prop_int);
        CHECK_FALSE(prop_int != prop_int);

        CHECK_FALSE(42 < prop_int);
        CHECK_FALSE(prop_int < 42);
        CHECK_FALSE(prop_int < prop_int);
    }

    SUBCASE("Testing ro property of const"){

        property<const int> prop_int(42);

        CHECK(prop_int.get() == 42);
        CHECK(42 == prop_int);
        CHECK(prop_int == 42);

        CHECK_FALSE(prop_int == convertable<int>());
        CHECK_FALSE(convertable<int>() == prop_int);
        CHECK(prop_int != convertable<int>());
        CHECK(convertable<int>() != prop_int);
        CHECK_FALSE(prop_int != prop_int);

        CHECK(convertable<int>() < prop_int);
        CHECK_FALSE(prop_int < convertable<int>());
        CHECK_FALSE(prop_int < prop_int);
    }

    SUBCASE("Testing ro property"){

        property<int, property<>::ro> prop_int(42);

        CHECK(prop_int.get() == 42);
        CHECK(42 == prop_int);
        CHECK(prop_int == 42);

        property<const int> 
            prop_cint(42),
            prop_cint2(prop_int + 1);

        CHECK(prop_cint == prop_int);
        CHECK(prop_int == prop_cint);
        CHECK_FALSE(prop_int > prop_cint);

        CHECK(prop_cint2 > prop_int);
        CHECK(prop_cint2 != prop_int);
        CHECK(prop_int != prop_cint2);
    }

    SUBCASE("Testing wo property"){

        property<int, property<>::wo> prop_int(10);

        prop_int.set(10);
        CHECK(prop_int == prop_int);
        //CHECK_EQ(10, prop_int);
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


    SUBCASE("Testing rw contained property"){
        property_container<int> prop_cont;

        prop_cont.value = 11;

        CHECK(prop_cont.value.get() == 11);
        CHECK(11 == prop_cont.value);
        CHECK(prop_cont.value == 11);

        int val = 42;
        prop_cont.value.set(val);

        CHECK(prop_cont.value.get() == val);
        CHECK(val == prop_cont.value);
        CHECK(prop_cont.value == val);

        CHECK_FALSE(prop_cont.value != val);
        CHECK_FALSE(val != prop_cont.value);
        CHECK_FALSE(prop_cont.value != prop_cont.value);

        CHECK_FALSE(val < prop_cont.value);
        CHECK_FALSE(prop_cont.value < val);
        CHECK_FALSE(prop_cont.value < prop_cont.value);
    }
}