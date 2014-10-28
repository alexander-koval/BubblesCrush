#include "GameScreen.h"

GameScreen::GameScreen(Context context)
    : Screen(context)
    , m_world(context) {

}

void GameScreen::draw(void) {
    m_world.draw();
}

void GameScreen::enter(void) {

}

bool GameScreen::update(sf::Time dt) {
    m_world.update(dt);
    return true;
}

void GameScreen::exit(void) {

}





