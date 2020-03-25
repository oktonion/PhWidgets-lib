#include "./testsuit/testsuit.h"

#include "./artifacts/Dialog0.h"
#include "./artifacts/Menu0.h"
#include "./artifacts/Picture0.h"
#include "./artifacts/TEST_WINDOW.h"

#include "./artifacts/Dialog0.cpp"
#include "./artifacts/Menu0.cpp"
#include "./artifacts/Picture0.cpp"
#include "./artifacts/TEST_WINDOW.cpp"

TEST_CASE("Checking using of generated UI"){

    using namespace PhGUI;

    SUBCASE("TEST_WINDOW"){
        
        TEST_WINDOW test_window;    
        
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

