#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "Screen.h"
#include "World.h"

class GameScreen : public Screen {
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
