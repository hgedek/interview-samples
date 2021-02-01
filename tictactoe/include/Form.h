#pragma once

#include <QWidget>
#include "Board.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Form; }
QT_END_NAMESPACE

class GameManager;

class Form : public QWidget
{
    Q_OBJECT
    
public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
  
private:
    /**
     * @brief setupConnections init connections / signal~slots 
     */
    void setupConnections() noexcept;
    /**
     * @brief setup init ui configurations 
     */
    void setup() noexcept;
    /**
     * @brief clean cleaning ui components status etc.
     */
    void clean() noexcept;
    
private slots:
    /**
     * @brief onCellClick user triggers
     */
    void onCellClick(int,int);
    /**
     * @brief onNewGameClick new-game button triggers
     */
    void onNewGameClick();
    /**
     * @brief onCellUpdate game or player object can trigger 
     */
    void onCellUpdate(Cell);
    /**
     * @brief onSucceded game object triggers
     */
    void onSucceded(Path const&);
    
    /**
     * @brief onCompleted game object triggers
     */
    void onCompleted();
    
private:
    Ui::Form *ui;
    /**
     * @brief m_gameManager Model-View-Manager [ Controller ], Layer between view and others
     */
    std::shared_ptr<GameManager> m_gameManager;
};
