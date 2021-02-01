#include "catch.hpp"
#include "easing_file_parser.hpp"

TEST_CASE("file not exists")
{
    REQUIRE_THROWS_AS(easing_file_parser{}.parse(toolkit::absolute_path("not_exist.txt")),
            std::runtime_error);
}

TEST_CASE("empty file") 
{
    const auto easing_list = easing_file_parser{}.parse(toolkit::absolute_path("empty.txt"));
    REQUIRE(easing_list.empty());
}

TEST_CASE("one curve file")
{
    const auto easing_list = easing_file_parser{}.parse(toolkit::absolute_path("one_curve.txt"));

    REQUIRE(easing_list.size() == 1);

    /*

Linear,x_t0=100,x_tmax=200,duration=1
0.2
0.5
1.0
*/
    const auto& obj = easing_list.front();

    REQUIRE(obj.type == easing_type::linear);
    REQUIRE(obj.definition.x_t0 == 100);
    REQUIRE(obj.definition.x_tmax == 200);
    REQUIRE(obj.definition.duration == 1);
    
    REQUIRE(obj.time_list.size() == 3);
    REQUIRE(obj.time_list.front() == 0.2f);
    REQUIRE(obj.time_list.back() == 1.0f);

}

TEST_CASE("two curves file")
{
    const auto easing_list = easing_file_parser{}.parse(toolkit::absolute_path("two_curves.txt"));

    REQUIRE(easing_list.size() == 2);

    const auto& obj = easing_list.front();
    const auto& obj1 = easing_list.back();

    REQUIRE(obj.type == easing_type::linear);
    REQUIRE(obj.definition.x_t0 == 100);
    REQUIRE(obj.definition.x_tmax == 200);
    REQUIRE(obj.definition.duration == 1);
    
    REQUIRE(obj.time_list.size() == 3);
    REQUIRE(obj.time_list.front() == 0.2f);
    REQUIRE(obj.time_list.back() == 1.0f);

    REQUIRE(obj1.type == easing_type::linear);
    REQUIRE(obj1.definition.x_t0 == 100);
    REQUIRE(obj1.definition.x_tmax == 200);
    REQUIRE(obj1.definition.duration == 1);
    
    REQUIRE(obj1.time_list.size() == 3);
    REQUIRE(obj1.time_list.front() == 0.2f);
    REQUIRE(obj1.time_list.back() == 1.0f);
}

TEST_CASE("multiple curves files")
{
    const auto easing_list = easing_file_parser{}.parse(toolkit::absolute_path("multiple_curves.txt"));

    REQUIRE(easing_list.size() == 4);
}

TEST_CASE("fail00.txt = one curve exists")
{
    const auto easing_list = easing_file_parser{}.parse(toolkit::absolute_path("fail_00.txt"));

    REQUIRE(easing_list.size() == 1);

    const auto& obj = easing_list.front();

    REQUIRE(obj.type == easing_type::linear);
    REQUIRE(obj.definition.x_t0 == 100);
    REQUIRE(obj.definition.x_tmax == 200);
    REQUIRE(obj.definition.duration == 1);
    
    REQUIRE(obj.time_list.size() == 3);
    REQUIRE(obj.time_list.front() == 0.2f);
    REQUIRE(obj.time_list.back() == 1.0f);
}


