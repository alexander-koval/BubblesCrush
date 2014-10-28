#include <cassert>
#include "DisplayObject.h"
#include "iostream"

DisplayObject::DisplayObject(void)
: m_parent(nullptr) {

}

void DisplayObject::addChild(Ptr child) {
    child->m_parent = this;
    m_children.push_back(std::move(child));
}

DisplayObject::Ptr DisplayObject::removeChild(const Ptr &child) {
    return this->removeChild(*child.get());
}

DisplayObject::Ptr DisplayObject::removeChild(const DisplayObject &child) {
    auto found = std::find_if(m_children.begin(), m_children.end(),
                              [&] (Ptr& p) -> bool {
        return (p.get() == &child);
    });
    assert(found != m_children.end());
    Ptr result =std::move(*found);
    result->m_parent = nullptr;
    m_children.erase(found);
    return result;
}

void DisplayObject::update(sf::Time dt) {
    this->updateCurrent(dt);
    this->updateChildren(dt);
}

void DisplayObject::removeFromParent(void) {
    assert(m_parent != nullptr);
    m_parent->removeChild(*this);
}

DisplayObject* DisplayObject::getParent(void) {
    assert(m_parent != nullptr);
    return m_parent;
}

sf::FloatRect DisplayObject::getLocalBounds(void) const {
    return sf::FloatRect();
}

sf::FloatRect DisplayObject::getGlobalBounds(void) const {
    return sf::FloatRect();
}

void DisplayObject::updateCurrent(sf::Time dt) {

}

void DisplayObject::updateChildren(sf::Time dt) {
    for (Ptr& child : m_children) {
        child->update(dt);
    }
}


void DisplayObject::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= this->getTransform();
    drawCurrent(target, states);
    drawChildren(target, states);
}

void DisplayObject::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {

}

void DisplayObject::drawChildren(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const Ptr& child : m_children) {
        child->draw(target, states);
    }
}
