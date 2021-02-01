#pragma once

#include "easing_input_data.hpp"
#include <memory>
#include <unordered_map>

struct easing_curve_generator {
    virtual void operator()(easing_t const&) const = 0;
};

using generator_t = std::shared_ptr<easing_curve_generator>;

class generator_manager {
public:
    static generator_manager& instance() {
        static generator_manager instance;
        return instance;
    }

    const generator_t operator[](easing_type) const;

    generator_t operator[](easing_type);

private:
    generator_manager();

private:
    mutable std::unordered_map<easing_type, generator_t> generators;
};

