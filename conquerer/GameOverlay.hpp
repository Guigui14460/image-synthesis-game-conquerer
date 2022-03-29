#ifndef __GAME_OVERLAY_HPP__
#define __GAME_OVERLAY_HPP__
#include "TextPrinter.hpp"

class GameOverlay {
public:
    GameOverlay();

    void update(float deltaTime);
    void render();

private:
//    TextPrinter m_textRenderer;
    // TODO: add meshes for the rectangles and timer (and minimap in future)
};

#endif // __GAME_OVERLAY_HPP__
