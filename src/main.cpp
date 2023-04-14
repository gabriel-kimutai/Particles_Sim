#include <raylib.h>
#include <stdio.h>

#include <cmath>
#include <string>
#include <vector>

unsigned int screenWidth = 800;
unsigned int screenHeight = 450;

class Particle {
   public:
    Vector2 position;
    Vector2 velocity;
    int radius;

    void move()
    {
        position.x += velocity.x * GetFrameTime();
        position.y += velocity.y * GetFrameTime();
    }
    void bounce()
    {
        if (position.x >= screenWidth || position.x <= 0) {
            velocity.x *= -1;
        }
        if (position.y >= screenHeight || position.y <= 0) {
            velocity.y *= -1;
        }
    }
};

int particleNum = 200;
std::vector<Particle> particles;

void createParticles()
{
    for (int i = 0; i < particleNum; i++) {
        Particle particle;

        particle.position = (Vector2){(float)GetRandomValue(0, screenWidth),
                                      (float)GetRandomValue(0, screenHeight)};
        particle.velocity = (Vector2){(float)GetRandomValue(-200, 200),
                                      (float)GetRandomValue(-200, 200)};
        particle.radius = 3;
        particles.push_back(particle);
    }
}

void addParticles(int numToAdd)
{
    for (int i = 0; i < numToAdd; i++) {
        Particle newParticle;

        newParticle.position =
            (Vector2){(float)GetRandomValue(0, screenWidth),
                      (float)GetRandomValue(0, screenHeight)};
        newParticle.velocity = (Vector2){(float)GetRandomValue(-200, 200),
                                         (float)GetRandomValue(-200, 200)};
        newParticle.radius = 3;
        particles.push_back(newParticle);
    }
}
int main(int argc, char *argv[])
{
    InitWindow(screenWidth, screenHeight, "particles");
    SetWindowSize(screenWidth, screenHeight);
    SetTargetFPS(120);

    Font Iosevka;
    Iosevka = LoadFont("./assets/Iosevka Nerd Font Complete Medium.ttf");

    createParticles();

    while (!WindowShouldClose()) {
        ClearBackground(BLACK);
        BeginDrawing();
        DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 12, WHITE);
        DrawText(TextFormat("Particles: %d", particles.size()), 15,
                 screenHeight - 10, 12, WHITE);
        if (IsKeyPressed(KEY_A)) {
            addParticles(10);
        }
        if (IsKeyPressed(KEY_R)) {
            for (int i = 0; i < 5; i++) {
                particles.pop_back();
            }
        }
        int i, j;
        for (i = 0; i < particles.size(); i++) {
            // DrawCircleV(particles[i].position, particles[i].radius, BLANK);
            if (!IsKeyDown(KEY_SPACE)) {
                particles[i].move();
            }
            particles[i].bounce();
            for (j = 0; j <= i - 1; j++) {
                float distX = particles[j].position.x - particles[i].position.x;
                float distY = particles[j].position.y - particles[i].position.y;
                float distance =
                    std::sqrt(std::pow(distX, 2) + std::pow(distY, 2));
                if (distance <= 50 && distance != 0) {
                    DrawLineV(particles[i].position, particles[j].position,
                              PURPLE);
                }
                /* DrawTextPro(Iosevka,
                            TextFormat("p[%d]: (%f, %f)\n d: %.2f", i,
                                       particles[i].position.x,
                                       particles[i].position.y, distance),
                            particles[i].position, (Vector2){0, 0}, 0, 12, 1,
                            GREEN); */
                /* printf("distance between p[%i] and p[%i]: %f\n", i, j,
                       distance); */
            }
        }
        // printf("Number of particles: %d \n", (int)particles.size());
        EndDrawing();
    }
    UnloadFont(Iosevka);
    CloseWindow();
}
