#include "Screen.h"
#include "ScreenManager.h"

Screen::Context::Context(sf::RenderWindow &window, ScreenManager &manager, TextureManager &textures, FontManager &fonts)
    : m_window(window)
    , m_screenManager(manager)
    , m_textureManager(textures)
    , m_fontManager(fonts) {

}

Screen::Screen(Context context)
    : m_context(context) {

}

Screen::~Screen(void) {

}

const Screen::Context& Screen::getContext(void) const {
    return m_context;
}
