#include "EventDispatcher.h"
#include <algorithm>
#include <iostream>

EventDispatcher::EventDispatcher(void) {

}

EventDispatcher::~EventDispatcher(void) {

}

void EventDispatcher::addEventListener(Type type, Listener& listener) {
    Vector& listeners = m_listeners[type];
    if (listeners == nullptr) {
        Vector list(new std::vector<Listener*>());
        m_listeners[type] = std::move(list);
    }
    listeners->push_back(&listener);
}

void EventDispatcher::removeEventListener(Type type, Listener& listener) {
    Vector& listeners = m_listeners[type];
    auto found = std::remove_if(listeners->begin(), listeners->end(), [&](Listener* list) {
        return (list == &listener);
    });
    if (found != listeners->end()) {
        listeners->erase(found);
    }
}

void EventDispatcher::removeEventListeners(void) {
    m_listeners.clear();
}

void EventDispatcher::dispatchEvent(sf::Event &event) {
    this->invokeEvent(event);
}

bool EventDispatcher::hasEventListener(Type type) {
    Vector& listeners = m_listeners[type];
    return listeners->size();
}

bool EventDispatcher::invokeEvent(sf::Event &event) {
    Vector& listeners = m_listeners[event.type];
    bool result = listeners->size();
    std::for_each(listeners->begin(), listeners->end(), [&](Listener* listener) {
        listener->operator()(event);
    });
    return result;
}
