#pragma once

#include <array>

#include "system.h"

template <int Cols, int Rows>
class TileBuffer
{
public:
    void set_pixel_buffer(CRGB * first_pixel)
    {
        pixels_ = first_pixel;
    }

    void reset(CHSV gradientColor = {0, 255, 0})
    {
        for (int i = 0; i < Rows * Cols; ++i)
        {
            int v = i % 256;
            pixels_[i] = CRGB(CHSV(gradientColor.h, gradientColor.s, v));
        }
    }

    CRGB const & get_pixel(int col, int row) const
    {
        return pixels_[row * Cols + col];
    }

    CRGB & get_pixel(int col, int row)
    {
        return pixels_[row * Cols + col];
    }

private:
    CRGB * pixels_;
};


template <int Cols, int Rows>
struct Extents
{ };


template <int NumTileCols, int NumTileRows, int NumPixelsInTileCols, int NumPixelsInTileRows>
class Board
{
public:
    using TBuffer = TileBuffer<NumPixelsInTileCols, NumPixelsInTileRows>;

    Board()
    {
        CRGB * pixels = pixels_.data();
        for (auto & tile : tiles_)
        {
            tile.set_pixel_buffer(pixels);
            pixels += NumPixelsInTileCols * NumPixelsInTileRows;
        }
    }

    void reset()
    {
        int hue = 0;
        for (auto & tile : tiles_)
        {
            tile.reset(CHSV{uint8_t(hue), 255, 0});
            hue += 16;
            hue %= 256;
        }
    }

    TBuffer const & get_tile(int col, int row) const
    {
        return tiles_[row * NumTileCols + col];
    }

    TBuffer & get_tile(int col, int row)
    {
        return tiles_[row * NumTileCols + col];
    }

    CRGB const & get_pixel(int col, int row) const
    {
        auto & tbuffer = get_tile(col / NumPixelsInTileCols, row / NumPixelsInTileRows);
        return tbuffer.get_pixel(col % NumPixelsInTileCols, row % NumPixelsInTileRows);
    }

    CRGB & get_pixel(int col, int row)
    {
        auto & tbuffer = get_tile(col / NumPixelsInTileCols, row / NumPixelsInTileRows);
        return tbuffer.get_pixel(col % NumPixelsInTileCols, row % NumPixelsInTileRows);
    }

private:
    std::array<CRGB, NumTileCols * NumPixelsInTileCols * NumTileRows * NumPixelsInTileRows> pixels_;
    std::array<TBuffer, NumTileCols * NumTileRows> tiles_;
};



