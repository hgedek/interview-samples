#include "catch.hpp"
#include "Player.h"
#include "Board.h"


TEST_CASE("user player tests", "[player]") {
    User user;
    
    SECTION("move type") {
        REQUIRE(user.moveType() == MoveType::NONE);
        user.setMoveType(MoveType::X);
        REQUIRE(user.moveType() == MoveType::X);
        user.setMoveType(MoveType::O);
        REQUIRE(user.moveType() == MoveType::O);
    }
    
    SECTION("selection of cell") {
        REQUIRE(user.lastSelectedPosition() == position_t{-1,-1});
        user.select(1, 1);
        REQUIRE(user.lastSelectedPosition() == position_t{1,1});
    }
}

TEST_CASE("computer player tests", "[player]") {
    
    Computer computer;
    
    SECTION("move type") {
        REQUIRE(computer.moveType() == MoveType::NONE);
        computer.setMoveType(MoveType::X);
        REQUIRE(computer.moveType() == MoveType::X);
        computer.setMoveType(MoveType::O);
        REQUIRE(computer.moveType() == MoveType::O);
    }
    
    SECTION("selection of cell") {
        REQUIRE(computer.lastSelectedPosition() == position_t{-1,-1});
        computer.select(1, 1);
        REQUIRE(computer.lastSelectedPosition() == position_t{1,1});
        computer.select(2, 2);
        REQUIRE(computer.lastSelectedPosition() == position_t{2,2});
    }
    
    SECTION("selection of strategy") {
        
        REQUIRE(computer.strategy() == nullptr);
        computer.setStrategy(StrategyFactory::create(StrategyType::Offensive));
        REQUIRE(computer.strategy() != nullptr);
        REQUIRE(typeid(*computer.strategy()) == typeid(OffensiveStrategy));
        computer.setStrategy(StrategyFactory::create(StrategyType::Defensive));
        REQUIRE(computer.strategy() != nullptr);
        REQUIRE(typeid(*computer.strategy()) == typeid(DefensiveStrategy));  
    }
    
    SECTION("move of player") {
        Board board;
        
        SECTION("offensive") {
            REQUIRE(computer.lastSelectedPosition() == position_t{-1,-1});
            computer.setStrategy(StrategyFactory::create(StrategyType::Offensive));
            computer.nextMove(board);
            REQUIRE(computer.lastSelectedPosition() != position_t{-1,-1});
        }
        
        SECTION("defensive") {
            REQUIRE(computer.lastSelectedPosition() == position_t{-1,-1});
            computer.setStrategy(StrategyFactory::create(StrategyType::Defensive));
            computer.nextMove(board);
            REQUIRE(computer.lastSelectedPosition() != position_t{-1,-1});
        }
    }
}
