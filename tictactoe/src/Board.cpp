#include "Board.h"
#include <algorithm>
#include <QDebug>

Board::Board() {
    createCells();
    createPaths();
}

void Board::createCells() noexcept {
    m_data.reserve(ROW_COUNT * COL_COUNT);
    for (auto i = 0; i < ROW_COUNT; ++i){
        for (auto j = 0; j < COL_COUNT; ++j) {
            m_data.emplace_back(i, j);
        }
    }    
}

void Board::createPaths() noexcept {
    // push normal rows and cols
    for (auto i = 0; i < ROW_COUNT; ++i)
        m_paths.emplace_back(rows(i));
    
    for (auto j = 0; j < COL_COUNT; ++j)
        m_paths.emplace_back(cols(j));
    
    // corss paths for 3x3 board
    // [left:top] => [right:bottom]
    // [left:bottom] => [right:top]
    m_paths.emplace_back(Path{cell(0,0), cell(1,1), cell(2,2)});
    m_paths.emplace_back(Path{cell(0,2), cell(1,1), cell(2,0)});
}

void Board::clean() noexcept {
    m_isEmpty = true;
    for(auto& cell : m_data)
        cell.value = MoveType::NONE;
}

const cell_array_t& Board::data() const noexcept { return m_data; }

const_row_t Board::rows(int rowIndex) const noexcept {
    const_row_t row;
    for (auto i = 0; i < COL_COUNT; ++i) {
        row.emplace_back(m_data[COL_COUNT * rowIndex+i]);
    }
    
    return row;
}

const_col_t Board::cols(int colIndex) const noexcept 
{
    const_col_t col;
    for (auto i = 0; i < ROW_COUNT; ++i){
        col.push_back(m_data[i*ROW_COUNT + colIndex]);
    }
    
    return col;
}

Cell& Board::cellData(int row, int col) noexcept 
{
    return m_data.at(row*ROW_COUNT + col);
}

const Cell& Board::cell(int row, int col) const noexcept 
{
    return m_data.at(row*ROW_COUNT + col);
}

void Board::setValue(int row, int col, MoveType mvType)  noexcept {
    m_isEmpty = false;
    cellData(row,col).value = mvType;
}

MoveType Board::value(int row, int col) const  noexcept  {
    return cell(row, col).value;
}

bool Board::isCompleted() const noexcept 
{
    return std::none_of(m_data.begin(), m_data.end(), [](const Cell& cell){
        return cell.value == MoveType::NONE;
    });
}

bool Board::isEmpty() const noexcept
{
    return m_isEmpty;
//    return std::all_of(m_data.begin(), m_data.end(), [](const Cell& cell){
//        return cell.value == MoveType::NONE;
//    });
}

const Board::path_array_t& Board::paths() const noexcept 
{
    return m_paths;
}

size_t Board::size() const { return m_data.size(); }

size_t Path::count(MoveType type) const
{
    return std::count_if(data.cbegin(),
                  data.cend(),
                  [type](const auto& c){
                      return c.get().value == type; 
    });
}

bool Path::isComplete() const {
    std::unordered_map<MoveType,int> m;
    for(const auto& item : data) {
        m[item.get().value]++;
    }
    
    const auto itr = std::find_if(m.begin(), m.end(),[](const auto& p) {
        return p.first != MoveType::NONE;
    });
    
    if (m.size() == 1 && itr != m.end()) return true;
    return false;
}
