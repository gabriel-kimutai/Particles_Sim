#include <raylib.h>

#include <vector>

class Node {
   public:
    std::vector<Node> nodes;
    float minDistance;

    void draw();
    void addNodes();
    void deleteNodes();
    void update();
    void infoLog();
    void init(int numberOfParticles);

    Vector2 position;
    Vector2 velocity;
    int radius;
    Color race;
};
