#ifndef EFFECT_H
#define EFFECT_H

#include "octocap.h"

class Effect
{
public:
    Effect(Octopus const * octopus);
    virtual ~Effect();
    
	virtual void animate(long ticks) = 0;
private:
	Octopus * _octopus;
};

#endif // #ifndef EFFECT_H

