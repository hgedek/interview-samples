#define CATCH_CONFIG_MAIN

#include "Board.h"
#include "catch.hpp"

TEST_CASE("complete board tests","[board]") {
    Board board;
    
    REQUIRE(board.size() != 0);
    
    SECTION("size test","[size]") {
        REQUIRE(board.rowCount() == ROW_COUNT);
        REQUIRE(board.colCount() == COL_COUNT);
        REQUIRE(board.size() == (ROW_COUNT * COL_COUNT));
    }
    
    SECTION("data test", "[data]") {
        board.setValue(0, 0, MoveType::O);
        board.setValue(1, 1, MoveType::X);
        
        REQUIRE(board.value(0,0) == MoveType::O);
        REQUIRE(board.value(1,1) == MoveType::X);
        REQUIRE(board.value(2,2) == MoveType::NONE);
    }
    
    SECTION("cell test","[cell]") {
        REQUIRE(board.isEmpty() == true);
        
        board.setValue(0,0, MoveType::X);
        
        REQUIRE_FALSE(board.isEmpty());
        REQUIRE(board.cell(0,0).value == MoveType::X);
        REQUIRE(board.value(0,0) == MoveType::X);
        REQUIRE_FALSE(board.isCompleted());
    }
    
    SECTION("paths test","[path]") {
        
        REQUIRE(board.paths().size() == 8);
        
        auto const& path = board.paths().front();
        board.setValue(0, 0, MoveType::X);
        
        REQUIRE(path.count(MoveType::X)  == 1);
        REQUIRE_FALSE(path.isComplete());
        
        board.setValue(0, 1, MoveType::X);
        board.setValue(0, 2, MoveType::X);
        
        REQUIRE(path.isComplete());
    }
}
