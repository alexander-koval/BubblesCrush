#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "SFML/System/NonCopyable.hpp"
#include "Screen.h"
#include "World.h"

class GameScreen : public Screen, public sf::NonCopyable {
public:
    GameScreen(Context context);

    virtual void draw(void);

    virtual void enter(void);

    virtual bool update(sf::Time dt);

    virtual void exit(void);

private:
    World m_world;
};

#endif // GAMESCREEN_H
