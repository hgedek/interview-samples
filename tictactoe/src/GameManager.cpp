#include "GameManager.h"
#include "Game.h"
#include "Player.h"
#include "Strategy.h"
#include <QDebug>

GameManager::GameManager()
{
    setupConnections();
}

std::shared_ptr<GameManager> GameManager::instance() noexcept {
    static auto ins = std::make_shared<GameManager>();
    return ins;
}

void GameManager::setupConnections() noexcept
{
    connect(&m_userPlayer, &Player::moveSelected,
            this, &GameManager::onMovePlayer);
    connect(&m_compPlayer, &Player::moveSelected,
            this, &GameManager::onMovePlayer);
    connect(&m_currentGame, &Game::succeded,
            this, &GameManager::onSucceded);
}

void GameManager::onSucceded(const Player* player, const Path &path)
{
    if (typeid(*player) == typeid(m_userPlayer))
        m_gameData.userScore += 1;
    else
        m_gameData.computerScore += 1;
    
    emit succeded(path);
}

void GameManager::newGame() noexcept {
    
    m_currentGame.reset();
    
    // one player: X other O [ modes of player sides ]
    setPlayerMoveTypes();
    // set computer player strategies
    setComputerStrategy();
    
    m_gameData.gameCount++;
    
    // if computer is X then make first move
    if (m_compPlayer.moveType() == MoveType::X)
        // X: offensive mode
        m_compPlayer.nextMove(m_currentGame.board());
}

User &GameManager::user()  noexcept{ return m_userPlayer; }

const User &GameManager::user() const noexcept { return m_userPlayer; }

Computer &GameManager::computer()  noexcept{ return m_compPlayer; }

const Computer &GameManager::computer() const  noexcept{ return m_compPlayer; }

void GameManager::setPlayerMoveTypes() noexcept {
    // Select sides for players
    if (m_gameData.gameCount % 2 == 0) {
        m_userPlayer.setMoveType(MoveType::X);
        m_compPlayer.setMoveType(MoveType::O);
    } else {
        m_userPlayer.setMoveType(MoveType::O);
        m_compPlayer.setMoveType(MoveType::X);
    }
}

void GameManager::setComputerStrategy()
{
    // for now computer bot has 2 modes
    switch (m_compPlayer.moveType()) {
    case MoveType::X:
        m_compPlayer.setStrategy(StrategyFactory::create(StrategyType::Offensive));
        break;
    case MoveType::O:
        m_compPlayer.setStrategy(StrategyFactory::create(StrategyType::Defensive));
        break;
    default:
        throw std::runtime_error("unknown movetype");
    }
}

const GameData &GameManager::gameData() const noexcept { return m_gameData; }

Game &GameManager::game()  noexcept{ return m_currentGame; }

const Game &GameManager::game() const noexcept { return m_currentGame; }

void GameManager::onMovePlayer(const Player *player)  noexcept
{
    // pass move data into game object
    m_currentGame.movePlayer(player);
    
    // make computer player next move
    if (!m_currentGame.isCompleted()) {
        if (typeid(*player) == typeid(m_userPlayer)){
            // computer makes its move
            m_compPlayer.nextMove(m_currentGame.board());
        } 
    }
}

