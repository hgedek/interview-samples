#pragma once

#include "easing_input_data.hpp"

class easing_file_parser_impl;

class easing_file_parser {
public:
    easing_file_parser();
    easing_file_parser(easing_file_parser const&) = delete;
    easing_file_parser(easing_file_parser&& ) = delete;
    easing_file_parser& operator=(easing_file_parser const&) = delete;
    easing_file_parser& operator=(easing_file_parser&&) = delete;

    easing_list_t parse(std::string const&) const;
    
#ifdef TESTIING
    
    easing_list_t parse(std::vector<std::string> const&) const;

#endif 

    struct impl_deleter {
        void operator()(easing_file_parser_impl* obj);
    };

    std::unique_ptr<easing_file_parser_impl,impl_deleter> impl;
};

