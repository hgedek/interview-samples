#ifndef CELL_HPP
#define CELL_HPP

#include <QDebug>
#include <QUrl>
#include <QUuid>

class Cell {
  public:
    Cell() = default;
    Cell(QUrl &&url, uint32_t id) : _url(std::move(url)), _id(id) {}
    ~Cell() = default;

    void reset() { _checked = false; }

    const uint32_t &getId() const { return _id; }

    const QUrl &getUrl() const { return _url; }

    bool isChecked() const { return _checked; }

    void setChecked(bool value) { _checked = value; }

    friend bool operator==(Cell const &left, Cell const &right);

    friend bool operator!=(Cell const &left, Cell const &right);

  private:
    QUrl _url;
    uint32_t _id = 0;
    bool _checked = false;
};

#endif // CELL_HPP
