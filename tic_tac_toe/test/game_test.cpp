#include "catch.hpp"
#include "Game.h"
#include "Player.h"

TEST_CASE("complete game tests", "[game]") {
    
    Game game;
    
    REQUIRE(game.isEmpty());
    
    SECTION("move player", "[move]") {
        
        REQUIRE(game.board().value(1,1) == MoveType::NONE);
        REQUIRE(game.board().value(1,2) == MoveType::NONE);
        
        User user;
        user.setMoveType(MoveType::X);
        user.select(1, 1);
        game.movePlayer(&user);
        REQUIRE(game.board().value(1,1) == MoveType::X);
        
        user.select(1, 2);
        game.movePlayer(&user);
        REQUIRE(game.board().value(1,2) == MoveType::X);
    }
}
