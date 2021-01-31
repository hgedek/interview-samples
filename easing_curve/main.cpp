#include <iostream>
#include "easing_file_parser.hpp"

constexpr auto PARAM_COUNT = 2;

int main(int argc, char **argv) {

    if (argc < PARAM_COUNT) {
        std::cerr << "Invalid param count...Enter easing curve filename" << std::endl;
        return -1; 
    }
    
    (void)easing_file_parser{}.parse(argv[1]);    
     
    return 0;
}
