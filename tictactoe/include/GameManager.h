/* 02.08.2020 Hakan Gedek
 * 
 * Manager of Form - MVC ( MVM ) pattern ( almost ) 
 * 
 * The layer class between Form and others {game,player}
 * 
 * Holds game-data and controls of the flow of game between players and view
 * 
 */
#pragma once

#include <QObject>
#include "Game.h"
#include "Player.h"

/**
 * @brief The GameData struct holds summary of total gaming
 */
struct GameData {
    uint32_t userScore = 0;
    uint32_t computerScore = 0;
    uint32_t gameCount = 0;
};


/**
 * @brief The GameManager class
 */
class GameManager: public QObject {
    Q_OBJECT
    
public:
    explicit GameManager();
    ~GameManager() = default;
    
    /**
     * @brief instance singleton instance
     * @return 
     */
    static std::shared_ptr<GameManager> instance() noexcept;
  
    /**
     * @brief newGame init a new game [ clear game data ]
     */
    void newGame() noexcept;
    
public:
    /**
     * @brief user
     * @return 
     */
    User& user() noexcept;
    /**
     * @brief user
     * @return 
     */
    const User& user() const noexcept;
    /**
     * @brief computer
     * @return 
     */
    Computer& computer() noexcept;
    /**
     * @brief computer
     * @return 
     */
    const Computer& computer() const noexcept;
    /**
     * @brief gameData 
     * @return 
     */
    const GameData &gameData() const noexcept;
     /**
      * @brief game
      * @return 
      */
    Game& game() noexcept;
     /**
      * @brief game
      * @return 
      */
     const Game& game() const noexcept;
     
 private slots:
     /**
     * @brief onMovePlayer
     * @param row
     * @param col
     */
     void onMovePlayer(const Player*) noexcept; 
     
private:
    /**
     * @brief setPlayerMoveTypes set X | O for next new game - each time it changes
     */
    void setPlayerMoveTypes() noexcept;
    /**
     * @brief setComputerStrategy update computer player strategy
     */
    void setComputerStrategy();
    /**
     * @brief setupConnections ui signal slot updates
     */
    void setupConnections() noexcept;
    
private slots:
    /**
     * @brief onSucceded triggered by game object
     */
    void onSucceded(const Player*, Path const&);
    
signals:
    /**
     * @brief succeded triggers for form
     */
    void succeded(const Path&);
    
private:
    /**
     * @brief m_userPlayer 
     */
    User m_userPlayer;
    /**
     * @brief m_compPlayer
     */
    Computer m_compPlayer;
    /**
     * @brief m_currentGame
     */
    Game m_currentGame;
    /**
     * @brief m_gameData
     */
    GameData m_gameData;
};

