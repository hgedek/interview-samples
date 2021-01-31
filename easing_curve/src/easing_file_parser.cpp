#include "easing_file_parser.hpp"
#include "easing_data_parser.hpp"
#include "toolkit.hpp"

class easing_file_parser_impl {
public:
    easing_list_t parse(std::string const& file_name) const;
    
#ifdef TESTING
    easing_list_t parse(std::vector<std::string> const& lines) const;
#endif
};

easing_list_t easing_file_parser_impl::parse(std::string const& file_name) const {

    std::ifstream in(file_name);
    std::string line;

    easing_list_t curve_list;
    
    easing_data_parser parser{};

    while (std::getline(in, line)) {
        try {
            if (line.empty())
                continue;
            else if (toolkit::str_to_easing_type(line) != easing_type::none)
                curve_list.emplace_back(parser(line));
            else if (toolkit::is_floating_number(line)) 
                curve_list.back().time_list.push_back(std::stof(line));
        } catch(std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    return std::move(curve_list);
}

easing_file_parser::easing_file_parser()
    : impl(new easing_file_parser_impl())
{}

easing_list_t easing_file_parser::parse(std::string const& file_name) const{

    if (file_name.empty())
        throw std::runtime_error("filename is empty");

    if(!file_system::exists(file_name)) 
        throw std::runtime_error("file not exists");

    return impl->parse(file_name);
}

#ifdef TESTING

easing_list_t easing_file_parser::parse(std::vector<std::string> const& lines) {
    if (lines.empty())
        throw std::runtime_error("list is empty");

    return impl->parse(lines);
}

#endif
