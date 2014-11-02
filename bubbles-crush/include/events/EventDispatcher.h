#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include <map>
#include <vector>
#include <memory>
#include <functional>
#include "SFML/Window/Event.hpp"

class EventDispatcher {
public:
    typedef sf::Event::EventType Type;
    typedef std::function<void(sf::Event&)> Listener;
    typedef std::unique_ptr<std::vector<Listener*>> Vector;

    EventDispatcher(void);

    ~EventDispatcher(void);

    void addEventListener(Type type, Listener& listener);

    void removeEventListener(Type type, Listener& listener);

    void removeEventListeners(void);

    void dispatchEvent(sf::Event& event);

    bool hasEventListener(Type type);

private:
    bool invokeEvent(sf::Event& event);

private:
    std::map<Type, Vector> m_listeners;
};

#endif // EVENTDISPATCHER_H
