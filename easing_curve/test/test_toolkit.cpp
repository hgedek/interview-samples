#include "catch.hpp"
#include "toolkit.hpp"
#include <string>
#include <iostream>

TEST_CASE("file exists") {

    const std::string file_name = toolkit::absolute_path("empty.txt");
    decltype(file_name) non_exist = toolkit::absolute_path("input.txt_");

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
    REQUIRE(toolkit::str_to_easing_type("inquad") == easing_type::in_quad);
    REQUIRE(toolkit::str_to_easing_type("outquad") == easing_type::out_quad);
    REQUIRE(toolkit::str_to_easing_type("inoutquad") == easing_type::in_out_quad);
}

TEST_CASE("easing type to str")
{
    REQUIRE(toolkit::easing_type_to_str(easing_type::linear) == "Linear");
    REQUIRE(toolkit::easing_type_to_str(easing_type::in_quad) == "InQuad");
    REQUIRE(toolkit::easing_type_to_str(easing_type::out_quad) == "OutQuad");
    REQUIRE(toolkit::easing_type_to_str(easing_type::in_out_quad) == "InOutQuad");
}

TEST_CASE("type extracting from string")
{
    std::vector<std::string> lines {
        "Linear,fdsf",
        "linear,dsafds",
        "inoutquad,fdafdsf",
        "inquad,fdffds",
        "outquad,dfdsafs",
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

