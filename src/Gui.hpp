#include <raylib.h>

class Gui {
   public:
    int width;
    int height;
    Vector2 position;
    Rectangle guiContainer;

    void drawGui();
};
