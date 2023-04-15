#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "Gui.hpp"
#include "defines.hpp"

void Gui::drawGui()
{
    guiContainer = {position.x, position.y, (float)width, (float)height};
    GuiWindowBox(guiContainer, "Controls");
}
