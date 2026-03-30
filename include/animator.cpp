// animator.cpp

#include "animator.h"

// ── Constructor ───────────────────────────────────────────────────────────────
animator::animator() {}

// ── Public interface ──────────────────────────────────────────────────────────
void animator::add(card_sprite*          pSprite,
                   sf::Vector2f          vFrom,
                   sf::Vector2f          vTo,
                   float                 fSeconds,
                   std::function<void()> fnOnComplete)
{
    if (!pSprite) return;
    if (fSeconds <= 0.0f)
    {
        // Zero-duration: snap immediately and fire callback.
        pSprite->set_position(vTo);
        if (fnOnComplete) fnOnComplete();
        return;
    }

    animation anm;
    anm.pSprite      = pSprite;
    anm.vFrom        = vFrom;
    anm.vTo          = vTo;
    anm.fDuration    = fSeconds;
    anm.fElapsed     = 0.0f;
    anm.fnOnComplete = fnOnComplete;

    // Snap to starting position immediately so there is no visual jump.
    pSprite->set_position(vFrom);

    dqQueue.push_back(anm);
}

void animator::update(float fDeltaTime)
{
    for (auto& anm : dqQueue)
    {
        anm.fElapsed += fDeltaTime;

        float fT = anm.fElapsed / anm.fDuration;
        if (fT > 1.0f) fT = 1.0f;

        float fSmooth = ease_in_out(fT);

        anm.pSprite->set_position(sf::Vector2f(
            lerp(anm.vFrom.x, anm.vTo.x, fSmooth),
            lerp(anm.vFrom.y, anm.vTo.y, fSmooth)
        ));
    }

    // Remove finished animations from the front and fire their callbacks.
    while (!dqQueue.empty() && dqQueue.front().fElapsed >= dqQueue.front().fDuration)
    {
        animation& anm = dqQueue.front();
        anm.pSprite->set_position(anm.vTo);     // Snap to exact destination.
        if (anm.fnOnComplete) anm.fnOnComplete();
        dqQueue.pop_front();
    }
}

bool animator::isAnimating() const
{
    return !dqQueue.empty();
}

void animator::flush()
{
    while (!dqQueue.empty())
    {
        animation& anm = dqQueue.front();
        anm.pSprite->set_position(anm.vTo);
        if (anm.fnOnComplete) anm.fnOnComplete();
        dqQueue.pop_front();
    }
}

// ── Private helpers ───────────────────────────────────────────────────────────
float animator::lerp(float fA, float fB, float fT)
{
    return fA + (fB - fA) * fT;
}

float animator::ease_in_out(float fT)
{
    // Smoothstep: 3t² - 2t³
    return fT * fT * (3.0f - 2.0f * fT);
}
