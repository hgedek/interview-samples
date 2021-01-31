#pragma once

#include "easing_input_data.hpp"
/*
 * kept this here for supportign if input data types are different for each curve 
 * we will need a different parser 
 *
 * [easing_type, parser] => was used at first but document & examples shows that format is same ? 
 */

struct data_parser {
    // std::smatch data index
    // 0 : all group { x_t0 = value }
    // 1 : left { x_t0 }
    // 2 : right { value }
    enum {
        KEY = 1,
        VALUE
    };

   // enum anonymous constants re well used as readable indexs
   // instead of using 0,1,2 ... on datas using enum :: Value's re always better 
    enum {
        T0 = 1,
        TMAX,
        DURATION
    };

    virtual easing_t operator()(std::string const& definition) const = 0;
};


struct easing_data_parser: data_parser {

    easing_t operator()(std::string const& definition_str) const override;

private:
    constexpr static auto DEFINITON_LENGTH = 4;
};

