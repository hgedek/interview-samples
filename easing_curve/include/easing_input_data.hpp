#pragma once

#include <vector>
#include <iostream>
#include <type_traits>
#include "toolkit.hpp"

// At first I thought each curve has different data types so i decided to create so
// but because of lack of examples i couldnt decide that and using easing_input_data i will parse all
// if there is such a possibility moving from single type to polymorphic data type will be easy
// so using enum which can be used instead of polymorohism costly usage we can differentiate data types
struct easing_data {
    explicit easing_data(easing_type t = easing_type::none): type(t) {}

    easing_data(easing_data const&) = delete;
    easing_data& operator=(easing_data const&) = delete;

    easing_data(easing_data&&) = default;
    easing_data& operator=(easing_data&&) = default;

    easing_type type;
};

struct easing_input_data final: easing_data { 
    
    easing_input_data() = default;

    explicit easing_input_data(easing_type type): easing_data(type) {} 

    explicit easing_input_data(uint32_t t0, uint32_t tmax, uint32_t duration) 
        : easing_data()
        , definition{t0, tmax, duration}
        {}

    explicit easing_input_data(easing_type type,uint32_t t0, uint32_t tmax, uint32_t duration)
        : easing_data(type)
        , definition{t0, tmax, duration}
    {}

    easing_input_data(easing_input_data const&) = delete;
    easing_input_data& operator=(easing_input_data const&) = delete;

    easing_input_data(easing_input_data&&) = default;
    easing_input_data& operator=(easing_input_data&&) = default;

    constexpr bool is_valid() const { 
        return definition.x_t0 != std::numeric_limits<uint32_t>::max() &&
               definition.x_tmax != std::numeric_limits<uint32_t>::max() &&
               definition.duration != std::numeric_limits<uint32_t>::max() &&
               !time_list.empty();
    }

    friend std::ostream& operator<<(std::ostream& out, easing_input_data const& input) 
    {
        out << toolkit::easing_type_to_str(input.type) << ','
            << "x_t0=" << input.definition.x_t0 << ','
            << "x+jmax=" << input.definition.x_tmax << ','
            << "duration=" << input.definition.duration
            << '\n';

        return out;
    }

    // for members that needs to checking & controlling etc... while accessing we must use getter/setters
    // for encapsulation & information hiding reasons
    // but for others this is boilerplate coding so public acessing is better

    struct {
        uint32_t x_t0 = std::numeric_limits<uint32_t>::max();
        uint32_t x_tmax = std::numeric_limits<uint32_t>::max();
        uint32_t duration = std::numeric_limits<uint32_t>::max();
    } definition;

    std::vector<float> time_list;
};

using easing_t = easing_input_data;
using easing_ptr_t = std::unique_ptr<easing_input_data>;
using easing_list_t = std::vector<easing_input_data>;
using easing_ptr_list_t = std::vector<easing_ptr_t>;
using easing_result_data_t = std::vector<float>;


struct easing_result {
    explicit easing_result(easing_result_data_t && data): results(std::move(data)) {}

    friend std::ostream& operator<<(std::ostream& out, easing_result const& easing){
        for (auto result : easing.results) 
            out << result << '\n';
        
        return out;
    }

    easing_result_data_t results;
};


