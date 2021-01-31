#include "easing_file_parser.hpp"
#include "toolkit.hpp"
#include <regex>

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
    enum index {
        T0 = 1,
        TMAX,
        DURATION
    };

    virtual easing_t operator()(std::string const& definition) const = 0;

};

struct easing_data_parser: data_parser {

    easing_t operator()(std::string const& definition_str) const override {

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
        auto result = std::make_unique<linear_easing_data>();
       
        // order of x_t0 and x_tmax can change in input string 
        auto fn_set_values = [&result](const std::smatch& sm) {
            if (sm[KEY] == "x_t0")
                result->definition.x_t0 = std::stoi(sm[VALUE]); 
            else if (sm[KEY] == "x_tmax")
                result->definition.x_tmax = std::stoi(sm[VALUE]);
            else if(sm[KEY] == "duration")
                result->definition.duration = std::stoi(sm[VALUE]);
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

private:
    constexpr static auto DEFINITON_LENGTH = 4;
};

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
