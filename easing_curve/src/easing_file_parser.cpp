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
    
    easing_type_checker type_checker{}; 
    easing_data_parser parser{};
  
    // flag that is used to skip wrong definitions
    // if definition is wrong but it has time list we will skip time list  
    bool skip_times = true;

    // read till to a new line that has a new definition
    // skip empty lines
    // if eof => leave
    while (std::getline(in, line)) {
        if (line.empty()) 
            skip_times = true;
        else if (type_checker(line) != easing_type::none){ 
            try {
                // if parsing crashes ... but not eof => goes on
                curve_list.emplace_back(parser(line));
                skip_times = false;
             } catch(...) {
                skip_times = true;
            }
        }
        else if (toolkit::is_floating_number(line) && !skip_times)
        {
            // if float number is somehow wrong ... dont stop here
            try {
                curve_list.back().time_list.push_back(std::stof(line));
            } catch(...){}
        } 
    }

    return std::move(curve_list);
}

easing_file_parser::easing_file_parser()
    : impl(new easing_file_parser_impl())
{}

void easing_file_parser::impl_deleter::operator()(easing_file_parser_impl* obj) {
    delete obj;
}

easing_list_t easing_file_parser::parse(std::string const& file_name) const{

    if (file_name.empty())
        throw std::runtime_error("filename is empty");

    if(!file_system::exists(file_name)) 
        throw std::runtime_error("file not exists");

    return impl->parse(file_name);
}

