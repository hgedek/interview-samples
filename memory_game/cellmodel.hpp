#ifndef CELLMODEL_HPP
#define CELLMODEL_HPP

#include "cell.hpp"
#include <QAbstractListModel>
#include <QList>
#include <QQuickItem>
#include <thread>

class CellModel : public QAbstractListModel
{
    Q_OBJECT
    
  public:
    explicit CellModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    bool isIndexValid(const QModelIndex &) const;

    void initialize(uint32_t imageCount) noexcept;
    /**
     * @brief shuffle using std::shuffle -> randomize cells
     */
    void shuffle() noexcept;

  public:
    /**
     * @brief isCompleted if game is completed close it
     * @return
     */
    Q_INVOKABLE bool isCompleted() const;

    /**
     * @brief isEqual is previous and current indexed cells same ?
     * @param previous
     * @param current
     * @return
     */
    Q_INVOKABLE bool isEqual(int previous, int current) const;

    /**
     * @brief updateCellCheckedStatus if current cell clicked update status
     * @param index
     * @param value
     */
    Q_INVOKABLE void updateCellCheckedStatus(int index, bool value);

    /**
     * @brief isCellChecked return true if indexed cell is checked
     * @param index
     * @return
     */
    Q_INVOKABLE bool isCellChecked(int index) const;

    /**
     * @brief setSelected modelList keeps track of last selected qml cell
     * @param selected
     */
    Q_INVOKABLE void setSelected(QQuickItem *selected) { _selected = selected; }

    Q_INVOKABLE QQuickItem *getSelected() const { return _selected; }

    /**
     * @brief reset reset game
     */
    Q_INVOKABLE void reset();

    Q_INVOKABLE int size() const { return _cellList.size(); }
#ifdef QT_DEBUG
    void printCellUrls() const;
    void printCellIds() const;
#endif

  private:
    /**
     * @brief createCellId using static id we create cells using same id for 2
     * cells
     * @return
     */
    static uint32_t createCellId() { return _id++; }

  private:
    /**
     * @brief _cellList model list
     */
    QList<Cell> _cellList;
    /**
     * @brief _selected last selected qml cell object
     */
    QQuickItem *_selected;

    /**
     * @brief _id unique id for cells - we can use UUID but ...
     */
    static inline uint32_t _id = 0;
};

#endif // CELLMODEL_HPP
