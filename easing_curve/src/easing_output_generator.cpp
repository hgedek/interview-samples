#include "easing_output_generator.hpp"
#include "easing_curve_generator.hpp"

void easing_output_generator::generate(easing_list_t const& vl) {

    if (vl.empty())
        throw std::runtime_error("empty easing list");

    const auto& manager = generator_manager::instance();

    for (const auto& item : vl)
        manager[item.type]->operator()(item);   
}
