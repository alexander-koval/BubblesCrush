#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#include <memory>
#include <vector>
#include "SFML/System/Time.hpp"
#include "SFML/System/NonCopyable.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"

class DisplayObject : public sf::Transformable, public sf::Drawable, public sf::NonCopyable {
public:
    typedef std::shared_ptr<DisplayObject> Ptr;

    explicit DisplayObject(void);

    void addChild(Ptr child);

    Ptr removeChild(const DisplayObject& child);

    void update(sf::Time dt);

    void removeFromParent(void);

    DisplayObject* getParent(void) { return m_parent; }

protected:
    virtual void updateCurrent(sf::Time dt);
    virtual void updateChildren(sf::Time dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    std::vector<Ptr> m_children;
    DisplayObject* m_parent;
};

#endif // DISPLAYOBJECT_H
