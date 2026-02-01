#pragma once

#include <array>

#include "frame.h"

enum class CellState
{
    Empty,
    Volatile,
    Source,
    Sink
};


class GolBoard : public EffectBoard
{
public:
    GolBoard(PixelBoard & board) : EffectBoard{ &board } { }

    constexpr static int HistorySize = 4;

    using GolState = std::array<CellState, get_cols() * get_rows()>;

    std::array<CRGB, 4> palette_ = {};
    std::array<GolState, HistorySize> board_history_ = {};

    size_t current_board_index_ = {};

    void reset() override
    {
        EffectBoard::reset();

        // randomize palette
        auto hue = u8(random(256));
        palette_[0] = CRGB{CHSV{hue, u8(random(128)), u8(random(64))}};
        palette_[1] = CRGB{CHSV{u8((hue + 30 + random(30)) % 256), u8(128 + random(128)), u8(192 + random(64))}};
        palette_[2] = CRGB{CHSV{u8((hue + 60 + random(60)) % 256), u8(128 + random(128)), u8(192 + random(64))}};
        palette_[3] = CRGB{CHSV{u8((hue + 120 + random(120)) % 256), u8(128 + random(128)), u8(192 + random(64))}};

        // clear cells
        auto & cells = board_history_[current_board_index_];
        switch(random(3))
        {
        case 0:
            for (size_t i = 0; i < cells.size(); ++i) {
                auto r = random(20);
                cells[i] = r & 1 ? CellState::Volatile
                                 : CellState::Empty; }
            break;
        case 1:
            for (size_t i = 0; i < cells.size(); ++i) {
                auto r = random(60);
                cells[i] = r > 0 ? ((r & 1) ? CellState::Volatile
                                            : CellState::Empty)
                                 : CellState::Source; }
            break;
        case 2:
            for (size_t i = 0; i < cells.size(); ++i) {
                auto r = random(120);
                cells[i] = r > 1 ? ((r & 1) ? CellState::Volatile
                                            : CellState::Empty)
                                  : (r ? CellState::Source 
                                       : CellState::Sink); }
            break;
        }


        for (size_t b = 0; b < board_history_.size(); ++b)
        {
            if (b == current_board_index_) { continue; }
            
            auto & cells = board_history_[b];
            for (size_t i = 0; i < cells.size(); ++i) { cells[i] = CellState::Empty; }
        }

        frame_number_ = {};
    }

    size_t frame_number_ = {};

    void animate([[maybe_unused]] long ticks) override
    {
        EffectBoard::animate(ticks);

        if (frame_number_++ == 1024 || checkHistory() ) {
            stop();
        }
        else {
            if (frame_number_ % 8 == 0) {
                runRules();
            }
        }
    }

    bool checkHistory()
    {
        auto & current_cells = board_history_[current_board_index_];
        size_t num_diffs = {};
        for (size_t b = 0; b < board_history_.size(); ++b)
        {
            if (b == current_board_index_) { continue; }
            
            auto & cells = board_history_[b];
            for (size_t i = 0; i < cells.size(); ++i)
            {
                if (cells[i] != current_cells[i]) { num_diffs += 1; break; }
            }
        }
        return num_diffs < board_history_.size() - 1;
    }

    constexpr int static UpLeft = - get_cols() - 1;
    constexpr int static Up = - get_cols();
    constexpr int static UpRight = - get_cols() + 1;
    constexpr int static Right = + 1;
    constexpr int static DownRight = + get_cols() + 1;
    constexpr int static Down = + get_cols();
    constexpr int static DownLeft = + get_cols() - 1;
    constexpr int static Left = - 1;

    void runRules()
    {
        int next_board_index = (current_board_index_ + 1) % board_history_.size();
        auto & current_cells = board_history_[current_board_index_];
        auto & next_cells = board_history_[next_board_index];

        auto isit = [](CellState state) { return (state == CellState::Volatile || state == CellState::Source) ? 1 : 0; };

        for (int y = 0; y < get_rows(); ++y)
        {
            for (int x = 0; x < get_cols(); ++x)
            {
                auto current_cell = current_cells[y * get_cols() + x];
                auto & next_cell = next_cells[y * get_cols() + x];
                if (current_cell == CellState::Sink || current_cell == CellState::Source) {
                    next_cell = current_cell;
                    continue;
                }

                int neighbors = 0;
                if (y > 0 && x > 0)
                { auto state = current_cells[(y - 1) * get_cols() + (x - 1)]; neighbors += isit(state); }
                if (y > 0)
                { auto state = current_cells[(y - 1) * get_cols() + (x + 0)]; neighbors += isit(state); }
                if (y > 0 && x < get_cols() - 1)
                { auto state = current_cells[(y - 1) * get_cols() + (x + 1)]; neighbors += isit(state); }
                if (x < get_cols() - 1)
                { auto state = current_cells[(y + 0) * get_cols() + (x + 1)]; neighbors += isit(state); }
                if (y < get_rows() - 1 && x < get_cols() - 1)
                { auto state = current_cells[(y + 1) * get_cols() + (x + 1)]; neighbors += isit(state); }
                if (y < get_rows() - 1)
                { auto state = current_cells[(y + 1) * get_cols() + (x + 0)]; neighbors += isit(state); }
                if (y < get_rows() - 1 && x > 0) 
                { auto state = current_cells[(y + 1) * get_cols() + (x - 1)]; neighbors += isit(state); }
                if (x > 0)
                { auto state = current_cells[(y + 0) * get_cols() + (x - 1)]; neighbors += isit(state); }

                if (current_cell == CellState::Volatile) {
                    if (neighbors == 2 || neighbors == 3) {
                        next_cell = CellState::Volatile;
                    }
                    else {
                        next_cell = CellState::Empty;
                    }
                }
                else if (current_cell == CellState::Empty) {
                    if (neighbors == 3) {
                        next_cell = CellState::Volatile;
                    }
                    else {
                        next_cell = CellState::Empty;
                    }
                }
            }
        }

        current_board_index_ = next_board_index;
    }

    void render() override
    {
        auto const & current_cells = board_history_[current_board_index_];

        for (int y = 0; y < get_rows(); ++y)
        {
            for (int x = 0; x < get_cols(); ++x)
            {
                auto current_cell = current_cells[y * get_cols() + x];
                auto & pixel = get_pixel(x, y);
                pixel = palette_[static_cast<int>(current_cell)];
            }
        }
    }
};

