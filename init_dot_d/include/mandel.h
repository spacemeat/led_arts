#pragma once

#include <complex>
#include <array>

#include "frame.h"

class MandelBoard : public EffectBoard
{
    using Cx = std::complex<float>;

    constexpr static std::array interesting_ts = {
        Cx { -0.7012693643569946f, -0.3593555545806885f },
        Cx { 0.3007597541809083f, -0.02015016555786133f },
        Cx { -1.7864376220703122, 0 },
        Cx { -0.5859806579589844f, 0.450714111328125f },
        Cx { -0.15290824890136723f, 1.039254150390625f },
        Cx { -1.266309994235635f, -0.4139231875538826f },
    };

public:
    MandelBoard(PixelBoard & board) : EffectBoard { &board } { }

    std::array<CRGB, 256> palette_ = {};

    void reset() override
    {
        EffectBoard::reset();

        c0 = {-2.0f, 2.0f};
        c1 = {2.0f, -2.0f};
        t = interesting_ts[interesting_index_++];
        interesting_index_ %= interesting_ts.size();
        // Fill out a randomized palette
        u8 rnd = static_cast<u8>(random(256));
        switch(random(2))
        {
        case 0: // roll hue, random start, full saturation, full value
            for (size_t i = 0; i < palette_.size(); ++i)
            {
                palette_[i] = CRGB{CHSV{rnd, 255, 255}};
                rnd += 1;
                rnd %= 256;
            }
            break;
        case 1: // one random hue, roll value
            for (size_t i = 0; i < palette_.size(); ++i)
            {
                palette_[i] = CRGB{CHSV{rnd, 255, u8(i % 256)}};
            }
            break;
        }
    }

    void animate([[maybe_unused]] long ticks) override
    {
        // move c0 and c1 to t
        auto midpoint = (c0 + c1) / 2.0f;
        auto new_midpoint = midpoint + (t - midpoint) / 10.0f; // * static_cast<float>(ticks) / 32.0f;
        auto offset = (c1 - c0) / 2.02f;
        if (std::abs(offset.real()) < 0.000008 || std::abs(offset.imag()) < 0.000008) { stop(); }
        else {
            c0 = new_midpoint - offset;
            c1 = new_midpoint + offset;
        }
    }

    void render() override
    {
        // This seems too slow to be > 1
        constexpr int antialias_factor = 1;

        auto d = (c1 - c0);
        auto da = Cx { d.real() / float(get_cols() * antialias_factor),
                       d.imag() / float(get_rows() * antialias_factor)};

        for (int py = 0; py < NumPixelsPerBoardY; ++py)
        {
            float cpy = float(py) / float(NumPixelsPerBoardY) * d.imag() + c0.imag();
            for (int px = 0; px < NumPixelsPerBoardX; ++px)
            {
                float cpx = float(px) / float(NumPixelsPerBoardX) * d.real() + c0.real();
                Cx cp  = Cx { cpx, cpy };
                auto & pixel = get_pixel(px, py);

                int accum {};
                for (int ay = 0; ay < antialias_factor; ++ay)
                {
                    float cay =  float(ay) / float(antialias_factor) * da.imag();
                    for (int ax = 0; ax < antialias_factor; ++ax)
                    {
                        float cax =  float(ax) / float(antialias_factor) * da.real();
                        Cx z {};
                        Cx c = cp + Cx {cax, cay};

                        int i {};
                        for (i = 0; i < 256; ++i)
                        {
                            z = z * z + c;
                            if (std::norm(z) > 4.0f)
                            {
                                accum += i;
                                break;
                            }
                        }
                    }
                }
                if (accum == 0)
                {
                    pixel = CRGB{0, 0, 0};
                }
                else
                {
                    pixel = CRGB{palette_[(accum / antialias_factor / antialias_factor) % palette_.size()]};
                }
            }
        }
    }


//private:
    std::complex<float> c0, c1;
    std::complex<float> t;
    int interesting_index_ {};
};

