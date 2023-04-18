#include <raylib.h>
#include <vector>

class Node {
   public:
    Vector2 position;
    Vector2 velocity;
    int radius;
    Color race;
    void init(int numberOfParticles);

    std::vector<Node> nodes;
    float minDistance;

    void draw();
    void addNodes();
    void deleteNodes();
    void update();
    void infoLog();
};
