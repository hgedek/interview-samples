#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "header.hpp"

TEST_CASE("stringify") {

  SECTION("3x4") {

    int data[] = {2,3,4,8, 5,7,9,12,1,0,6,10};
    char output[256];

    StringifyMatrix(data, 3, 4, output);
    std::string required = "2,5,1,0,6,10,12,8,4,3,7,9";
    std::string result(output);

    REQUIRE(required == result);
  }

  SECTION("2x2"){
    int data[] = {1,2,3,4};
    
    char output[100];

    StringifyMatrix(data, 2, 2, output);

    std::string required = "1,3,4,2";
    std::string result {output};

    REQUIRE(required == result); 
  }
}


TEST_CASE("Rnd"){
  PrintRndByEleven(10);
  PrintRndByEleven(5);
  PrintRndByEleven(30);
  PrintRndByEleven(15);
}
