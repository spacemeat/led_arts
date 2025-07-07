#ifndef OCTOPUSEFFECT_H
#define OCTOPUSEFFECT_H

#include "effect.h"
#include "../octopus.h"

class OctopusEffect : public Effect
{
public:
    OctopusEffect(Octopus * octopus);
    virtual ~OctopusEffect();
    
    virtual void reset() = 0;
	virtual void animate(long ticks) = 0;
    virtual void render() = 0;
protected:
	Octopus * octopus_;
};

#endif // #ifndef OCTOPUSEFFECT_H

