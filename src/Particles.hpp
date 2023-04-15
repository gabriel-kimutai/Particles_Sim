#include <raylib.h>
#include <vector>

class Particle {
   public:
    Vector2 position;
    Vector2 velocity;
    int radius;

    int particleNum = 200;
    std::vector<Particle> particles;

    void move();
    void bounce();
    void createParticles();
    void addParticles(int numToAdd);
};
