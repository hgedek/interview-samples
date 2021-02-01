#include "catch.hpp"
#include "Strategy.h"
#include "Board.h"
#include <QDebug>

TEST_CASE("defensive test", "[strategy]") {
    Board board;
    auto strategy = StrategyFactory::create(StrategyType::Defensive);
    
    REQUIRE(board.size() == ROW_COUNT * COL_COUNT);
    REQUIRE(strategy != nullptr);
    
    board.setValue(1, 1, MoveType::X);
    auto pos = strategy->nextMove(board);
    
    REQUIRE((pos.first >= 0 and pos.first < ROW_COUNT));
    REQUIRE((pos.second >= 0 and pos.second < COL_COUNT));
    REQUIRE(pos != position_t{1,1});
}


TEST_CASE("offensive test", "[strategy]") {
    Board board;
    auto strategy = StrategyFactory::create(StrategyType::Offensive);
    
    REQUIRE(board.size() == ROW_COUNT * COL_COUNT);
    REQUIRE(strategy != nullptr);
    
    board.setValue(0, 0, MoveType::X);
    board.setValue(2, 0, MoveType::O);
    
    auto pos = strategy->nextMove(board);
    
    REQUIRE((pos.first >= 0 and pos.first < ROW_COUNT));
    REQUIRE((pos.second >= 0 and pos.second < COL_COUNT));
    REQUIRE(pos != position_t{0,0});
    REQUIRE(pos != position_t{1,0});
    REQUIRE((pos == position_t{1,0} or pos == position_t{0, 1}));
    
}

