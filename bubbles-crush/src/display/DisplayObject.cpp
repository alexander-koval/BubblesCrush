#include <cassert>
#include "DisplayObject.h"
#include "iostream"

DisplayObject::DisplayObject(void) {

}

void DisplayObject::initialize(void) {

}

void DisplayObject::addChild(Ptr child) {
    child->m_parent = shared_from_this();
    m_children.push_back(child);
}

DisplayObject::Ptr DisplayObject::removeChild(const Ptr& child) {
    return this->removeChild(*child.get());
}

DisplayObject::Ptr DisplayObject::removeChild(const DisplayObject& child) {
    auto found = std::find_if(m_children.begin(), m_children.end(),
                              [&] (Ptr& p) -> bool {
        return (p.get() == &child);
    });
    assert(found != m_children.end());
    Ptr result = (*found);
    result->m_parent.reset();
    m_children.erase(found);
    return result;
}

DisplayObject::Ptr DisplayObject::getChildAt(int index) {
    Ptr child = m_children[index];
    assert(child);
    return child;
}

size_t DisplayObject::numChildren(void) {
    return m_children.size();
}

void DisplayObject::update(sf::Time dt) {
    this->updateCurrent(dt);
    this->updateChildren(dt);
}

void DisplayObject::removeFromParent(void) {
    Ptr parent = m_parent.lock();
    assert(parent);
    parent->removeChild(shared_from_this());
}

DisplayObject::Ptr DisplayObject::getParent(void) {
    Ptr parent = m_parent.lock();
    assert(parent != nullptr);
    return parent;
}

sf::Vector2f DisplayObject::getWorldPosition() const {
    return getWorldTransform() * sf::Vector2f();
}

sf::Transform DisplayObject::getWorldTransform() const {
    sf::Transform transform = sf::Transform::Identity;

    for (std::shared_ptr<const DisplayObject> object = shared_from_this(); object != nullptr; object = object->m_parent.lock()) {
        transform = object->getTransform() * transform;
    }

    return transform;
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
    for (std::shared_ptr<DisplayObject>& child_ptr : m_children) {
        assert(child_ptr);
        child_ptr->update(dt);
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
    std::vector<std::shared_ptr<DisplayObject> >::const_iterator it = m_children.begin();
    for (; it != m_children.end(); it++) {
        Ptr child_ptr = (*it);
        assert(child_ptr);
        child_ptr->draw(target, states);
    }
}
