#include "catch.hpp"
#include "easing_input_data.hpp"

TEST_CASE("initialization")
{

    SECTION("default")
    {
        easing_input_data data{};
        REQUIRE(data.type == easing_type::none);
        REQUIRE_FALSE(data.is_valid());
    }

    SECTION("with type")
    {
        easing_input_data data{easing_type::linear};

        REQUIRE(data.type == easing_type::linear);
        REQUIRE_FALSE(data.is_valid());
    }

    SECTION("with params")
    {
        easing_input_data data{easing_type::linear, 0, 100, 1}; 
        data.time_list.push_back(0.2);
        data.time_list.push_back(0.5);

        REQUIRE(data.type == easing_type::linear);
        REQUIRE(data.is_valid());
    }
}
