/*
 * Computer player has 2 strategies [ X: offensive, O: defensive ]
 * 
 * Strategy is extendible
 * 
 * For now both of the strategies developed simply - not complex
 */

#pragma once

#include <memory>

/**
 * @brief The StrategyType enum
 */
enum class StrategyType {
    Offensive,
    Defensive,
    None
};

struct Board;

using position_t = std::pair<uint32_t, uint32_t>;

/**
 * @brief The Strategy class
 */
class Strategy{
public:
    Strategy() = default;
    virtual ~Strategy() = default;
    /**
     * @brief nextMove searches for next cell to move
     * @param board
     * @return 
     */
    virtual position_t nextMove(const Board& board) noexcept = 0;
};

/**
 * @brief The OffensiveStrategy class
 */
class OffensiveStrategy final: public Strategy {
public:
    OffensiveStrategy() = default;
    ~OffensiveStrategy() = default;
    position_t nextMove(const Board &board) noexcept override;
};

/**
 * @brief The DefensiveStrategy class
 * 
 * It checks all paths on board and sets cells priorities according to user play[X]
 * Selects the first priority from the cell list to select
 */
class DefensiveStrategy final: public Strategy {
public:
    DefensiveStrategy() = default;
    ~DefensiveStrategy() = default;
    /**
     * @brief nextMove search for next cell to select
     * @param board
     * @return 
     */
    position_t nextMove(const Board& board) noexcept override;  
};

/**
 * @brief The StrategyFactory class
 */
class StrategyFactory {
public:
    /**
     * @brief create factory create mothod - creates strategy instances
     * @param type
     * @return 
     */
    static std::unique_ptr<Strategy> create(StrategyType type);
};
