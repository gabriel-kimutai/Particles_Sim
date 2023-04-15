#include <raylib.h>

#include <vector>

class Particle {
   public:
    std::vector<Particle> particles;
    float minDistance;

    void drawParticles(bool renderNodes);
    void drawConnectors();
    void drawNames(); 
    void move();
    void bounce();
    void createParticles();
    void removeParticles();
    void circleCollision();
    void addParticles(int numToAdd);

   private:
    int particleNum = 200;
    Vector2 position;
    Vector2 velocity;
    int radius;
    int i, j;
};
