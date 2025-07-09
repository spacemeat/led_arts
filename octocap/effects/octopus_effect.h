#ifndef OCTOPUSEFFECT_H
#define OCTOPUSEFFECT_H

#include "effect.h"
#include "../octopus.h"

class OctopusEffect : public Effect
{
public:
    OctopusEffect(Octopus * octopus);
    ~OctopusEffect() override;
    
    void reset() override = 0;
	void animate(long ticks) override = 0;
    void render() override = 0;

    void report() const override = 0;

protected:
	Octopus * octopus_;
};

#endif // #ifndef OCTOPUSEFFECT_H

