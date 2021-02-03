#include "Form.h"
#include "ui_Form.h"
#include "GameManager.h"
#include "Player.h"
#include "Game.h"
#include <QMessageBox>

Form::Form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
    , m_gameManager(GameManager::instance())
{
    ui->setupUi(this);
    
    // initialize UI and connections 
    setup();
    setupConnections();
}

void Form::setup() noexcept {
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    setFixedSize(this->width(),this->height());
    
    // set label for cellwidget so we can use pixmap
    for (auto i = 0; i < ui->tableWidget->rowCount(); ++i){
        for (auto j = 0; j < ui->tableWidget->columnCount(); ++j) {
            auto label = new QLabel;
            label->setScaledContents(true);
            label->setMargin(10);
            label->setAlignment(Qt::AlignHCenter);
            ui->tableWidget->setCellWidget(i, j, label);
        }
    }
    
    // default: its not enabled
    ui->tableWidget->setEnabled(false);
}

void Form::setupConnections() noexcept {
    connect(ui->tableWidget, &QTableWidget::cellClicked,
            this, &Form::onCellClick);
    connect(ui->newGameButton, &QPushButton::clicked,
            this, &Form::onNewGameClick);
    connect(&m_gameManager->game(),&Game::cellUpdated,
            this, &Form::onCellUpdate);
    connect(&m_gameManager->game(), &Game::completed,
            this, &Form::onCompleted);
    connect(m_gameManager.get(), &GameManager::succeded,
            this, &Form::onSucceded);
}

void Form::onCellClick(int row, int col) {
    // if a game exists make user next-move
    if (m_gameManager->game().isCompleted())
        return;
    
    if (m_gameManager->game().isCellEmpty(row, col)) {
         m_gameManager->user().select(row, col);
    }
}

void Form::onNewGameClick() {
    // if game is not finished or not empty check user to restart game
    if (!m_gameManager->game().isEmpty() && !m_gameManager->game().isCompleted()){
        int ret = QMessageBox::warning(this, tr("Leave"),"Leave current game ?",
                                       QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::No)
            return;
    }
    
    // clean X & O's from table
    clean();
    ui->tableWidget->setEnabled(true);
    
    // start a new game
    m_gameManager->newGame();
}

void Form::clean() noexcept {
    for (auto i = 0; i < ui->tableWidget->rowCount(); ++i){
        for (auto j = 0; j < ui->tableWidget->columnCount(); ++j){
            QLabel* label = qobject_cast<QLabel*>(ui->tableWidget->cellWidget(i,j));
            label->clear();
            label->setStyleSheet("");
        }
    } 
}

void Form::onCellUpdate(Cell cell) {
    switch(cell.value) {
    case MoveType::X:
        qobject_cast<QLabel*>(
            ui->tableWidget->cellWidget(cell.row, cell.col))->setPixmap(QPixmap(":/icons/x.png"));
        break;
    case MoveType::O:
        qobject_cast<QLabel*>(
            ui->tableWidget->cellWidget(cell.row, cell.col))->setPixmap(QPixmap(":/icons/o.png"));        
        break;
    default:
        throw std::runtime_error("unknown move type");
    }
}

void Form::onSucceded(const Path& path)
{
    for (const auto& p : path.data){
        
        QLabel* label = qobject_cast<QLabel*>(ui->tableWidget->cellWidget( p.get().row,
                                                                          p.get().col));
        label->setStyleSheet("background-color: red;");
    }
    
    // update score labels
    ui->playerScore->setText(QString::number(m_gameManager->gameData().userScore));
    ui->computerScore->setText(QString::number(m_gameManager->gameData().computerScore));
}

void Form::onCompleted()
{
    ui->tableWidget->setEnabled(false);
}

Form::~Form()
{
    delete ui;
}

