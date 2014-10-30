#include "ScreenManager.h"
#include <iostream>
#include <cassert>

ScreenManager::ScreenManager(Screen::Context context)
    : m_current(Screens::ID::None)
    , m_previous(Screens::ID::None)
    , m_context(context) {

}

void ScreenManager::removeScreen(Screens::ID screenID) {

}

void ScreenManager::update(sf::Time dt) {
    m_screens[m_current]->update(dt);
}

void ScreenManager::draw(void) {
    Screen::Ptr& screen = m_screens[m_current];
    screen->draw();
}

void ScreenManager::setScreen(Screens::ID screenID) {
    if (m_current == Screens::ID::None) {
        m_current = screenID;
        Screen::Ptr& screen = m_screens[m_current];
        screen->enter();
    }
    if (m_current == screenID) {
        std::cout << "this object is already in the " << (uint32_t)screenID << " screen." << std::endl;
        return;
    } else {
        Screen::Ptr& screen = m_screens[m_current];
        screen->exit();
        m_previous = m_current;
        m_current = screenID;
        m_screens[m_current]->enter();
        return;
    }

}

bool ScreenManager::isEmpty(void) const {
    return m_screens.empty();
}
