#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#include <memory>
#include <vector>
#include "SFML/System/Time.hpp"
#include "SFML/System/NonCopyable.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"

class DisplayObject
        : public sf::Transformable
        , public sf::Drawable
        , public sf::NonCopyable
        , public std::enable_shared_from_this<DisplayObject> {
public:
    using Ptr = std::shared_ptr<DisplayObject>;

    explicit DisplayObject(void);

    virtual void initialize(void);

    virtual void addChild(Ptr child);

    virtual Ptr removeChild(const Ptr& child);

    virtual Ptr removeChild(const DisplayObject& child);

    void update(sf::Time dt);

    void removeFromParent(void);

    Ptr getParent(void);

    Ptr getChildAt(int index);

    size_t numChildren(void);

    sf::Vector2f getWorldPosition() const;

    sf::Transform getWorldTransform() const;

    virtual sf::FloatRect getLocalBounds(void) const;

    virtual sf::FloatRect getGlobalBounds(void) const;

protected:
    virtual void updateCurrent(sf::Time dt);
    virtual void updateChildren(sf::Time dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    std::vector<std::shared_ptr<DisplayObject>> m_children;
    std::weak_ptr<DisplayObject> m_parent;
};

#endif // DISPLAYOBJECT_H
