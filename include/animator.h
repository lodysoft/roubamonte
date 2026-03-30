// animator.h

// Queue-based card animation system using linear interpolation.
// Add animations via add(); call update() every frame with delta time.
// While isAnimating() returns true, the scene should block player input.

#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <deque>
#include <functional>

#include <SFML/Graphics.hpp>

#include "card_sprite.h"

struct animation
{
    card_sprite*         pSprite;       // Target sprite to move. Must remain valid for lifetime of animation.
    sf::Vector2f         vFrom;         // Starting position.
    sf::Vector2f         vTo;           // Destination position.
    float                fDuration;     // Total duration in seconds.
    float                fElapsed;      // Time elapsed so far.
    std::function<void()> fnOnComplete; // Optional callback fired when animation finishes.
};

class animator
{
public:
    animator();

    // Enqueue a slide animation for pSprite from vFrom to vTo over fSeconds.
    // An optional callback fnOnComplete fires when the animation finishes.
    void add(card_sprite* pSprite,
             sf::Vector2f vFrom,
             sf::Vector2f vTo,
             float fSeconds,
             std::function<void()> fnOnComplete = nullptr);

    // Advance all active animations by fDeltaTime seconds.
    // Completed animations are removed and their callbacks fired.
    void update(float fDeltaTime);

    // Returns true while any animations are in flight.
    bool isAnimating() const;

    // Discard all pending animations and snap sprites to their destinations.
    void flush();

private:
    std::deque<animation> dqQueue;

    static float lerp(float fA, float fB, float fT);
    static float ease_in_out(float fT);     // Smoothstep — feels better than raw lerp.
};

#endif
