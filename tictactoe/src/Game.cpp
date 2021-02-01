#include "Game.h"
#include "Player.h"
#include <QDebug>
#include <QPushButton>

Game::Game(QObject *parent): QObject(parent){}

bool Game::isEmpty() const {
    return m_board.isEmpty();
}

bool Game::isCompleted() const {
    return m_completed;
}

void Game::movePlayer(const Player *player)
{
    auto [row,col] = player->lastSelectedPosition();
    m_board.setValue(row, col, player->moveType());
    
    emit cellUpdated(m_board.cell(row, col));
    
    if ( auto [result, path] = checkForSuccess(); result) {
        m_completed = true;
        emit succeded(player, path);
    }
    else if(m_board.isCompleted()) {
        m_completed = true;
        emit completed();
    }
}

bool Game::isCellEmpty(int row, int col) const {
    return m_board.value(row,col) == MoveType::NONE;
}

void Game::reset()
{
    m_board.clean();
    m_completed = false;
}

std::tuple<bool,Path> Game::checkForSuccess() const {
    for (const auto& path : m_board.paths())
        if (path.isComplete())
            return std::make_tuple(true, path);
    
    return std::make_tuple(false,Path{});
}


const Board &Game::board() const { return m_board; }
