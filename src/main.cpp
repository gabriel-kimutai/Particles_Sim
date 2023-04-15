#include <raylib.h>
#include <stdio.h>

#include <cmath>
#include <string>
#include <thread>
#include <vector>

#include "Gui.hpp"
#include "Particles.hpp"
#include "defines.hpp"

int main(int argc, char *argv[])
{
    SetTraceLogLevel(LOG_NONE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "particles");
    SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    SetTargetFPS(120);

    // node.createParticles();

    Gui gui;
    gui.width = 200;
    gui.height = SCREEN_HEIGHT;
    gui.position = (Vector2){(float)SCREEN_WIDTH - gui.width, 0};

    Rectangle box = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f,
                     (float)GetScreenWidth(), 20};
    Particle node;
    node.minDistance = 40;

    while (!WindowShouldClose()) {
        ClearBackground(BLACK);
        BeginDrawing();

        // Draw GUI
        gui.drawGui();
        DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 12, WHITE);
        DrawText(TextFormat("Particles: %d", node.particles.size()), 15,
                 SCREEN_HEIGHT - 10, 12, WHITE);
        node.drawParticles(false);
        node.drawConnectors();
        if (IsKeyPressed(KEY_A)) {
            node.addParticles(10);
        }
        if (IsKeyPressed(KEY_R)) {
            node.removeParticles();
        }
        EndDrawing();
    }
    CloseWindow();
}
