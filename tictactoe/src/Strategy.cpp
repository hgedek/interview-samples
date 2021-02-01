#include "Strategy.h"
#include "Board.h"
#include <random>
#include <QDebug>

/**
 * used as random [row,col] generator
 */
template <size_t MIN = 0, size_t MAX = 0, typename T = uint32_t>
struct RandomDevice {
    std::random_device rd;
    std::mt19937 g;
    std::uniform_int_distribution<T> gen; // uniform, unbiased
    /**
     * @brief RandomDevice
     */
    constexpr explicit RandomDevice(): g(rd()), gen(MIN, MAX) {}
    /**
     * @brief generate returns a random number between [min-max]
     * @return 
     */
    constexpr T generate() {
        return gen(g);
    }
};

/** 
 * @brief The Node struct used to find next-move in path
 */
struct Node {
    /**
     * @brief value
     */
    int32_t value = 0;
    /**
     * @brief pos
     */
    position_t pos;
    /**
     * @brief path
     */
    const Path* path;
    
    // operator overloadings
    friend bool operator<(const Node& left, const Node& right){
        return left.value < right.value;
    }
    
    friend bool operator==(const Node& left, const Node& right) {
        return left.value == right.value && left.pos == right.pos;
    }
    
    friend bool operator!=(const Node& left, const Node& right)  {
        return  left.value != right.value && left.pos != right.pos;
    }
    
    friend bool operator>(const Node& left, const Node& right) {
        return left.value > right.value;
    }
};

/*
 * Searches for user X values on paths and tries to prevent its movements
 * Each empty cell is given a number ( count of X ) so we try to select
 * max valued cells to move
 */
position_t DefensiveStrategy::nextMove(const Board &board) noexcept {
    
    std::vector<Node> nodes(ROW_COUNT * COL_COUNT);
    
    // create nodes array to find next cell to move
    for (auto const& path:  board.paths()) {
        for (const auto& c: path.data) {
            if (c.get().value == MoveType::NONE) {
                auto index = c.get().row * ROW_COUNT + c.get().col;
                nodes[index].pos = {c.get().row, c.get().col};
                nodes[index].value += path.count(MoveType::X); // add 10 to make it first in queue
                nodes[index].path = &path;
            }
        }
    }
    
    // descending sorting to get max points
    std::sort(nodes.begin(), nodes.end(), std::greater<>());
    
    // find the max pointed section of nodes
    // use for randomize it
    auto low = std::lower_bound(nodes.begin(), nodes.end(), nodes.front(), std::greater<>());          
    auto up = std::upper_bound(nodes.begin(), nodes.end(), nodes.front(), std::greater<>());
    
    // randomize the max pointed section so different moves
    std::shuffle(low,up,RandomDevice{}.g);
    
    return nodes.front().pos;
}

/*
 * Searches own X values on cells and selects possible paths 
 * Each cell holds a int number and possible ones holds larger values
 * Using Node structs we select them and after sorting we randomly select one
 */
position_t OffensiveStrategy::nextMove(const Board &board) noexcept
{
    // new started game 
    if (board.isEmpty()) {
        return {
            // create random [row,col] for each start
            RandomDevice<0,ROW_COUNT-1>{}.generate(),
            RandomDevice<0,COL_COUNT-1>{}.generate()
        };
    } else {
         std::vector<Node> nodes(ROW_COUNT * COL_COUNT);
         // create nodes array to find next cell to move
         for (auto const& path:  board.paths()) {       
             for (const auto& c: path.data) {
                auto index = c.get().row * ROW_COUNT + c.get().col;
                nodes[index].pos = {c.get().row, c.get().col};
                nodes[index].path = &path;
                
                 if (c.get().value == MoveType::NONE)
                     nodes[index].value += (path.count(MoveType::X) - path.count(MoveType::O)); // add 10 to make it first in queue
                 else
                     nodes[index].value -= 100;
             }          
         }
         
         // descending sorting to get max points
         std::sort(nodes.begin(), nodes.end(), std::greater<>());
         
         // find the max pointed section of nodes
         // use for randomize it
         auto low = std::lower_bound(nodes.begin(), nodes.end(), nodes.front(), std::greater<>());          
         auto up = std::upper_bound(nodes.begin(), nodes.end(), nodes.front(), std::greater<>());
         
         // check path completion possibility
         // if 1 step to check-mate then return it
         for (auto itr = low; itr < up; ++itr) {
             if (itr->path && itr->path->count(MoveType::X) == (CHECK_COUNT -1 ))
                 return itr->pos;
         }
         
         // randomize the max pointed section so different moves
         std::shuffle(low,up,RandomDevice{}.g);
         return nodes.front().pos;
    }
}

std::unique_ptr<Strategy> StrategyFactory::create(StrategyType type)
{
    switch (type) {
    case StrategyType::Defensive:
        return std::make_unique<DefensiveStrategy>();
    case StrategyType::Offensive:
        return std::make_unique<OffensiveStrategy>();
    default:
        throw std::runtime_error("unknown strategy type");
    }
}


