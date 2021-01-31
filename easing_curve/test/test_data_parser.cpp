#include "catch.hpp"
#include "easing_data_parser.hpp"

TEST_CASE("parsing definition")
{

    easing_data_parser parser{};

    SECTION("wrong inputs")
    {
        const std::vector<std::string> lines {
            "Linear,a=0,b=1",
            "a=1,b=2,duration=3",
            "Linear",
            "x_t0=0,x_tmax=100,duration=1",
            "duration=0"
        }; 

        for (const auto& str : lines) 
            REQUIRE_THROWS_AS(parser(str), std::runtime_error);
    }

    SECTION("correct inputs")
    {
        const std::vector<std::string> lines {
            "lineaR,x_t0=0,x_tmax=100,duration=1",
            "LINEAR,x_t0=0,x_tmax=100,duration=1",
            "Linear,x_t0=0,x_tmax=100,duration=1"
        };
       
        const auto linear = parser(lines.at(0));

        REQUIRE(linear.definition.x_t0 == 0);
        REQUIRE(linear.definition.x_tmax == 100);
        REQUIRE(linear.definition.duration == 1);
        REQUIRE(linear.type == easing_type::linear);

        const auto LINEAR = parser(lines.at(1));
        REQUIRE(LINEAR.definition.x_t0 == 0);
        REQUIRE(LINEAR.definition.x_tmax == 100);
        REQUIRE(LINEAR.definition.duration == 1);
        REQUIRE(LINEAR.type == easing_type::linear);

        const auto Linear = parser(lines.at(2));
        REQUIRE(Linear.definition.x_t0 == 0);
        REQUIRE(Linear.definition.x_tmax == 100);
        REQUIRE(Linear.definition.duration == 1);
        REQUIRE(Linear.type == easing_type::linear);

    }
}
