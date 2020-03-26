#include "./testsuit/testsuit.h"

#include "./artifacts/Dialog0.h"
#include "./artifacts/Menu0.h"
#include "./artifacts/Picture0.h"
#include "./artifacts/TEST_WINDOW.h"

#include <Ap.h>
#include <Ph.h>

#include <unistd.h>
#include <cstdlib>

static const int PhWidgetsPtInit = 0;//PtInit(NULL);



static int PhotonInit()
{
    if(-1 == PhWidgetsPtInit)
    {
        std::cout << "PhotonInit failed" << std::endl;
        return -1;
    }
    char cwd[PATH_MAX];
    getcwd(cwd, PATH_MAX);

    int argc = 1;
    char *argv[1];

    argv[0] = &cwd[0];
    _Ap_.Ap_winstate = 0;

    ApInitialize( argc, argv, &AbContext );
	//PtExit( 0 );

	return 0;
} 




TEST_CASE("Checking using of generated UI"){

    REQUIRE(PhWidgetsPtInit == 0);

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
    }

    SUBCASE("Dialog0"){

        PhGUI::Dialog0 dialog0;
    }

    SUBCASE("Menu0"){
        
        PhGUI::Menu0 menu0;
    }

    SUBCASE("Picture0"){

        PhGUI::Picture0 picture0;
    }
}

