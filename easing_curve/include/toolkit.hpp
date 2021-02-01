#pragma once

#include "common.hpp"
#include <algorithm>
#include <unordered_map>
#include <fstream>

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif



// helper classes/structs re used to solve non related problems like convertions etc...
// they re stateless

// c++14 doesnt support std::filesystem and I didnt want to push boost::filesystem too
// this is easy way to check if a file exits but well not good with relative paths etc...
// so to be sure => please use absolute paths
struct file_system {
    static bool exists(const std::string& file_name) { 
        std::ifstream in(file_name);
        return in ? true : false;
    }
};

// place of many static helper methods like convertion, error checkings etc...
struct toolkit {
     static std::string get_input_path() {
        char buff[FILENAME_MAX];
        GetCurrentDir( buff, FILENAME_MAX );
    
        return std::string(buff) + "/../input";
    }
    
    static bool is_floating_number(std::string const& value) {
        try {
            (void)std::stof(value);
            return true; 
        } catch(...){
            return false;
        }
    }

    static void to_lower(std::string& str) {
        if (str.empty()) return;
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    }

    static std::string to_lower(std::string const& str) {
        std::string result;
        if (str.empty()) return result;        

        result.resize(str.size());
        
        std::transform(str.begin(), str.end(), result.begin(), ::tolower);
        return result;
    }

    static easing_type str_to_easing_type(std::string const& str) {
        
        static std::unordered_map<std::string, easing_type> hash_map = {
            {"linear", easing_type::linear},
            {"in_quad", easing_type::in_quad},
            {"out_quad", easing_type::out_quad},
            {"in_out_quad", easing_type::in_out_quad},
        };
        
        auto itr = hash_map.find(toolkit::to_lower(str));
        return  itr == hash_map.end() ? easing_type::none : itr->second;
    }

    static std::string easing_type_to_str(easing_type type) {

        static std::unordered_map<easing_type, std::string> hash_map = {
            {easing_type::linear, "Linear"},
            {easing_type::in_quad, "InQuad"},
            {easing_type::out_quad, "OutQuad"},
            {easing_type::in_out_quad, "InOutQuad"},
        };
        
        return hash_map[type];
    }
};

// according to definition if task a file can contain multiple curve definitions so
// for each reading we ve to check if it's a new curve definition
// to to so:
// - we can check string lenght 
// - we need to check first type string
struct easing_type_checker {
    easing_type operator()(std::string const& line) {
        const auto MIN_LENGTH = 5;

        if (line.empty() || line.length() < MIN_LENGTH)
            return easing_type::none;

        auto pos = line.find_first_of(',');
        if (pos == std::string::npos) 
            return easing_type::none;
        
        return toolkit::str_to_easing_type(line.substr(0, pos)); 
    }
};


