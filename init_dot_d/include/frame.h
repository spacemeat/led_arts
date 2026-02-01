#pragma once

#include <array>

#include "system.h"

constexpr int const NumTilesPerBoardX = 4;
constexpr int const NumTilesPerBoardY = 4;
constexpr int const NumPixelsPerTileX = 16;
constexpr int const NumPixelsPerTileY = 16;
constexpr int const NumPixelsPerBoardX = NumTilesPerBoardX * NumPixelsPerTileX;
constexpr int const NumPixelsPerBoardY = NumTilesPerBoardY * NumPixelsPerTileY;

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


template <int NumPixelsPerTileX, int NumPixelsPerTileY, int NumTilesX, int NumTilesY>
class Board
{
public:
    using TBuffer = TileBuffer<NumPixelsPerTileX, NumPixelsPerTileY>;

    Board()
    {
        CRGB * pixels = pixels_.data();
        for (auto & tile : tiles_)
        {
            tile.set_pixel_buffer(pixels);
            pixels += NumPixelsPerTileX * NumPixelsPerTileY;
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
        return tiles_[row * NumTilesX + col];
    }

    TBuffer & get_tile(int col, int row)
    {
        return tiles_[row * NumTilesX + col];
    }

    CRGB const & get_pixel(int col, int row) const
    {
        auto & tbuffer = get_tile(col / NumPixelsPerTileX, row / NumPixelsPerTileY);
        return tbuffer.get_pixel(col % NumPixelsPerTileX, row % NumPixelsPerTileY);
    }

    CRGB & get_pixel(int col, int row)
    {
        auto & tbuffer = get_tile(col / NumPixelsPerTileX, row / NumPixelsPerTileY);
        return tbuffer.get_pixel(col % NumPixelsPerTileX, row % NumPixelsPerTileY);
    }

private:
    std::array<CRGB, NumTilesX * NumPixelsPerTileX * NumTilesY * NumPixelsPerTileY> pixels_;
    std::array<TBuffer, NumTilesX * NumTilesY> tiles_;
};


using PixelBoard = Board<NumPixelsPerTileX, NumPixelsPerTileY, NumTilesPerBoardX, NumTilesPerBoardY>;

class EffectBoard
{
public:
    EffectBoard(PixelBoard * board, long animation_time = 32 * 1024) : board_{board}, max_animation_time_{animation_time} {}

    constexpr static int get_cols() { return NumTilesPerBoardX * NumPixelsPerTileX; }
    constexpr static int get_rows() { return NumTilesPerBoardY * NumPixelsPerTileY; }

    CRGB const & get_pixel(int col, int row) const
    {
        return board_->get_pixel(col, row);
    }

    CRGB & get_pixel(int col, int row)
    {
        return board_->get_pixel(col, row);
    }

    virtual void reset()
    {
        animation_time_ = 0;
        should_stop_ = false;
    }

    virtual void animate(long ticks)
    {
        animation_time_ += ticks;
    }

    virtual void render() = 0;

    bool should_stop()
    {
        return should_stop_ || animation_time_ > max_animation_time_;
    }

    void stop() { should_stop_ = true; }

protected:
    PixelBoard * board_ {nullptr};
    long animation_time_ {};
    long max_animation_time_ { 32 * 1024 };
    bool should_stop_ { false };
};


