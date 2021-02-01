#include "cellmodel.hpp"
#include <QDebug>
#include <algorithm>
#include <random>

CellModel::CellModel(QObject *parent) : QAbstractListModel(parent) {}

void CellModel::initialize(uint32_t imageCount) noexcept {

    // create path of image files according to resource file
    beginInsertRows(QModelIndex{}, 0, imageCount * 2);

    for (uint32_t i = 0; i < imageCount; ++i) {

        Cell cell{QUrl(QString("../images/%1").arg(i)), createCellId()};
        // put 2 of each
        _cellList.push_back(cell);
        _cellList.push_back(cell);
    }

    endInsertRows();
}

bool CellModel::isCompleted() const {
    return std::all_of(_cellList.begin(), _cellList.end(),
                       [](const Cell &cell) { return cell.isChecked(); });
}

bool CellModel::isEqual(int previous, int current) const {
    if (previous < 0 || current < 0 || previous > _cellList.size() ||
        current > _cellList.size())
        return false;

    if (_cellList.at(previous) == _cellList.at(current))
        return true;

    return false;
}

void CellModel::updateCellCheckedStatus(int index, bool value) {

    if (index < 0 || index > _cellList.size())
        throw std::out_of_range("index out of range");

    _cellList[index].setChecked(value);
}

bool CellModel::isCellChecked(int index) const {
    if (index < 0 || index > _cellList.size())
        throw std::out_of_range("index out of range");

    return _cellList.at(index).isChecked();
}

void CellModel::reset() {

    auto count = _cellList.size() / 2;

    beginRemoveRows(QModelIndex{}, 0, _cellList.size() - 1);
    _cellList.erase(_cellList.begin(), _cellList.end());
    endRemoveRows();

    initialize(count);

    setSelected(nullptr);
}

void CellModel::shuffle() noexcept {

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(_cellList.begin(), _cellList.end(), g);
}

int CellModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);

    return _cellList.size();
}

QVariant CellModel::data(const QModelIndex &index, int role) const {
    if (!isIndexValid(index)) {
        return QVariant();
    }

    const auto &cell = _cellList.at(index.row());

    switch (role) {
    case Qt::DisplayRole:
        return cell.getUrl();
    default:
        return QVariant();
    }
}

bool CellModel::isIndexValid(const QModelIndex &index) const {
    if (index.row() < 0 || index.row() >= rowCount() || !index.isValid()) {
        return false;
    }
    return true;
}

QHash<int, QByteArray> CellModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "url";
    return roles;
}

#ifdef QT_DEBUG
void CellModel::printCellUrls() const {
    Cell cell;
    foreach (cell, _cellList)
        qDebug() << cell.getUrl();
}

void CellModel::printCellIds() const {
    for (const auto &cell : _cellList)
        qDebug() << cell.getId();
}

#endif
