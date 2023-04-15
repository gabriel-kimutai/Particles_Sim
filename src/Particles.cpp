#include "Particles.hpp"
#include "defines.hpp"

void Particle::move()
{
    position.x += velocity.x * GetFrameTime();
    position.y += velocity.y * GetFrameTime();
}
void Particle::bounce()
{
    if (position.x >= SCREEN_WIDTH || position.x <= 0) {
        velocity.x *= -1;
    }
    if (position.y >= SCREEN_HEIGHT || position.y <= 0) {
        velocity.y *= -1;
    }
}
void Particle::createParticles()
{
    for (int i = 0; i < particleNum; i++) {
        Particle particle;

        particle.position = (Vector2){(float)GetRandomValue(0, SCREEN_WIDTH),
                                      (float)GetRandomValue(0, SCREEN_HEIGHT)};
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
            (Vector2){(float)GetRandomValue(0, SCREEN_WIDTH),
                      (float)GetRandomValue(0, SCREEN_HEIGHT)};
        newParticle.velocity = (Vector2){(float)GetRandomValue(-200, 200),
                                         (float)GetRandomValue(-200, 200)};
        newParticle.radius = 3;
        particles.push_back(newParticle);
    }
}
