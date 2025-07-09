#ifndef EFFECT_CONTROLLER_H
#define EFFECT_CONTROLLER_H

#include "../system.h"

class Effect;
class ObjectWithEffect;

class EffectController
{
public:
    EffectController();
    ~EffectController();

    void set_object(ObjectWithEffect * obj);

    Effect * get_effect_A() const { return _effectA; }
    Effect * get_effect_B() const { return _effectB; }

    void set_next_effect();
    void set_next_effect(Effect * effect);
    void animate(long ticks);
    void render();
    void set_pixel(Effect * effect, CRGB * pixel_addr, CHSV color);
    void set_pixel(Effect * effect, int pixel_idx, CHSV color);

    void report();

private:
    ObjectWithEffect * obj_ = nullptr;
    long _transitionTime = 0;
    int _blendFactor = 255;
    Effect * _effectA = nullptr;
    Effect * _effectB = nullptr;
};

class ObjectWithEffect
{
public:
    ObjectWithEffect() = default;
    virtual ~ObjectWithEffect() = default;
    virtual Effect * get_next_effect() = 0;
    EffectController * get_controller() { return &effect_controller_; }
	virtual void reset() = 0;
	virtual void animate(long ticks) = 0;
	virtual void render() = 0;

protected:
    EffectController effect_controller_;
};



#endif // #ifndef EFFECT_CONTROLLER_H

