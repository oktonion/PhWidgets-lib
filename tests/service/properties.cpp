#include "./testsuit.h"

#include <service/property.hpp>


TEST_CASE("Testing cppproperties") {
    
    using namespace cppproperties;

    SUBCASE("Testing properties for simple types"){
        {
            property<int> prop_int;

            prop_int = 11;

            CHECK(prop_int.get() == 11);
            CHECK(11 == prop_int);
            CHECK(prop_int == 11);
        }

        {
            const property<int> prop_int(42);

            CHECK(prop_int.get() == 42);
            CHECK(42 == prop_int);
            CHECK(prop_int == 42);
        }
    }
    
}