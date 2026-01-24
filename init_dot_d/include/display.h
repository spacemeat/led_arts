#pragma once

#include "frame.h"
#include "textBoard.h"
#include "mandel.h"

constexpr int const NumTilesPerBoardX = 4;
constexpr int const NumTilesPerBoardY = 4;
constexpr int const NumPixelsPerTileX = 16;
constexpr int const NumPixelsPerTileY = 16;
constexpr int const NumPixelsPerBoardX = NumTilesPerBoardX * NumPixelsPerTileX;
constexpr int const NumPixelsPerBoardY = NumTilesPerBoardY * NumPixelsPerTileY;

using PixelBoard = Board<NumTilesPerBoardX, NumTilesPerBoardY, NumPixelsPerTileX, NumPixelsPerTileY>;
using TextBoard8x16 = TextBoard<8, 16, NumTilesPerBoardX, NumTilesPerBoardY, NumPixelsPerTileX, NumPixelsPerTileY>;
using MBoard = MandelBoard<NumTilesPerBoardX, NumTilesPerBoardY, NumPixelsPerTileX, NumPixelsPerTileY>;

class Display
{
public:
    Display();
    PixelBoard & get_pixel_board() { return pixel_board_; }
    TextBoard8x16 & get_text_board_8x16() { return text_board_8x16_; }
    MBoard & get_mandel_board() { return mandel_board_; }
    void reset();
    void animate(long ticks);
    void render();

private:

    PixelBoard pixel_board_;
    TextBoard8x16 text_board_8x16_;
    MBoard mandel_board_;
};


