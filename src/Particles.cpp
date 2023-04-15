#include "Particles.hpp"

#include "Gui.hpp"
#include "defines.hpp"

typedef struct RenderBox {
    int width;
    int height;
} RenderBox;

RenderBox renderBox {600, SCREEN_HEIGHT};

void Particle::move()
{
    position.x += velocity.x * GetFrameTime();
    position.y += velocity.y * GetFrameTime();
}
void Particle::bounce()
{
    if (position.x + radius >= renderBox.width || position.x + radius <= 0) {
        velocity.x *= -1;
    }
    if (position.y + radius >= SCREEN_HEIGHT || position.y + radius <= 0) {
        velocity.y *= -1;
    }
}
void Particle::createParticles()
{
    for (int i = 0; i < particleNum; i++) {
        Particle particle;

        particle.position =
            (Vector2){(float)GetRandomValue(0, renderBox.width),
                      (float)GetRandomValue(0, renderBox.height)};
        particle.velocity = (Vector2){(float)GetRandomValue(-200, 200),
                                      (float)GetRandomValue(-200, 200)};
        particle.radius = 3;
        particles.push_back(particle);
    }
}
void Particle::addParticles(int numToAdd)
{
    for (int i = 0; i < numToAdd; i++) {
        Particle newParticle;

        newParticle.position =
            (Vector2){(float)GetRandomValue(0, renderBox.width),
                      (float)GetRandomValue(0, renderBox.height)};
        newParticle.velocity = (Vector2){(float)GetRandomValue(-200, 200),
                                         (float)GetRandomValue(-200, 200)};
        newParticle.radius = 3;
        particles.push_back(newParticle);
    }
}
