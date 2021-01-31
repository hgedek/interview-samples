#include "catch.hpp"
#include "toolkit.hpp"
#include <string>


TEST_CASE("file exists") {
    const std::string file_name ="/Users/hakan/Workspace/interview-samples/easing_curve/input.txt";
    decltype(file_name) non_exist = "/Users/hakan/Workspace/interview-samples/easing_curve/input.txt_";

    REQUIRE(file_system::exists(file_name) == true);
    REQUIRE(file_system::exists(non_exist) == false); 
}


TEST_CASE("is_floating_number")
{
    std::vector<std::string> numbers {"1.2f", "3.3", "abc","3.443434324"};

    REQUIRE(toolkit::is_floating_number(numbers[0]));
    REQUIRE(toolkit::is_floating_number(numbers[1]));
    REQUIRE_FALSE(toolkit::is_floating_number(numbers[2]));
    REQUIRE(toolkit::is_floating_number(numbers[3]));
}

TEST_CASE("to_lower")
{
    using namespace std::string_literals;

    std::string str = "ABCdef"s;
    const std::string empty = ""s;
    const std::string cstr = "ABCdef"s;

    SECTION("overwrite") 
    {
        toolkit::to_lower(str);
        REQUIRE(str == "abcdef"s);
    }        

    REQUIRE(toolkit::to_lower(cstr) == "abcdef"s);
    REQUIRE(toolkit::to_lower(empty) == ""s);
}

TEST_CASE("str to easing type")
{
    REQUIRE(toolkit::str_to_easing_type("LINEAR") == easing_type::linear);
    REQUIRE(toolkit::str_to_easing_type("Linar") == easing_type::none);
    REQUIRE(toolkit::str_to_easing_type("linear") == easing_type::linear);
    REQUIRE(toolkit::str_to_easing_type("LiNeAr") == easing_type::linear);
    REQUIRE(toolkit::str_to_easing_type("") == easing_type::none);
    REQUIRE(toolkit::str_to_easing_type("fdsfdsa") == easing_type::none);
    REQUIRE(toolkit::str_to_easing_type("in_quad") == easing_type::in_quad);
    REQUIRE(toolkit::str_to_easing_type("out_quad") == easing_type::out_quad);
    REQUIRE(toolkit::str_to_easing_type("in_out_quad") == easing_type::in_out_quad);
}

TEST_CASE("type extracting from string")
{
    std::vector<std::string> lines {
        "Linear,fdsf",
        "linear,dsafds",
        "in_out_quad,fdafdsf",
        "in_quad,fdffds",
        "out_quad,dfdsafs",
        "lin,fdsfds",
        "",
        "fdsafds,fdsafds"
    };

    easing_type_checker tc;

    REQUIRE(tc(lines[0]) == easing_type::linear);
    REQUIRE(tc(lines[1]) == easing_type::linear);
    REQUIRE(tc(lines[2]) == easing_type::in_out_quad);
    REQUIRE(tc(lines[3]) == easing_type::in_quad);
    REQUIRE(tc(lines[4]) == easing_type::out_quad);
    REQUIRE(tc(lines[5]) == easing_type::none);
    REQUIRE(tc(lines[6]) == easing_type::none);
    REQUIRE(tc(lines[7]) == easing_type::none);
}


