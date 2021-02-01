#include "easing_curve_generator.hpp"

struct linear_generator: easing_curve_generator {
    void operator()(easing_t const&) const override {}
};

struct in_quad_generator: easing_curve_generator {
    void operator()(easing_t const&) const override {}
};

struct out_quad_generator: easing_curve_generator {
    void operator()(easing_t const&) const override {}
};

struct in_out_quad_generator: easing_curve_generator {
    void operator()(easing_t const&) const override {}
};

struct generator_creator {
    generator_t operator()(easing_type type) const {
        switch (type) {
            case easing_type::linear:
                return std::make_shared<linear_generator>();
            case easing_type::in_quad:
                return std::make_shared<in_quad_generator>();
            case easing_type::out_quad:
                return std::make_shared<out_quad_generator>();
            case easing_type::in_out_quad:
            default:
                return std::make_shared<in_out_quad_generator>();
        }
    }
};

generator_manager::generator_manager() {
    generator_creator creator; 
   
    // one time initialization 
    generators.emplace(easing_type::linear, creator(easing_type::linear));
    generators.emplace(easing_type::in_quad, creator(easing_type::in_quad));
    generators.emplace(easing_type::out_quad, creator(easing_type::out_quad));
    generators.emplace(easing_type::in_out_quad, creator(easing_type::in_out_quad));
}

generator_t generator_manager::operator[](easing_type type) {
    return generators[type];
}

const generator_t generator_manager::operator[](easing_type type) const {
    return generators[type];
}
