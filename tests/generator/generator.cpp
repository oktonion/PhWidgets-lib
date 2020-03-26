#include "./testsuit/testsuit.h"

#include <etc/mkphgui/src/config.cfg.c>
#define main mkphgui_main
#include <etc/mkphgui/src/mkphgui.cpp>
#undef main

#include <string>

#include <unistd.h>
#include <cstdlib>
#include <cstdio>

bool all_ok = false;

TEST_CASE("Checks of generation of UI"){

    std::string program_path;
    {
        char cwd[PATH_MAX];
        program_path = getcwd(cwd, PATH_MAX);
    }
    
    int argc = 3;
    const char *argv[3];

    argv[0] = program_path.c_str();

    struct mkphguiRAII
    {
        ~mkphguiRAII() 
        {
            widgets.clear();
            hierarchy.clear();
            last_child_id = -1;
        }
    };

    SUBCASE("TEST_WINDOW"){
        
        mkphguiRAII mkphguiRAII_;

        argv[1] = "./tests/generator/testsuit/resources/test_app/wgt/TEST_WINDOW.wgtw";
        argv[2] = "./tests/generator/artifacts/";
        
        CHECK(0 == mkphgui_main(argc, argv));
        
    }

    SUBCASE("Dialog0"){

        mkphguiRAII mkphguiRAII_;

        argv[1] = "./tests/generator/testsuit/resources/test_app/wgt/Dialog0.wgtd";
        argv[2] = "./tests/generator/artifacts/";
        
        CHECK(0 == mkphgui_main(argc, argv));
    }

    SUBCASE("Menu0"){
        
        mkphguiRAII mkphguiRAII_;

        argv[1] = "./tests/generator/testsuit/resources/test_app/wgt/Menu0.wgtm";
        argv[2] = "./tests/generator/artifacts/";
        
        CHECK(0 == mkphgui_main(argc, argv));
    }

    SUBCASE("Picture0"){
        
        mkphguiRAII mkphguiRAII_;

        argv[1] = "./tests/generator/testsuit/resources/test_app/wgt/Picture0.wgtp";
        argv[2] = "./tests/generator/artifacts/";
        
        CHECK(0 == mkphgui_main(argc, argv));
    }

    SUBCASE("Generating test for UI"){
        
        REQUIRE(0 == std::system("./tests/generator/build_consumer.sh"));

        struct RemoveConsumer
        {
            ~RemoveConsumer() {
                std::remove("./tests/bin/consumer");
            }
        }RemoveConsumerRAII;

        std::cout << "running generated test consumer" << std::endl;

        REQUIRE(0 == std::system("chmod a+rwx ./tests/bin/consumer"));
        REQUIRE(0 == std::system("./tests/bin/consumer -nv -nc"));
    }
}

