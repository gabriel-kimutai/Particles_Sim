#include <raylib.h>
#include <stdio.h>

#include <cmath>
#include <string>
#include <vector>

#include "Particles.hpp"
#include "Gui.hpp"
#include "defines.hpp"

int main(int argc, char *argv[])
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "particles");
    SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    SetTargetFPS(120);

    Font Iosevka;
    Iosevka = LoadFont("./assets/Iosevka Nerd Font Complete Medium.ttf");

    Particle point;
    point.createParticles();

    Gui gui;
    gui.width = 200;
    gui.height = SCREEN_HEIGHT;
    gui.position = (Vector2){(float)SCREEN_WIDTH - gui.width, 0};

    Rectangle box = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f,
                     (float)GetScreenWidth(), 20};
    float minDistance = 40;

    while (!WindowShouldClose()) {
        ClearBackground(BLACK);
        BeginDrawing();
        // Draw GUI
        gui.drawGui();
        DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 12, WHITE);
        DrawText(TextFormat("Particles: %d", point.particles.size()), 15,
                 SCREEN_HEIGHT - 10, 12, WHITE);
        if (IsKeyPressed(KEY_A)) {
            point.addParticles(10);
        }
        if (IsKeyPressed(KEY_R)) {
            for (int i = 0; i < 5; i++) {
                point.particles.pop_back();
            }
        }
        int i, j;
        for (i = 0; i < point.particles.size(); i++) {
            // DrawCircleV(point.particles[i].position,
            // point.particles[i].radius, BLANK);
            if (!IsKeyDown(KEY_SPACE)) {
                point.particles[i].move();
            }
            point.particles[i].bounce();
            for (j = 0; j <= i - 1; j++) {
                float distX = point.particles[j].position.x -
                              point.particles[i].position.x;
                float distY = point.particles[j].position.y -
                              point.particles[i].position.y;
                float distance =
                    std::sqrt(std::pow(distX, 2) + std::pow(distY, 2));
                if (distance <= minDistance && distance != 0) {
                    DrawLineV(point.particles[i].position,
                              point.particles[j].position, PURPLE);
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
        // printf("Number of particles: %d \n", (int)point.particles.size());
        EndDrawing();
    }
    UnloadFont(Iosevka);
    CloseWindow();
}
