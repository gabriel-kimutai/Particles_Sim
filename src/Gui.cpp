#define RAYGUI_IMPLEMENTATION
#include "Gui.hpp"

#include <raygui.h>

#include "defines.hpp"

void Gui::drawGui()
{
    guiContainer = {position.x, position.y, (float)width, (float)height};
    GuiWindowBox(guiContainer, "Controls");
}
