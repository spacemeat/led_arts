#ifndef OCTOPUS_H
#define OCTOPUS_H

#include "effects/effect_controller.h"

constexpr const long NumBands = 0;
constexpr const long NumLedsPerBand = 20;
constexpr const long NumLedsInMantle = NumBands * NumLedsPerBand;

constexpr const long NumTentacles = 8;
constexpr const long NumStripsPerTentacle = 1;
constexpr const long NumLedsPerStrip = 60;
constexpr const long NumLedsPerTentacle = NumStripsPerTentacle * NumLedsPerStrip;
constexpr const long NumLedsInTentacles = NumTentacles * NumLedsPerTentacle;

constexpr const long NumLedsInOctopus = NumLedsInMantle + NumLedsPerTentacle;

constexpr const long EffectTransitionDuration = 1024;
constexpr const long EffectDuration = 1024 * 10;

struct Tentacle
{
	Tentacle() = default;
	void set_tentacle_id(int tentacle_id)
    {
        _tentacle_id = tentacle_id;
        _frame_buffer_start = tentacle_id * NumLedsPerTentacle;
    }

	int _tentacle_id = 0;
	int _frame_buffer_start = 0;
};

struct MantleBand // whoa, black betty
{
    MantleBand() = default;
	void set_band_id(int band_id) { _band_id = band_id; }

    int _band_id = 0;
	int _frame_buffer_start = 0;
};


class Octopus : public ObjectWithEffect
{
public:
    Octopus();
    ~Octopus() override = default;
    Effect * get_next_effect(Effect * forbidden) override;
	void reset() override;
	void animate(long ticks) override;
	void render() override;

//protected:
    MantleBand _mantleBands[NumBands];
	Tentacle _tentacles[NumTentacles];
};


#endif // #ifndef OCTOPUS_H

