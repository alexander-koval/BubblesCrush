#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <map>
#include <functional>
#include "Screen.h"
#include "SFML/System/NonCopyable.hpp"
#include "SFML/System/Time.hpp"
#include <cassert>

namespace sf {
    class RenderWindow;
}

namespace Screens {
    enum class ID {
        NONE,
        GAME
    };
}

class ScreenManager : public sf::NonCopyable {
public:
    explicit ScreenManager(Screen::Context context);

    template <typename T>
    void addScreen(Screens::ID screenID);

    void removeScreen(Screens::ID screenID);

    void update(sf::Time dt);

    void draw(void);

    void setScreen(Screens::ID screenID);

    Screens::ID getCurrent(void) { return m_current; }

    Screens::ID getPrevious(void) { return m_previous; }

    bool isEmpty(void) const;

private:
    Screens::ID m_current;
    Screens::ID m_previous;
    Screen::Context m_context;
    std::map<Screens::ID, Screen::Ptr> m_screens;
    std::map<Screens::ID, std::function<Screen::Ptr()>> m_factories;
};

template <typename T>
void ScreenManager::addScreen(Screens::ID screenID) {
    m_factories[screenID] = [this]() {
        return Screen::Ptr(new T(m_context));
    };
    auto found = m_factories.find(screenID);
    assert(found != m_factories.end());

    m_screens[screenID] = found->second();
}

#endif // SCREENMANAGER_H
