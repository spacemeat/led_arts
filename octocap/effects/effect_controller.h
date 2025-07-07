#ifndef EFFECT_CONTROLLER_H
#define EFFECT_CONTROLLER_H

#include "../system.h"

class Effect;
class ObjectWithEffect;

class EffectController
{
public:
    EffectController(ObjectWithEffect * obj);
    ~EffectController();

    void set_next_effect();
    void set_next_effect(Effect * effect);
    void animate(long ticks);
    void render();
    void set_pixel(Effect * effect, CRGB * pixel_addr, CHSV color);
    void set_pixel(Effect * effect, int pixel_idx, CHSV color);

private:
    ObjectWithEffect * obj_;
    long _transitionTime = 0;
    int _blendFactor = 255;
    Effect * _effectA = nullptr;
    Effect * _effectB = nullptr;
};

class ObjectWithEffect
{
public:
    ObjectWithEffect();
    virtual ~ObjectWithEffect() = default;
    virtual Effect * get_next_effect() = 0;
    EffectController * get_controller() { return &effect_controller_; }

protected:
    EffectController effect_controller_;
};



#endif // #ifndef EFFECT_CONTROLLER_H

