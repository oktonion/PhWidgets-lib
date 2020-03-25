#include "./testsuit/testsuit.h"

#include <etc/mkphgui/src/config.cfg.c>
#define main mkphgui_main
#include <etc/mkphgui/src/mkphgui.cpp>
#undef main

#include <string>

#include <unistd.h>

TEST_CASE("Checking generation of UI"){

    std::string program_path;
    {
        char cwd[PATH_MAX];
        program_path = getcwd(cwd, PATH_MAX);
    }
    
    int argc = 3;
    const char *argv[3];

    argv[0] = program_path.c_str();
    argv[1] = "./tests/generator/testsuit/resources/test_app/wgt/TEST_WINDOW.wgtw";
    argv[2] = "./tests/generator/artifacts/";
    
    CHECK(0 == mkphgui_main(argc, argv));
}

