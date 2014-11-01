#ifndef SPRITEPOOL_H
#define SPRITEPOOL_H

#include <vector>
#include <memory>
#include "DisplayObject.h"

template <typename Sprite>
class SpritePool {
public:
    typedef std::unique_ptr<DisplayObject> Ptr;

    SpritePool(int size, int growth);

    Ptr getSprite(void);

    void setSprite(Ptr sprite);

private:
    std::size_t m_growth;
    std::size_t m_counter;
    std::vector<std::unique_ptr<DisplayObject>> m_pool;
};


template <typename Sprite>
SpritePool<Sprite>::SpritePool(int size, int growth)
    : m_growth(growth)
    , m_counter(size)
    , m_pool(size) {
    int index = size;
    while (--index > -1) {
        m_pool[index] = std::unique_ptr<DisplayObject>(new Sprite());
    }
}

template <typename Sprite>
std::unique_ptr<DisplayObject> SpritePool<Sprite>::getSprite(void) {
    if (m_counter > 0) {
        std::unique_ptr<DisplayObject>& result = m_pool[--m_counter];
        return std::move(result);
    }
    int index = m_growth;
    while (--index > -1) {
        m_pool.push_back(std::unique_ptr<Sprite>(new Sprite()));
    }
    m_counter = m_growth;
    return getSprite();
}

template <typename Sprite>
void SpritePool<Sprite>::setSprite(std::unique_ptr<DisplayObject> sprite) {
    m_pool[m_counter++] = std::move(sprite);
}



#endif // SPRITEPOOL_H
