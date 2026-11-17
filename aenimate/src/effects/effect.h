#ifndef EFFECT_H
#define EFFECT_H

#include "effect_controller.h"
#include "../octocap.h"

class Effect
{
public:
    Effect(EffectController * controller);
    virtual ~Effect();
    
    virtual void reset() = 0;
	virtual void animate(long ticks) = 0;
    virtual void render() = 0;

    virtual void report() const = 0;
protected:
    EffectController * controller_;
};

#endif // #ifndef EFFECT_H

