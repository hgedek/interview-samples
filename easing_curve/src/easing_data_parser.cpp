#include "easing_data_parser.hpp"
#include <regex>

easing_t easing_data_parser::operator()(std::string const& definition_str) const 
{
    // splitting into vector of string 
    std::vector<std::string> definition_list;

    auto split = [definition_str, &definition_list] {
        // default delim = , 
        const std::regex re{","};
        
        // token parser can give -1, 0, 1, 2... from a pattern
        std::sregex_token_iterator rit {
                                    definition_str.cbegin(), 
                                    definition_str.cend(),
                                    re,
                                    -1};
        std::sregex_token_iterator rend;

        std::copy(rit, rend, std::back_inserter(definition_list));
   
       // I think size should be 4 right ?  
        if(definition_list.size() != DEFINITON_LENGTH)
            throw std::runtime_error("input error. definition is not correct");
    }; 
  
    // split definition string into parts 
    split();

    // const aliasing the group datas in line
    const std::string& first_group = definition_list.at(index::T0);
    const std::string& second_group = definition_list.at(index::TMAX);
    const std::string& duratin_group = definition_list.at(index::DURATION);

    // initializing of esing data from definition string
    easing_input_data result; 
    // order of x_t0 and x_tmax can change in input string 
    auto fn_set_values = [&result](const std::smatch& sm) {
        if (sm[KEY] == "x_t0")
            result.definition.x_t0 = std::stoi(sm[VALUE]); 
        else if (sm[KEY] == "x_tmax")
            result.definition.x_tmax = std::stoi(sm[VALUE]);
        else if(sm[KEY] == "duration")
            result.definition.duration = std::stoi(sm[VALUE]);
        else
            throw std::runtime_error("unknown key input");
    };

    // pattern for extracting A=B
    const std::regex re {R"((\w+)=(\d+))"};
    std::smatch sm;
    // extract t0
    std::regex_search(first_group, sm, re);
    fn_set_values(sm);

    // extract tmax
    std::regex_search(second_group, sm, re);
    fn_set_values(sm);

    // extract duration
    std::regex_search(duratin_group, sm, re);
    fn_set_values(sm);

    return std::move(result);
}

