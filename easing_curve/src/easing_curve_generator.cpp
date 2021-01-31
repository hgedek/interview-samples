#include "easing_curve_generator.hpp"


struct linear_generator {
    void operator()(easing_t const&){}
};

struct in_quad_generator {
    void operator()(easing_t const&) {}
};

struct out_quad_generator {
    void operator()(easing_t const&) {}
};

struct in_out_quad_generator {
    void operator()(easing_t const&) {}
};

class easing_curve_generator_impl {
public:
    easing_curve_generator_impl(); 
    
    void operator()(easing_list_t const& vl);

private:
    using generator_func_t = std::function<void(easing_t const&)>;
    std::unordered_map<easing_type, generator_func_t> generators;
};

easing_curve_generator_impl::easing_curve_generator_impl(){
    generators.insert({
        {easing_type::linear, linear_generator{}},
        {easing_type::in_quad, in_quad_generator{}},
        {easing_type::out_quad, out_quad_generator{}},
        {easing_type::in_out_quad, in_out_quad_generator{}} 
    });
}

void easing_curve_generator_impl::operator()(easing_list_t const& vl) {
    for (const auto& item : vl) {
        auto generator = generators.find(item.type);
        if (generator != generators.end())
           (generator->second)(item);
    }
}

easing_curve_generator::easing_curve_generator()
    : impl(new easing_curve_generator_impl()){
}

void easing_curve_generator::operator()(easing_list_t const& vl) {
    impl->operator()(vl);
}
