/* 02.08.2020 Hakan Gedek
 * 
 * Game has 2 players - User & Computers. Models both of them.
 * 
 * A player can select an empty cell [MoveType::NONE]
 * 
 * Computer players uses 2 strategies and according to its algorithm it decides to nextmove
 */

#pragma once

#include <QObject>
#include "Common.h"
#include "Strategy.h"

struct Board;

/**
 * @brief The Player class
 */
class Player: public QObject {
    Q_OBJECT
    
protected:
    Player(QObject* parent = nullptr);
    Player(MoveType mvType, QObject* parent = nullptr);
    
    virtual ~Player() = default;
    
public:
    /**
     * @brief moveType returns move type
     * @return 
     */
    MoveType moveType() const noexcept;
    
    /**
     * @brief setMoveType move type of player = changes in order
     * @param value
     */
    void setMoveType(MoveType value) noexcept;

    /**
     * @brief select select a cell [row,col]
     * @param row
     * @param col
     */
    void select(int row, int col) noexcept;
    
    /**
     * @brief lastSelectedPosition
     * @return 
     */
    position_t lastSelectedPosition() const noexcept;
    
signals:
    /**
     * @brief moveSelected triggers this player selected a cell
     */
    void moveSelected(const Player*);
    
private:
    MoveType m_moveType;
    position_t m_lastSelect;
};

/**
 * @brief The User class
 */
class User final: public Player {
public:
    User(QObject* parent = nullptr);
    ~User() = default;
};

/**
 * @brief The Computer class
 */
class Computer final: public Player {
public:
    Computer(QObject* parent = nullptr);
    /**
     * @brief nextMove pass move data into signal - doesnt hold move data
     */
    void nextMove(const Board&);
    /**
     * @brief setStragety 
     */
    void setStrategy(std::unique_ptr<Strategy>) noexcept;
    /**
     * @brief strategy
     * @return 
     */
    const Strategy* strategy() const noexcept;
    
private:
    
    std::unique_ptr<Strategy> m_strategy;
};

