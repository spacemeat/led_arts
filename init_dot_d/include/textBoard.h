#pragma once

#include <span>

#include "frame.h"
#include "bitmaps.h"
#include "colors.h"

struct TextCell
{
    char ch_ = ' ';
    ColorPair colors_ = {
        .bg=static_cast<uint8_t>(Color::BLACK), 
        .fg=static_cast<uint8_t>(Color::WHITE)};
};

template <int NumPixelsInCellCols, int NumPixelsInCellRows, 
          int NumTileCols,         int NumTileRows, 
          int NumPixelsInTileCols, int NumPixelsInTileRows>
class TextBoard
{
public:
    using PixelBoard = Board<NumTileCols, NumTileRows, NumPixelsInTileCols, NumPixelsInTileRows>;

    TextBoard(PixelBoard & board) : board_ { &board } { }

    constexpr static int get_cols() { return NumPixelsInTileCols * NumTileCols / NumPixelsInCellCols; }
    constexpr static int get_rows() { return NumPixelsInTileRows * NumTileRows / NumPixelsInCellRows; }

    TextCell const & get_cell(int col, int row) const { return cells_[row * get_cols() + col]; }
    TextCell & get_cell(int col, int row) { return cells_[row * get_cols() + col]; }

    void reset()
    {
        for (auto & cell : cells_)
        {
            cell = TextCell {};
        }
    }

    void set_cell(int col, int row, char ch, ColorPair colors)
    {
        if (col >= get_cols() ||
            row >= get_rows()) { return; }
        cells_[row * get_cols() + col] = TextCell { .ch_ = ch, .colors_ = colors };
    }

    void set_string(int col, int row, std::string_view str, std::span<ColorPair> colors)
    {
        cursorCol_ = col;
        cursorRow_ = row;
        append_string(str ,colors);
    }

    void scroll(int num_rows)
    {
        if (num_rows < get_rows())
        {
            std::copy(cells_.begin() + get_cols() * num_rows, 
                      cells_.end(),
                      cells_.begin());
        }
        for (auto it = cells_.end() - get_cols() * num_rows; it != cells_.end(); ++it)
        {
            *it = TextCell{};
        }
        cursorRow_ -= num_rows;
        if (cursorRow_ < 0) { cursorRow_ = 0; cursorCol_ = 0; }
    }

    void append_string(std::string_view str, std::span<ColorPair> colors)
    {
        for(uint64_t idx = 0; idx < std::min(str.size(), colors.size()); ++idx)
        {
            if (cursorCol_ >= get_cols()) { cursorCol_ = 0; cursorRow_ += 1; }
            if (cursorRow_ >= get_rows()) { scroll(cursorRow_ - get_rows() + 1); }

            set_cell(cursorCol_, cursorRow_, str[idx], colors[idx]);
            if (str[idx] == '\n') { cursorCol_ = 0; cursorRow_ += 1; }
            else { cursorCol_ += 1; }
        }
    }

    // 8x16
    void animate([[maybe_unused]] long ticks)
    {
    }

    void render()
    {
        for (int chi = 0; chi < get_cols() * get_rows(); ++chi)
        {
            int chr = chi / get_cols() * 16;
            int chc = chi % get_cols() * 8;
            auto & textCell = cells_[chi];
            unsigned char * pbits = font8x16[static_cast<int>(textCell.ch_)];
            for (int br = 0; br < 16; ++br) {
                unsigned char charbits = pbits[br];
                for (int bc = 0; bc < 8; ++bc)
                {
                    CRGB & color = (charbits & 0x80) ? ansi_colors[textCell.colors_.fg] : ansi_colors[textCell.colors_.bg];
                    charbits <<= 1;

                    int pr = chr + br;
                    int pc = chc + bc;
                    board_->get_pixel(pc, pr) = color;
                }
            }
        }
    }

private:

    PixelBoard * board_;
    std::array<TextCell, get_cols() * get_rows()> cells_;
    int cursorCol_ {};
    int cursorRow_ {};
};

