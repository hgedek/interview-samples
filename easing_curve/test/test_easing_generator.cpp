#include "catch.hpp"
#include "easing_curve_generator.hpp"


TEST_CASE("generator succeeds")
{
// Linear,x_t0=100,x_tmax=200,duration=1
// 0.2
// 0.5
// 1.0
    easing_t obj { easing_type::linear, 100, 200, 1 };
    obj.time_list.emplace_back(0.2f);
    obj.time_list.emplace_back(0.5f);
    obj.time_list.emplace_back(1.0f);

    easing_type type = easing_type::linear;
    
    auto result = generator_manager::instance()[type]->operator()(obj);
    
    REQUIRE(result.results.at(0) == 120);
    REQUIRE(result.results.at(1) == 150);
    REQUIRE(result.results.at(2) == 200);  
}
