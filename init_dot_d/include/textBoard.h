#pragma once

#include <span>
#include <string_view>

#include "frame.h"
#include "bitmaps.h"
#include "colors.h"

#define COLOR(bg, fg) ColorPair {static_cast<uint8_t>(Color::bg), static_cast<uint8_t>(Color::fg)}


using Msg = std::pair<std::string_view, std::array<ColorPair, 8>>;

constexpr static const Msg msg_Ok {
    "[  OK  ]", {
    COLOR(BLACK, WHITE),
    COLOR(BLACK, GREEN),
    COLOR(BLACK, GREEN),
    COLOR(BLACK, GREEN),
    COLOR(BLACK, GREEN),
    COLOR(BLACK, GREEN),
    COLOR(BLACK, GREEN),
    COLOR(BLACK, WHITE) }
};

constexpr static const Msg msg_Failed {
    "[FAILED]", {
    COLOR(BLACK, WHITE),
    COLOR(BLACK, RED),
    COLOR(BLACK, RED),
    COLOR(BLACK, RED),
    COLOR(BLACK, RED),
    COLOR(BLACK, RED),
    COLOR(BLACK, RED),
    COLOR(BLACK, WHITE) }
};

constexpr static const std::array msg_Eggs {
    Msg { "[MOOPED]", {
        COLOR(BLACK, WHITE),
        COLOR(BLACK, BLUE),
        COLOR(BLACK, BLUE),
        COLOR(BLACK, BLUE),
        COLOR(BLACK, BLUE),
        COLOR(BLACK, BLUE),
        COLOR(BLACK, BLUE),
        COLOR(BLACK, WHITE) }
    },
    Msg { "[FOOBAR]", {
        COLOR(BLACK, WHITE),
        COLOR(BLACK, RED),
        COLOR(BLACK, RED),
        COLOR(BLACK, RED),
        COLOR(BLACK, YELLOW),
        COLOR(BLACK, YELLOW),
        COLOR(BLACK, YELLOW),
        COLOR(BLACK, WHITE) }
    },
    Msg { "[ELOPED]", {
        COLOR(BLACK, WHITE),
        COLOR(BLACK, GREEN),
        COLOR(BLACK, GREEN),
        COLOR(BLACK, GREEN),
        COLOR(BLACK, GREEN),
        COLOR(BLACK, GREEN),
        COLOR(BLACK, GREEN),
        COLOR(BLACK, WHITE) }
    },
    Msg { "[GOATED]", {
        COLOR(BLACK, WHITE),
        COLOR(BLACK, GREEN),
        COLOR(BLACK, GREEN),
        COLOR(BLACK, GREEN),
        COLOR(BLACK, GREEN),
        COLOR(BLACK, GREEN),
        COLOR(BLACK, GREEN),
        COLOR(BLACK, WHITE) }
    },
    Msg { "[HOHOHO]", {
        COLOR(BLACK, WHITE),
        COLOR(BLACK, LT_GREEN),
        COLOR(BLACK, LT_GREEN),
        COLOR(BLACK, LT_RED),
        COLOR(BLACK, LT_RED),
        COLOR(BLACK, LT_GREEN),
        COLOR(BLACK, LT_GREEN),
        COLOR(BLACK, WHITE) }
    },
    Msg { "[<3<3<3]", {
        COLOR(BLACK, WHITE),
        COLOR(BLACK, LT_RED),
        COLOR(BLACK, LT_RED),
        COLOR(BLACK, LT_MAGENTA),
        COLOR(BLACK, LT_MAGENTA),
        COLOR(BLACK, LT_BLUE),
        COLOR(BLACK, LT_BLUE),
        COLOR(BLACK, WHITE) }
    },
    Msg { "[MURICA]", {
        COLOR(BLACK, WHITE),
        COLOR(BLACK, LT_RED),
        COLOR(BLACK, LT_WHITE),
        COLOR(BLACK, LT_BLUE),
        COLOR(BLACK, LT_RED),
        COLOR(BLACK, LT_WHITE),
        COLOR(BLACK, LT_BLUE),
        COLOR(BLACK, WHITE) }
    },
    Msg { "[UNDEAD]", {
        COLOR(BLACK, WHITE),
        COLOR(BLACK, LT_BLACK),
        COLOR(BLACK, LT_BLACK),
        COLOR(BLACK, LT_BLACK),
        COLOR(BLACK, LT_BLACK),
        COLOR(BLACK, LT_BLACK),
        COLOR(BLACK, LT_BLACK),
        COLOR(BLACK, WHITE) }
    },
    Msg { "[DOOMED]", {
        COLOR(BLACK, WHITE),
        COLOR(LT_BLACK, RED),
        COLOR(LT_BLACK, RED),
        COLOR(LT_BLACK, RED),
        COLOR(LT_BLACK, RED),
        COLOR(LT_BLACK, RED),
        COLOR(LT_BLACK, RED),
        COLOR(BLACK, WHITE) }
    },
};


struct TextCell
{
    char ch_ = ' ';
    ColorPair colors_ = {
        .bg=static_cast<uint8_t>(Color::BLACK), 
        .fg=static_cast<uint8_t>(Color::WHITE)};
};

template <int NumPixelsInCellCols, int NumPixelsInCellRows>
class TextBoard : public EffectBoard
{
public:
    TextBoard(PixelBoard & board) : EffectBoard{ &board, 5 * 1024 } { }

    //constexpr static int get_cell_cols() { return NumPixelsInTileCols * NumTileCols / NumPixelsInCellCols; }
    //constexpr static int get_cell_rows() { return NumPixelsInTileRows * NumTileRows / NumPixelsInCellRows; }
    constexpr static int get_cell_cols() { return get_cols() / NumPixelsInCellCols; }
    constexpr static int get_cell_rows() { return get_rows() / NumPixelsInCellRows; }

    TextCell const & get_cell(int col, int row) const
    { return cells_[row * get_cell_cols() + col]; }

    TextCell & get_cell(int col, int row)
    { return cells_[row * get_cell_cols() + col]; }

    void reset() override
    {
        EffectBoard::reset();

        for (auto & cell : cells_)
        {
            cell = TextCell {};
        }

        cursorCol_ = 0;
        cursorRow_ = 0;
    }

    void set_cell(int col, int row, char ch, ColorPair colors)
    {
        if (col >= get_cell_cols() ||
            row >= get_cell_rows()) { return; }
        cells_[row * get_cell_cols() + col] = TextCell { .ch_ = ch, .colors_ = colors };
    }

    void set_string(int col, int row, std::string_view str, std::span<ColorPair> colors)
    {
        cursorCol_ = col;
        cursorRow_ = row;
        append_string(str ,colors);
    }

    void scroll(int num_rows)
    {
        if (num_rows < get_cell_rows())
        {
            std::copy(cells_.begin() + get_cell_cols() * num_rows, 
                      cells_.end(),
                      cells_.begin());
        }
        for (auto it = cells_.end() - get_cell_cols() * num_rows; it != cells_.end(); ++it)
        {
            *it = TextCell{};
        }
        cursorRow_ -= num_rows;
        if (cursorRow_ < 0) { cursorRow_ = 0; cursorCol_ = 0; }
    }

    void append_string(std::string_view str, std::span<ColorPair const> colors)
    {
        for(uint64_t idx = 0; idx < std::min(str.size(), colors.size()); ++idx)
        {
            if (cursorCol_ >= get_cell_cols()) { cursorCol_ = 0; cursorRow_ += 1; }
            if (cursorRow_ >= get_cell_rows()) { scroll(cursorRow_ - get_cell_rows() + 1); }

            set_cell(cursorCol_, cursorRow_, str[idx], colors[idx]);
            if (str[idx] == '\n') { cursorCol_ = 0; cursorRow_ += 1; }
            else { cursorCol_ += 1; }
        }
    }

    void animate([[maybe_unused]] long ticks) override
    {
        EffectBoard::animate(ticks);

        if (frame_number_++ == next_frame_number_)
        {
            frame_number_ = 0;
            next_frame_number_ = random(32);
            auto mode = random(100);
            if (mode > 10)
            {
                append_string(msg_Ok.first, msg_Ok.second);
            }
            else if (mode > 1)
            {
                append_string(msg_Failed.first, msg_Failed.second);
            }
            else
            {
                auto const & msg = msg_Eggs[random(msg_Eggs.size())];
                append_string(msg.first, msg.second);
            }
        }
    }

    size_t frame_number_ = {};
    size_t next_frame_number_ = random(32);

    void render() override
    {
        for (int chi = 0; chi < get_cell_cols() * get_cell_rows(); ++chi)
        {
            int chr = chi / get_cell_cols() * 16;
            int chc = chi % get_cell_cols() * 8;
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
                    get_pixel(pc, pr) = color;
                }
            }
        }
    }

private:
    std::array<TextCell, get_cell_cols() * get_cell_rows()> cells_;
    int cursorCol_ {};
    int cursorRow_ {};
};

