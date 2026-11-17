#include "effect_controller.h"
#include "effect.h"

#ifndef ARDUINO
#include <ostream>
#endif

EffectController::EffectController()
{
}

EffectController::~EffectController()
{
}

void EffectController::set_object(ObjectWithEffect * obj)
{
    obj_ = obj;

    _effectA = obj_->get_next_effect(nullptr);
    _effectA->reset();

    _effectB = obj_->get_next_effect(_effectA);
    _effectB->reset();

    _transitionTime = EffectTransitionDuration;
    _blendFactor = 255;
}

void EffectController::set_next_effect()
{
    // choose the next effect
    auto effect = obj_->get_next_effect(_effectA);
    set_next_effect(effect);
}

void EffectController::set_next_effect(Effect * effect)
{
    _effectB = _effectA;
    _effectA = effect;
    
    _effectTime = 0;
    _transitionTime = 1024;
    _blendFactor = 255;
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
            _effectTime = _transitionTime - EffectTransitionDuration;
            _transitionTime = EffectTransitionDuration;
            effect_ended = true;
        }
        long blend = (_transitionTime * 255) / EffectTransitionDuration;
        _blendFactor = 255 - static_cast<int>(blend);

        if (effect_ended)
        {
            set_next_effect();
        }
    }
    else if (_effectTime < EffectDuration)
    {
        _effectTime += ticks;
        if (_effectTime >= EffectDuration)
        {
            _transitionTime = _effectTime - EffectDuration;
            _effectTime = EffectDuration;
        }
    }

    // animate effects
    if (_effectA)
        { _effectA->animate(ticks); }
    if (_effectB)
        { _effectB->animate(ticks); }
}

void EffectController::render()
{
    // set all CRGB to 0 first, so we can blend multiple effects
    for (int i = 0; i < NumLedsInMantle + NumLedsInTentacles; ++i)
    {
        frame_buffer[i] = CRGB(0, 0, 0);
    }
    
    // render effects
    if (_effectA)
        { _effectA->render(); }
    if (_effectB)
        { _effectB->render(); }
}

void EffectController::set_pixel(Effect * effect, CRGB * pixel_addr, CHSV color)
{
    color.v = min(color.v, MaxPower);
    int r = 0, g = 0, b = 0;
    CRGB rgb;

    if (effect == _effectA)
    {
        rgb = CRGB(color);
        r = ((int) rgb.r * (255 - _blendFactor)) >> 8;
        g = ((int) rgb.g * (255 - _blendFactor)) >> 8;
        b = ((int) rgb.b * (255 - _blendFactor)) >> 8;
        rgb = CRGB(r, g, b);
    }

    else if (effect == _effectB)
    {
        rgb = CRGB(color);
        r = ((int) rgb.r * (_blendFactor)) >> 8;
        g = ((int) rgb.g * (_blendFactor)) >> 8;
        b = ((int) rgb.b * (_blendFactor)) >> 8;
        rgb = CRGB(r, g, b);
    }

    * pixel_addr += rgb;
}

void EffectController::set_pixel(Effect * effect, int pixel_idx, CHSV color)
{
    set_pixel(effect, frame_buffer + pixel_idx, color);
}


void EffectController::report()
{
    //std::cout << "transition time: " << _transitionTime << "   \n"
    //          << "effect time: " << _effectTime << "   \n"
    //          << "blend factor: " << _blendFactor << "   \n";
}

