#include "ScreenManager.h"
#include <iostream>
#include <cassert>

ScreenManager::ScreenManager(Screen::Context context)
    : m_current(Screens::ID::NONE)
    , m_previous(Screens::ID::NONE)
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
    if (m_current == Screens::ID::NONE) {
        m_current = screenID;
        Screen::Ptr& screen = m_screens[m_current];
        screen->enter();
    }
    if (m_current == screenID) {
        std::cout << "this object is already in the " << (uint32_t)screenID << " screen." << std::endl;
        return;
    } else {
        std::cout << "screen " << (uint32_t)screenID << " cannot be used while in the " << (uint32_t)m_current << " state." << std::endl;
        return;
    }

}

bool ScreenManager::isEmpty(void) const {
    return m_screens.empty();
}
