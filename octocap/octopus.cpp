#include "octopus.h"
#include "effects/crawling_stripe.h"

Effect * octopus_effects[1];

Octopus::Octopus()
{
	for (int i = 0; i < NumBands; ++i)
	{
		_mantleBands[i].set_band_id(i);
	}
	for (int i = 0; i < NumTentacles; ++i)
	{
		_tentacles[i].set_tentacle_id(i);
	}

    octopus_effects[0] = new CrawlingStripe(this);
}

Effect * Octopus::get_next_effect()
{
    return octopus_effects[random(sizeof(octopus_effects) / sizeof(octopus_effects[0]))];
}

void Octopus::reset()
{
}

void Octopus::animate(long ticks)
{
    effect_controller_.animate(ticks);
}

void Octopus::render()
{
    effect_controller_.render();
}

