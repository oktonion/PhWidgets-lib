#define main doctest_main
#include "./testsuit/testsuit.h"
#undef main

#include "./artifacts/Dialog0.h"
#include "./artifacts/Menu0.h"
#include "./artifacts/Picture0.h"
#include "./artifacts/TEST_WINDOW.h"

#include <Ap.h>
#include <Ph.h>

extern "C"
{
    #define ApOptions ApOptionsDisabled
    #include "./testsuit/resources/test_app/src/abimport.h"
    #include "./testsuit/resources/test_app/src/abevents.h"
    #undef ApOptions
}

#include <unistd.h>
#include <cstdlib>


static int PhotonInit()
{
    static char cwd[PATH_MAX];
    getcwd(cwd, PATH_MAX);

    int argc = 1;
    static char *argv[1];

    argv[0] = &cwd[0];
    _Ap_.Ap_winstate = 0;

    int err = ApInitialize( argc, argv, &AbContext );
    if (err) return err;

    ApLinkWindow( NULL, &AbApplLinks[0], NULL );

    return 0;
} 

namespace PhWidgets {
    std::size_t GetABWCount();
    std::vector<PtWidget_t*> GetABW();
}


TEST_CASE("Checking using of generated UI"){

    REQUIRE(PhWidgets::GetABWCount() > 0);
    REQUIRE(PhWidgets::GetABW().size() > 0);

    static const int PhWidgetsApInit = PhotonInit();

    REQUIRE(PhWidgetsApInit == 0);

    using namespace PhGUI;

    SUBCASE("TEST_WINDOW"){

        REQUIRE(_Ap_.Ap_base_wgt);

        CHECK_NOTHROW({
            PhGUI::TEST_WINDOW test_window;
        });        
        
        PhGUI::TEST_WINDOW test_window;    
        
        CHECK(test_window.Left == 0);
        CHECK((nullptr == test_window.Parent()));

        CHECK(test_window.TEST_BUTTON.Enabled == true);

        CHECK(test_window.TEST_NUMERIC_FLOAT.Value == 0.f);
        test_window.TEST_NUMERIC_FLOAT.Value = 1.1f;

        CHECK(test_window.TEST_NUMERIC_FLOAT.Value == 1.1f);
    }

    SUBCASE("Dialog0"){

        CHECK_THROWS({
            PhGUI::Dialog0 dialog0;
        });
    }

    SUBCASE("Menu0"){

        CHECK_THROWS({
            PhGUI::Menu0 menu0;
        });
    }

    SUBCASE("Picture0"){
        
        CHECK_THROWS({
            PhGUI::Picture0 picture0;
        });
    }
}

extern "C"
{
    int main ( int argc, char *argv[] )
    {
        int err = doctest_main(argc, argv);

        PtExit( 0 );

        return err;
    }
}

