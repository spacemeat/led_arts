#include <cstring>
#include <iostream>
#include <iomanip>

#include "board.h"

//CRGB board_buffer[PixelsPerBoard];
std::array<CRGB, PixelsPerBoard> board_buffer;

void Cell::report() const
{
    std::cout << "C" << col_ << "," << row_ << ": " << std::setw(4) << cell_address_ << " " << ch_ << "  ";
}

void Cell::set_pos(int tile_address, int col, int row)
{
    tile_address_ = tile_address;
    col_ = col;
    row_ = row;
    cell_address_ = tile_address + row_ * PixelsPerTileWidth + col_ * PixelsPerCellWidth;
}


void Cell::set_ch(char ch, ColorPair colors={
    .bg=static_cast<uint8_t>(Color::BLACK),
    .fg=static_cast<uint8_t>(Color::WHITE)})
{
    ch_ = ch;
    colors_ = colors;
}


void Cell::draw()
{
    int addr = cell_address_;
    unsigned char * pch = font8x16[static_cast<int>(ch_)];
    for (int i = 0; i < PixelsPerCellHeight; ++i)
    {
        addr += PixelsPerCellWidth;
        unsigned char ch = pch[i];
        for (int b = 0; b < PixelsPerCellWidth; ++b)
        {
            addr -= 1;
            CRGB & color = (ch & 0x01) ? ansi_colors[colors_.fg] : ansi_colors[colors_.bg];
            board_buffer[addr] = color;
            ch >>= 1;
        }
        addr += PixelsPerTileWidth;
    }
}


void Tile::recell()
{
    for (int j = 0; j < CellsPerTileHeight; ++j)
    {
        for (int i = 0; i < CellsPerTileWidth; ++i)
        {
            cells_[j][i].set_pos(tile_address_, i, j);
        }
    }
    
}

void Tile::report() const
{
    std::cout << "T" << col_ << "," << row_ << ": " << std::setw(4) << tile_address_ << "  ";
    for (int j = 0; j < CellsPerTileHeight; ++j)
    {
        for (int i = 0; i < CellsPerTileWidth; ++i)
        {
            cells_[j][i].report();
        }
    }
}

void Tile::set_pos(int col, int row)
{
    col_ = col;
    row_ = row;
    tile_address_ = row_ * BoardPitch * CellsPerTileHeight * PixelsPerCellHeight + col_ * TilePitch;
}

Cell & Tile::get_cell(int col, int row) {
    return cells_[row][col];
}

void Tile::set_cell(int col, int row, char ch, ColorPair colors)
{
    if (col < CellsPerTileWidth && row < CellsPerTileHeight)
    {
        cells_[row][col].set_ch(ch, colors);
    }
}

void Tile::draw()
{
    for (int j = 0; j < CellsPerTileHeight; ++j)
    {
        for (int i = 0; i < CellsPerTileWidth; ++i)
        {
            cells_[j][i].draw();
        }
    }
}

void Board::retile()
{
    for (int j = 0; j < TilesPerBoardHeight; ++j)
    {
        for (int i = 0; i < TilesPerBoardWidth; ++i)
        {
            tiles_[j][i].set_pos(i, j);
            tiles_[j][i].recell();
        }
    }
}


void Board::reset()
{
	for (unsigned int b = 0; b < PixelsPerBoard; ++b)
	{
		board_buffer[b] = CRGB(0, 0, 0);
	}
}

void Board::animate([[maybe_unused]] long ticks)
{
}

void Board::render()
{
    draw();
}

void Board::report() const
{
    std::cout << "Board:\n";

    for (int j = 0; j < TilesPerBoardHeight; ++j)
    {
        for (int i = 0; i < TilesPerBoardWidth; ++i)
        {
            tiles_[j][i].report();
        }
        std::cout << "\n";
    }
}

// text can be null-terminated. colors must be at least as long as text.
void Board::add_line(char const * text, ColorPair const * colors)
{
    scroll();
    for (int i = 0; i < CellsPerBoardWidth; ++i)
    {
        if (text[i] == 0) { break; }
        set_cell(i, CellsPerBoardHeight - 1, text[i], colors[i]);
    }
}

void Board::set_cell(int col, int row, char ch, ColorPair colors)
{
    Tile & tile = tiles_[row / CellsPerTileHeight][col / CellsPerTileWidth];
    tile.set_cell(col % CellsPerTileWidth, row % CellsPerTileHeight, ch, colors);
}

Tile & Board::get_tile(int col, int row)
{
    return tiles_[row][col];
}

Cell & Board::get_cell(int col, int row)
{
    Tile & tile = tiles_[row / CellsPerTileHeight][col / CellsPerTileWidth];
    return tile.get_cell(col % CellsPerTileWidth, row % CellsPerTileHeight);
}

void Board::scroll()
{
    // NOTE: This alg really only works as simply as is because there
    // is one cell per tile in height. If that gets split, this will 
    // need to be redone.
    /*
    for (int j = 0; j < TilesPerBoardHeight - 1; ++j)
    {
        auto slider = BoardPitch * PixelsPerCellHeight * CellsPerTileHeight;
        std::copy(board_buffer.begin() + slider * (j + 1), 
                  board_buffer.begin() + slider * (j + 2), 
                  board_buffer.begin() + slider * j);
    }
    */

    for (int cj = 0; cj < CellsPerBoardHeight - 1; ++cj)
    {
        for (int ci = 0; ci < CellsPerBoardWidth; ++ci)
        {
            auto & celld = get_cell(ci, cj);
            auto const & cells = get_cell(ci, cj + 1);
            celld.set_ch(cells.get_ch(), cells.get_colors());
        }
    }
}

void Board::draw()
{
    for (int j = 0; j < TilesPerBoardHeight; ++j)
    {
        for (int i = 0; i < TilesPerBoardWidth; ++i)
        {
            tiles_[j][i].draw();
        }
    }
}

