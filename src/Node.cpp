#include "Node.hpp"

#include <raylib.h>

#include <cmath>
#include <cstdio>
#include <thread>
#include <vector>

#include "Gui.hpp"
#include "defines.hpp"

typedef struct RenderBox {
    int width;
    int height;
} RenderBox;

RenderBox renderBox{600, SCREEN_HEIGHT};

Font Iosevka;

void move(std::vector<Node>* v_nodes)
{
    for (int i = 0; i < v_nodes->size(); i++) {
        v_nodes->data()[i].position.x += v_nodes->data()[i].velocity.x * GetFrameTime();
        v_nodes->data()[i].position.y += v_nodes->data()[i].velocity.y * GetFrameTime();
    }
}

static void createNodes(int particleNum, std::vector<Node>* v_nodes)
{
    int red = 0;
    int purple = 0;
    int green = 0;

    for (int i = 0; i < particleNum; i++) {
        Node particle;

        particle.position = (Vector2){(float)GetRandomValue(10, renderBox.width - 10),
                                      (float)GetRandomValue(10, renderBox.height - 10)};
        particle.velocity = (Vector2){(float)GetRandomValue(-200, 200), (float)GetRandomValue(-200, 200)};

        particle.radius = GetRandomValue(3, 5);

        if (i % 5 == 0) {
            particle.race = M_GREEN;
            green += 1;
        }
        if (i % 2 == 0) {
            particle.race = M_PURPLE;
            purple += 1;
        }
        if (i % 3 == 0) {
            particle.race = RED;
            red += 1;
        }

        v_nodes->push_back(particle);
    }
    printf("green: %i\n", green);
    printf("purple: %i\n", purple);
    printf("red: %i\n", red);
}

static void wallCollision(std::vector<Node>& v_nodes)
{
    for (int i = 0; i < v_nodes.size(); i++) {
        if (v_nodes[i].position.x + v_nodes[i].radius >= renderBox.width ||
            v_nodes[i].position.x - v_nodes[i].radius <= 0) {
            v_nodes[i].velocity.x *= -1.0f;
        }
        if (v_nodes[i].position.y + v_nodes[i].radius >= SCREEN_HEIGHT ||
            v_nodes[i].position.y - v_nodes[i].radius <= 0) {
            v_nodes[i].velocity.y *= -1.0f;
        }
    }
}

/* void removeNodes()
{
    for (int i = 0; i < 10; i++) {
        particles.pop_back();
    }
} */

void drawConnectors(std::vector<Node>& v_nodes)
{
    for (int i = 0; i < v_nodes.size(); i++) {
        for (int j = 0; j <= i - 1; j++) {
            float distX = v_nodes[j].position.x - v_nodes[i].position.x;
            float distY = v_nodes[j].position.y - v_nodes[i].position.y;
            float distance = std::sqrt(std::pow(distX, 2) + std::pow(distY, 2));
            if (distance <= 60 && v_nodes[i].race.r == v_nodes[j].race.r) {
                DrawLineEx(v_nodes[i].position, v_nodes[j].position, 2, v_nodes[i].race);
            }
            // printf("distance between p[%i] and p[%i]: %f\n", i, j,
            //        distance);
        }
    }
}

/* void Node::infoLog()
{
    for (i = 0; i < particles.size(); i++) {
        printf("p[%i]: (%i, %i, %i)\n", i, (int)particles[i].race.r,
               (int)particles[i].race.g, (int)particles[i].race.b);
    }
} */

/* void circleCollision()
{
    for (i = 0; i < particles.size(); i++) {
        for (j = 0; j < i; j++) {
            float distX = particles[j].position.x - particles[i].position.x;
            float distY = particles[j].position.y - particles[i].position.y;
            float distance = std::sqrt(std::pow(distX, 2) + std::pow(distY,
            2)); if (CheckCollisionCircles(
                    particles[i].position, particles[i].radius,
                    particles[j].position, particles[j].radius)) {
                particles[i].velocity.x *= -1.0f;
                particles[i].velocity.y *= -1.0f;
            }
        }
    }
} */

void Node::init(int numberOfNodes)
{
    std::thread create(createNodes, numberOfNodes, &nodes);
    create.join();
    printf("r_size: %lu\n", nodes.size());
}

void Node::addNodes()
{
    if (IsKeyPressed(KEY_A)) {
        createNodes(10, &nodes);
    }
}

void Node::deleteNodes()
{
    if (IsKeyPressed(KEY_R)) {
        for (int i = 0; i < 5; i++) {
            nodes.pop_back();
        }
    }
}

void Node::draw()
{
    for (int i = 0; i < nodes.size(); i++) {
        DrawCircleV(nodes[i].position, nodes[i].radius, nodes[i].race);
    }
}

void Node::update()
{
    move(&nodes);
    wallCollision(nodes);
    drawConnectors(nodes);
    deleteNodes();
}
