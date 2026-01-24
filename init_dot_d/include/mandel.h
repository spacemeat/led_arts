
#pragma once

#include <complex>

#include "frame.h"

template <int NumTilesPerBoardX,  int NumTilesPerBoardY, 
          int NumPixelsPerTileX,  int NumPixelsPerTileY>
class MandelBoard
{
    using Cx = std::complex<float>;

    constexpr static int const NumPixelsPerBoardX = NumTilesPerBoardX * NumPixelsPerTileX;
    constexpr static int const NumPixelsPerBoardY = NumTilesPerBoardY * NumPixelsPerTileY;

    constexpr static std::array interesting_ts = {
        Cx { -0.7012693643569946f, -0.3593555545806885f },
        Cx { 0.3007597541809083f, -0.02015016555786133f },
        Cx { -1.618033988749895f , 0 },
        Cx { -0.5865806579589844f, 0.450714111328125f },
        Cx { -0.15290824890136723f, 1.039254150390625f },
        Cx { -1.266309994235635f, -0.4139231875538826f },
    };

public:
    using PixelBoard = Board<NumTilesPerBoardX, NumTilesPerBoardY, NumPixelsPerTileX, NumPixelsPerTileY>;

    MandelBoard(PixelBoard & board) : board_ { &board } { }

    void reset()
    {
        c0 = {-2.0f, 2.0f};
        c1 = {2.0f, -2.0f};
        t = interesting_ts[interesting_index_++];
        interesting_index_ %= interesting_ts.size();
        // TODO: Fill out a randomized palette
    }

    void animate([[maybe_unused]] long ticks)
    {
        // move c0 and c1 to t
        auto midpoint = (c0 + c1) / 2.0f;
        auto new_midpoint = midpoint + (t - midpoint) / 10.0f; // * static_cast<float>(ticks) / 32.0f;
        auto offset = (c1 - c0) / 2.05f;
        if (offset.real() < 0.00005) { reset(); }
        else {
            c0 = new_midpoint - offset;
            c1 = new_midpoint + offset;
        }
    }
    void render()
    {
        auto d = c1 - c0;

        for (int y = 0; y < NumPixelsPerBoardY; ++y)
        {
            for (int x = 0; x < NumPixelsPerBoardX; ++x)
            {
                auto & pixel = board_->get_pixel(x, y);
                Cx z {};
                Cx c  = Cx { static_cast<float>(x) / static_cast<float>(NumPixelsPerBoardX) * d.real() + c0.real(),
                             static_cast<float>(y) / static_cast<float>(NumPixelsPerBoardY) * d.imag() + c0.imag()};

                int i {};
                for (i = 0; i < 256; ++i)
                {
                    z = z * z + c;
                    if (std::norm(z) > 4.0f)
                    {
                        // paint with hue i
                        pixel = CRGB{CHSV{static_cast<u8>(i), 255, 255}};
                        break;
                    }
                }
                // paint with value 0
                if (i == 256) {
                    pixel = CRGB{0, 0, 0};
                }
            }
        }
    }


//private:
    PixelBoard * board_;
    std::complex<float> c0, c1;
    std::complex<float> t;
    int interesting_index_ {};
};

