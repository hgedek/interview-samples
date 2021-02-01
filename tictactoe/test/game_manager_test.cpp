#include "catch.hpp"
#include "GameManager.h"

TEST_CASE("complete gamemanager tests","[game-manager]") {
    auto ins = GameManager::instance();
    
    REQUIRE(ins != nullptr);
    
    SECTION("new-game","[manager]") {
        
        REQUIRE(ins->user().moveType() == MoveType::NONE);
        REQUIRE(ins->computer().moveType() == MoveType::NONE);
        REQUIRE(ins->game().isEmpty());
        REQUIRE(ins->gameData().gameCount == 0);
        REQUIRE(ins->computer().strategy() == nullptr);
        
        ins->newGame();
        
        REQUIRE(ins->user().moveType() == MoveType::X);
        REQUIRE(ins->computer().moveType() == MoveType::O);
        REQUIRE(ins->game().isEmpty());
        REQUIRE(ins->gameData().gameCount == 1);
        REQUIRE(ins->computer().strategy() != nullptr);  
    }
}
