#include "easing_curve_generator.hpp"

#define FILL_AND_RETURN_RESULTS \
        easing_result_data_t results; \
\
        for (auto t : obj.time_list) \
           results.emplace_back(f(t)); \
\
        return std::move(easing_result{std::move(results)});

struct linear_generator: easing_curve_generator {
    easing_result operator()(easing_t const& obj) const override {
       // f(t) = x_t0 + t * (x_tmax - t_t0)/d;
        auto f = [&obj](auto t) {
            return obj.definition.x_t0 + t * 
                ( obj.definition.x_tmax - obj.definition.x_t0)/obj.definition.duration; 
        };
        
        FILL_AND_RETURN_RESULTS;
    }
};

// equations from here:
// https://www.gizma.com/easing/
struct in_quad_generator: easing_curve_generator {
    easing_result operator()(easing_t const& obj) const override {
        // t /= d;
        // f(t) =  t * t * ( x_tmax-x_t0) + x_t0

        auto f = [&obj](auto t) {
            t /= obj.definition.duration;
            
            return t * t * (obj.definition.x_tmax-obj.definition.x_t0) + 
                    obj.definition.x_t0; 
        };

        FILL_AND_RETURN_RESULTS;
    }
};

struct out_quad_generator: easing_curve_generator {
    easing_result operator()(easing_t const& obj) const override {
        // t /= d
        // f(t) = t * (t -2 ) * (x_t0 - x_tmax) + x_t0 

        auto f = [&obj](auto t) {
            t /= obj.definition.duration;
            
            return t * (t-2) * (obj.definition.x_t0 - obj.definition.x_tmax) + 
                    obj.definition.x_t0; 
        };

        FILL_AND_RETURN_RESULTS;
    }
};

struct in_out_quad_generator: easing_curve_generator {
    easing_result operator()(easing_t const& obj) const override {
        // t /= d/2
        // if t < 1
        // f(t) = in_quad()
        // t--;
        // f(t) = (x_t0 - x_tmax)/2 * (t*(t-2) -1) + x_t0

        auto f = [&obj](auto t) {
            t /= (obj.definition.duration/2);
            if ( t < 1) 
                return t * t * (obj.definition.x_tmax-obj.definition.x_t0) + 
                    obj.definition.x_t0; 
            t--;
            return (obj.definition.x_t0 - obj.definition.x_tmax)/2 * (t * (t-2) - 1) +
                    obj.definition.x_t0; 
        };

        FILL_AND_RETURN_RESULTS;
    }
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

