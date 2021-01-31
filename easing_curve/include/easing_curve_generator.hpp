#pragma once

#include "easing_input_data.hpp"
#include <functional>
#include <unordered_map>

class easing_curve_generator_impl;

class easing_curve_generator {
public:
    easing_curve_generator& intance(){
        static easing_curve_generator instance;
        return instance;
    }

    void operator()(easing_list_t const&);

private:
    easing_curve_generator();
   
    struct deleter {
        void operator()(easing_curve_generator_impl* impl);
    }; 

    std::unique_ptr<easing_curve_generator_impl, deleter> impl;
    
    using generator_func_t = std::function<void(easing_t const&)>;
    std::unordered_map<easing_type, generator_func_t> generators;
};

