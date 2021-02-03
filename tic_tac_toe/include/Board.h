/*
 * 01.08.2020 Hakan Gedek
 * 
 * I prefered to use QTableWidget to show board instead of creating a custom widget
 * or using view-model aproach. 
 * 
 * This class acts as board model and contains cells and related functions.
 * 
 * Path: proxy for cells row [ board actually has 8 paths]. On a board there are 8 [ for 3 x 3] 
 * paths that can be played.
 * 
 */

#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>
#include "Common.h"

/**
 * @brief The Cell struct model for cells on qtablewidget
 */
struct Cell {
    uint32_t row;
    uint32_t col;
    // [X,O,None] = each cell holds only one data
    MoveType value = MoveType::NONE;
    
    /**
     * @brief Cell ctor
     * @param r
     * @param c
     */
    Cell(int r, int c): row(r), col(c) {}
};

/**
 * Type aliases for easy to use / read
 */
using cell_ref_t            = std::reference_wrapper<Cell>;
using const_cell_ref_t      = std::reference_wrapper<const Cell>;
using cell_array_t          = std::vector<Cell>;

using row_t                 = std::vector<cell_ref_t>;
using const_row_t           = std::vector<const_cell_ref_t>;
using row_array_t           = std::vector<row_t>;

using col_t                 = row_t;
using const_col_t           = const_row_t;
using col_array_t           = std::vector<col_t>;


/**
 * @brief for simple tic-tac-toe 3x3 boards used so i'm using constants
 */
constexpr auto ROW_COUNT    = 3;
constexpr auto COL_COUNT    = 3;
constexpr auto CHECK_COUNT  = 3;

/**
 * @brief The Path struct on board each playable path rows.cols.crosses
 */
struct Path {
    using path_t = std::vector<const_cell_ref_t>;
    path_t data;
    /**
     * @brief Path
     * @param path
     */
    Path(const path_t& path): data(path.begin(), path.end()){}
    /**
     * @brief Path
     * @param list
     */
    Path(std::initializer_list<const_cell_ref_t> list): data(list.begin(), list.end()){}
    
    ~Path() = default;
    
    /**
     * @brief count returns number of a move-type on path
     * @param type
     * @return 
     */
    size_t count(MoveType type) const;
    /**
     * @brief isComplete checks if board is filled
     * @return 
     */
    bool isComplete() const;
};

/**
 * @brief The Board struct model data for qtablewidget 
 */
struct Board {
    Board();
    ~Board() = default;
    /**
     * @brief data board all data - array of cells
     * @return 
     */
    const cell_array_t& data() const noexcept;
    
    /**
     * @brief rows
     * @param rowIndex
     * @return 
     */
    const_row_t rows(int rowIndex) const noexcept;
    
    /**
     * @brief cols
     * @param colIndex
     * @return 
     */
    const_col_t cols(int colIndex) const  noexcept;
    
    /**
     * @brief cell
     * @param row
     * @param col
     * @return 
     */
    const Cell& cell(int row, int col) const noexcept;
    
    /**
     * @brief clean
     */
    void clean() noexcept;
    
    /**
     * @brief setValue
     * @param row
     * @param col
     * @param mvType
     */
    void setValue(int row, int col, MoveType mvType) noexcept ;
    
    /**
     * @brief value
     * @param row
     * @param col
     * @return 
     */
    MoveType value(int row, int col) const noexcept;
    
    /**
     * @brief isCompleted
     * @return 
     */
    bool isCompleted() const noexcept;
    /**
     * @brief isEmpty
     * @return 
     */
    bool isEmpty() const noexcept;
 
    using path_array_t = std::vector<Path>;
    /**
     * @brief paths
     * @return 
     */
    const path_array_t& paths() const noexcept;
    /**
     * @brief rowCount
     */
    constexpr auto rowCount() const { return ROW_COUNT; }
    /**
     * @brief colCount
     */
    constexpr auto colCount() const { return COL_COUNT; }
    /**
     * @brief size
     * @return 
     */
    size_t size() const;
private:
    /**
     * @brief createCells
     */
    void createCells() noexcept;
    /**
     * @brief createPaths
     */
    void createPaths() noexcept;
    /**
     * @brief cellData edit function for cell data
     * @param row
     * @param col
     * @return 
     */
    Cell& cellData(int row, int col) noexcept ;
    
private:
    /**
      * @brief m_data list of cells
      */
     cell_array_t m_data;
     /**
      * @brief m_paths list of paths
      */
     path_array_t m_paths;
     bool m_isEmpty = true;
};

