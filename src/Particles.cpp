#include "Particles.hpp"

#include <raylib.h>

#include <cmath>
#include <cstdio>

#include "Gui.hpp"
#include "defines.hpp"

typedef struct RenderBox {
    int width;
    int height;
} RenderBox;

RenderBox renderBox{600, SCREEN_HEIGHT};

Font Iosevka;

void Particle::move()
{
    position.x += velocity.x * GetFrameTime();
    position.y += velocity.y * GetFrameTime();
}
void Particle::bounce()
{
    if (position.x + radius >= renderBox.width || position.x - radius <= 0) {
        velocity.x *= -1.0f;
    }
    if (position.y + radius >= SCREEN_HEIGHT || position.y - radius <= 0) {
        velocity.y *= -1.0f;
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
        particle.radius = 6;
        particles.push_back(particle);
    }
}
void Particle::addParticles(int numToAdd)
{
    for (int i = 0; i < numToAdd; i++) {
        Particle newParticle;

        newParticle.position =
            (Vector2){renderBox.width / 2.0f, renderBox.height / 2.0f};
        newParticle.velocity = (Vector2){(float)GetRandomValue(-200, 200),
                                         (float)GetRandomValue(-200, 200)};
        newParticle.radius = 6;
        particles.push_back(newParticle);
    }
}

void Particle::drawParticles(bool renderNodes)
{
    for (i = 0; i < particles.size(); i++) {
        if (renderNodes) {
            DrawCircleV(particles[i].position, particles[i].radius, GREEN);
        }
        if (!IsKeyDown(KEY_SPACE)) {
            particles[i].move();
        }
        particles[i].bounce();
    }
}

void Particle::removeParticles()
{
    for (int i = 0; i < 10; i++) {
        particles.pop_back();
    }
}

void Particle::drawConnectors()
{
    for (i = 0; i < particles.size(); i++) {
        for (j = 0; j <= i - 1; j++) {
            float distX = particles[j].position.x - particles[i].position.x;
            float distY = particles[j].position.y - particles[i].position.y;
            float distance = std::sqrt(std::pow(distX, 2) + std::pow(distY, 2));
            if (distance <= minDistance && distance != 0) {
                DrawLineV(particles[i].position, particles[j].position, PURPLE);
            }
            /* printf("distance between p[%i] and p[%i]: %f\n", i, j,
                   distance); */
        }
    }
}

void Particle::drawNames()
{
    Iosevka = LoadFont("../assets/Iosevka Nerd Font Complete Medium.ttf");
    for (i = 0; i < particles.size(); i++) {
        for (j = 0; j <= i; j++) {
            DrawTextPro(Iosevka, TextFormat("p[%d] : p[%d]", i, j),
                        particles[i].position, (Vector2){0, 0}, 0, 12, 1,
                        GREEN);
            /* printf("distance between p[%i] and p[%i]: %f\n", i, j,
                   distance); */
        }
    }
    UnloadFont(Iosevka);
}

void Particle::circleCollision()
{
    for (i = 0; i < particles.size(); i++) {
        for (j = 0; j < i; j++) {
            float distX = particles[j].position.x - particles[i].position.x;
            float distY = particles[j].position.y - particles[i].position.y;
            float distance = std::sqrt(std::pow(distX, 2) + std::pow(distY, 2));
            if (CheckCollisionCircles(
                    particles[i].position, particles[i].radius,
                    particles[j].position, particles[j].radius)) {
                particles[i].velocity.x *= -1.0f;
                particles[i].velocity.y *= -1.0f;
            }
        }
    }
}
