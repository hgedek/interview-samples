#include "../include/catch.hpp"
#include "../include/toolkit.hpp"

TEST_CASE("File exists ?") 
{
    REQUIRE(file_system::exists("../input_.txt") == false);
    REQUIRE(file_system::exists("../input.txt") == true);
}
/*
TEST_CASE("Wrong number arguments")
{
    std::vector<std::string> lines;
   
    SECTION("definition string missing")
    {
        lines.emplace_back("x_t0=100,x_tmax=200,duration=1");
        lines.emplace_back("0.2");
        lines.emplace_back("0.5");
        lines.emplace_back("1.0");

        REQUIRE_THROWS(easing_file_parser{}.parse(lines));
    } 

    SECTION("Linear") {
        SECTION("x_t0 missing")
        {
            lines.emplace_back("Linear,x_tmax=200,duration=1");
            REQUIRE_THROWS(easing_file_parser{}.parse(lines));
        }
        SECTION("x_tmax missing")
        {
            lines.emplace_back("Linear,x_t0=100,duration=1");
            REQUIRE_THROWS(easing_file_parser{}.parse(lines));
        }
        SECTION("duration missing")
        {
            lines.emplace_back("Linear,x_t0=100,x_tmax=200");
            REQUIRE_THROWS(easing_file_parser{}.parse(lines));
        }
    }
}

TEST_CASE("Empty time list") {

    std::vector<std::string> lines;

    lines.emplace_back("Linear,x_t0=100,x_tmax=200,duration=1");

    REQUIRE_THROWS_AS(easing_file_parser{}.parse(lines),std::runtime_error);
}

TEST_CASE("Parsing successfull") {

    std::vector<std::string> lines;

    lines.emplace_back("Linear,x_t0=100,x_tmax=200,duration=1");
    lines.emplace_back("0.2");
    lines.emplace_back("0.5");
    lines.emplace_back("1.0");


    auto base_ptr = easing_file_parser{}.parse(lines);
    auto linear_ptr = static_cast<linear_easing_data*>(base_ptr.get()); 

    REQUIRE(linear_ptr->type() == easing_type::linear);
    REQUIRE(linear_ptr->definition.x_t0 == 100);
    REQUIRE(linear_ptr->definition.x_tmax == 200);
    REQUIRE(linear_ptr->definition.duration == 1);
    REQUIRE(linear_ptr->time_list.size() == 3);
    REQUIRE(linear_ptr->time_list[0] == 0.2f);
    REQUIRE(linear_ptr->time_list[1] == 0.5f);
    REQUIRE(linear_ptr->time_list[2] == 1.0f);
}

TEST_CASE("File parsing")
{
    std::string_view file_name = "/Users/hakan/Workspace/interview-samples/easing_curve/input.txt";

    auto base_ptr = easing_file_parser{file_name}.parse();
    auto linear_ptr = static_cast<linear_easing_data*>(base_ptr.get()); 

    REQUIRE(linear_ptr->type() == easing_type::linear);
    REQUIRE(linear_ptr->definition.x_t0 == 100);
    REQUIRE(linear_ptr->definition.x_tmax == 200);
    REQUIRE(linear_ptr->definition.duration == 1);
    REQUIRE(linear_ptr->time_list.size() == 3);
    REQUIRE(linear_ptr->time_list[0] == 0.2f);
    REQUIRE(linear_ptr->time_list[1] == 0.5f);
    REQUIRE(linear_ptr->time_list[2] == 1.0f);
}

*/
