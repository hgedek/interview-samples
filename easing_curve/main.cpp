#include <iostream>
#include "easing_file_parser.hpp"
#include "easing_output_generator.hpp"

constexpr auto PARAM_COUNT = 2;
constexpr auto WITH_ABSOLUTE_PATH = 3;

int main(int argc, char **argv) {

    if (argc < PARAM_COUNT) {
        std::cerr << "Invalid param count...Enter easing curve filename" << std::endl;
        return -1; 
     }
   
    try {

        if (argc == WITH_ABSOLUTE_PATH) 
            easing_output_generator::generate(easing_file_parser{}.parse(argv[1]));    
        else
            easing_output_generator::generate(easing_file_parser{}.parse(toolkit::absolute_path(argv[1])));    

    } catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    } 
     
    return 0;
}
