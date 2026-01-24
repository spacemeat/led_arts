#pragma once

#include <array>

#include "system.h"

#include "bitmaps.h"
#include "colors.h"

constexpr int const PixelsPerCellWidth = 8;
constexpr int const PixelsPerCellHeight = 16;
constexpr int const CellsPerTileWidth = 2;
constexpr int const CellsPerTileHeight = 1;
constexpr int const TilesPerBoardWidth = 4;
//constexpr int const TilesPerBoardHeight = 4;
constexpr int const TilesPerBoardHeight = 2;

constexpr int const PixelsPerBoard = 
    PixelsPerCellWidth
  * PixelsPerCellHeight
  * CellsPerTileWidth
  * CellsPerTileHeight
  * TilesPerBoardWidth
  * TilesPerBoardHeight;

constexpr int const BoardPitch = 
    PixelsPerCellWidth
  * CellsPerTileWidth
  * TilesPerBoardWidth;
constexpr int const PixelsPerBoardWidth = BoardPitch;
constexpr int const PixelsPerBoardHeight = 
    PixelsPerCellHeight
  * CellsPerTileHeight
  * TilesPerBoardHeight;

constexpr int const TilePitch = 
    PixelsPerCellWidth
  * CellsPerTileWidth;

constexpr int const TilesPerBoard =
    TilesPerBoardWidth
  * TilesPerBoardHeight;

constexpr int const PixelsPerTile =
    PixelsPerCellWidth
  * PixelsPerCellHeight
  * CellsPerTileWidth
  * CellsPerTileHeight;

constexpr int const PixelsPerTileWidth = 
    PixelsPerCellWidth
  * CellsPerTileWidth;

constexpr int const PixelsPerTileHeight = 
    PixelsPerCellHeight
  * CellsPerTileHeight;

constexpr int const CellsPerBoardWidth =
    CellsPerTileWidth
  * TilesPerBoardWidth;

constexpr int const CellsPerBoardHeight = 
    CellsPerTileHeight
  * TilesPerBoardHeight;


//extern CRGB board_buffer[PixelsPerBoard];
extern std::array<CRGB, PixelsPerBoard> board_buffer;


class Cell
{
public:
    Cell() = default;

    char get_ch() const { return ch_; }
    ColorPair get_colors() const { return colors_; }

    void report() const;

    void set_pos(int tile_address, int col, int row);
    int get_cell_address() { return cell_address_; }
    void set_ch(char ch, ColorPair colors);
    void draw();

private:
    int tile_address_ = 0;
    int col_ = 0;
    int row_ = 0;
    int cell_address_ = 0;
    char ch_ = ' ';
    ColorPair colors_ = {
        .bg=static_cast<uint8_t>(Color::BLACK), 
        .fg=static_cast<uint8_t>(Color::WHITE)};
};


class Tile
{
public:
    Tile() = default;

    void recell();

    void report() const;

    void set_pos(int col, int row);
    Cell & get_cell(int col, int row);
    void set_cell(int col, int row, char ch, ColorPair colors);
    int get_address() { return tile_address_; }
    void draw();

private:
    int col_ = 0;
    int row_ = 0;
    int tile_address_ = 0;
    Cell cells_[CellsPerTileHeight][CellsPerTileWidth];
};


class Board
{
public:
    Board() = default;
    void retile();
    void reset();
    void animate(long ticks);
    void render();

    void report() const;

    void add_line(char const * text, ColorPair const * colors);
    void set_cell(int col, int row, char ch, ColorPair colors);
    Tile & get_tile(int col, int row);
    Cell & get_cell(int col, int row);
    void scroll();
    void draw();
    
private:
    Tile tiles_[TilesPerBoardHeight][TilesPerBoardWidth];
};

