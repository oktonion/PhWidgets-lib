#include "./testsuit/testsuit.h"

#include "./artifacts/Dialog0.h"
#include "./artifacts/Menu0.h"
#include "./artifacts/Picture0.h"
#include "./artifacts/TEST_WINDOW.h"

TEST_CASE("Checking using of generated UI"){

    using namespace PhGUI;

    SUBCASE("TEST_WINDOW"){
        
        CHECK_NOTHROW({
            TEST_WINDOW test_window;
        });        
        
        TEST_WINDOW test_window;    
        
        CHECK(test_window.Left == 0);
        CHECK((nullptr == test_window.Parent()));
    }

    SUBCASE("Dialog0"){

        Dialog0 dialog0;
    }

    SUBCASE("Menu0"){
        
        Menu0 menu0;
    }

    SUBCASE("Picture0"){

        Picture0 picture0;
    }
}

