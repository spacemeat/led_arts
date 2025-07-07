#include "effect_controller.h"
#include "effect.h"

EffectController::EffectController(ObjectWithEffect * obj)
: obj_(obj)
{
}

EffectController::~EffectController()
{
}

void EffectController::set_next_effect()
{
    // choose the next effect
    auto effect = obj_->get_next_effect();
    set_next_effect(effect);
}

void EffectController::set_next_effect(Effect * effect)
{
    _effectB = _effectA;
    _effectA = effect;
    
    _transitionTime = 0;
    _blendFactor = 256;
    _effectA->reset();
}

void EffectController::animate(long ticks)
{
    // update transition and blendFactor
    if (_transitionTime < EffectTransitionDuration)
    {
        bool effect_ended = false;

        _transitionTime += ticks;
        if (_transitionTime >= EffectTransitionDuration)
        {
            _transitionTime = EffectTransitionDuration;
            effect_ended = true;
        }
        long blend = (_transitionTime * 256) / EffectTransitionDuration;
        _blendFactor = 256 - static_cast<int>(blend);

        if (effect_ended)
        {
            set_next_effect();
        }
    }

    // animate effects
    _effectA->animate(ticks);
    _effectB->animate(ticks);
}

void EffectController::render()
{
    // set all CRGB to 0 first, so we can blend multiple effects
    for (int i = 0; i < NumLedsInMantle + NumLedsInTentacles; ++i)
    {
        frame_buffer[i] = CRGB(0, 0, 0);
    }
    
    // render effects
    _effectA->render();
    _effectB->render();
}

void EffectController::set_pixel(Effect * effect, CRGB * pixel_addr, CHSV color)
{
    color.v = min(color.v, MaxPower);
    int r = 0, g = 0, b = 0;
    CRGB rgb;

    if (effect == _effectA)
    {
        rgb = CRGB(color);
        r = (rgb.r * (_blendFactor)) >> 8;
        g = (rgb.g * (_blendFactor)) >> 8;
        b = (rgb.b * (_blendFactor)) >> 8;
        rgb = CRGB(r, g, b);
    }

    if (effect == _effectB)
    {
        rgb = CRGB(color);
        r = (rgb.r * (256 - _blendFactor)) >> 8;
        g = (rgb.g * (256 - _blendFactor)) >> 8;
        b = (rgb.b * (256 - _blendFactor)) >> 8;
        rgb = CRGB(r, g, b);
    }

    * pixel_addr += color;
}

void EffectController::set_pixel(Effect * effect, int pixel_idx, CHSV color)
{
    set_pixel(effect, frame_buffer + pixel_idx, color);
}

ObjectWithEffect::ObjectWithEffect()
: effect_controller_(this)
{
}
