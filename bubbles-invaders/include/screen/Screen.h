#ifndef SCREEN_H
#define SCREEN_H

#include <memory>
#include "Resources.h"
#include "SFML/System/Time.hpp"

namespace sf {
class RenderWindow;
}

class ScreenManager;
class Screen {
public:
    typedef std::unique_ptr<Screen> Ptr;

    struct Context {
        Context(sf::RenderWindow& m_window,
                ScreenManager& manager,
                TextureManager& textures,
                FontManager& fonts);
        sf::RenderWindow& m_window;
        ScreenManager& m_screenManager;
        TextureManager& m_textureManager;
        FontManager& m_fontManager;
    };

public:
    Screen(Context context);

    virtual ~Screen(void);

    virtual void draw(void) = 0;

    virtual void enter(void) = 0;

    virtual bool update(sf::Time dt) = 0;

    virtual void exit(void) = 0;

protected:
    const Context& getContext(void) const;

private:
    Context m_context;
};

#endif // SCREEN_H
