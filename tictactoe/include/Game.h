/* 01.08.2020 Hakan Gedek
 * 
 * Game model. Includes board and also acts as a layer between manager & board
 * 
 * Controls events, status and flow of game
 * 
 * Controls logic of game flow
 */

#pragma once

#include <QObject>
#include "Board.h"


class Player;

class Game: public QObject {
    Q_OBJECT
    
public:
    explicit Game(QObject *parent = nullptr);
    ~Game() = default;
    
    /**
     * @brief isCompleted checks if game is ended
     * @return 
     */
    bool isCompleted() const;
    
    /**
     * @brief isEmpty
     * @return 
     */
    bool isEmpty() const;
    /**
     * @brief IsCellEmpty checks if row|col value is None 
     * @param row
     * @param col
     * @return 
     */
    bool isCellEmpty(int row, int col) const;
    /**
     * @brief reset
     */
    void reset();
    /**
     * @brief board
     * @return 
     */
    const Board& board() const;
    
    /**
     * @brief movePlayer select a cell according to row|col inputs for player
     * @param row
     * @param col
     */
    void movePlayer(const Player*);
    
private:
    /**
     * @brief checkForSuccess controls if any user succeeded 
     * @return 
     */
    std::tuple<bool,Path> checkForSuccess() const;

signals:
    /**
     * @brief cellUpdated triggers after player edit a cell
     */
    void cellUpdated(const Cell&);
    /**
     * @brief succeded triggers after a player wins
     */
    void succeded(const Player*, const Path&);
    /**
     * @brief completed triggers after ends without a win
     */
    void completed();
private:
    Board m_board;
    bool m_completed = false;
};
