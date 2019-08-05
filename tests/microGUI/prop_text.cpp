#include "./1phwidgets_init.cpp"

#include "./testsuit.h"

#include <Label.h>
#include <Text.h>


TEST_CASE("Testing Label::Text property"){

    using namespace PhWidgets;
    

    SUBCASE("Label Text test"){
        REQUIRE(PhWidgetsGetWidget<&PtLabel>());
        
        Label label(PhWidgetsGetWidget<&PtLabel>());

        label.Text = "";

        CHECK(label.Text() == std::string(""));

        label.Text = "Missisipi 1";
        CHECK(label.Text() == std::string("Missisipi 1"));

        label.Text = "Missisipi 2";
        CHECK(std::string("Missisipi 2") == label.Text());
    }

    SUBCASE("Text Label::Text test"){
        REQUIRE(PhWidgetsGetWidget<&PtText>());
        
        Text text(PhWidgetsGetWidget<&PtText>());

        text.Text = "";

        CHECK(text.Text() == std::string(""));

        text.Text = "Missisipi 3";
        CHECK(text.Text() == std::string("Missisipi 3"));

        text.Text = "Missisipi 4";
        CHECK(std::string("Missisipi 4") == text.Text());
    }

}