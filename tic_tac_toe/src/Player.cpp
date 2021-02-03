#include "Player.h"
#include "Board.h"
#include "Strategy.h"
#include <QDebug>

Player::Player(QObject *parent)
    : QObject(parent)
    , m_moveType(MoveType::NONE)
    , m_lastSelect{-1,-1} {}

Player::Player(MoveType value, QObject *parent)
    :  QObject(parent)
    , m_moveType(value)
    , m_lastSelect{-1,-1} 
{
}

MoveType Player::moveType() const noexcept { return m_moveType; }

void Player::setMoveType(MoveType value)  noexcept { m_moveType = value; }

void Player::select(int row, int col) noexcept {
    m_lastSelect = std::make_pair(row, col);
    emit moveSelected(this);
}

position_t Player::lastSelectedPosition() const noexcept{
    return m_lastSelect;
}


User::User(QObject *parent): Player(parent){}

Computer::Computer(QObject *parent)
    : Player(parent)
    , m_strategy{nullptr} {}

void Computer::setStrategy(std::unique_ptr<Strategy> strategy) noexcept
{
    if (m_strategy)
        m_strategy.reset(nullptr);
    
    m_strategy = std::move(strategy);
}

const Strategy *Computer::strategy() const noexcept {
    return m_strategy.get();
}

void Computer::nextMove(const Board& board) {
    if (!m_strategy)
        throw std::runtime_error("strategy not found");
    
    auto [row, col] = m_strategy->nextMove(board);
    select(row, col);
}

