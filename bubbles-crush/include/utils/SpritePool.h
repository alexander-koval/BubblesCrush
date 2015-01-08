#ifndef SPRITEPOOL_H
#define SPRITEPOOL_H

#include <vector>
#include <memory>
#include "DisplayObject.h"

template <typename Sprite>
class SpritePool {
public:
//    typedef std::shared_ptr<DisplayObject> Ptr;
    using Ptr = std::shared_ptr<Sprite>;

    SpritePool(int size, int growth);

    Ptr getSprite(void);

    void setSprite(Ptr sprite);

private:
    std::size_t m_growth;
    std::size_t m_counter;
    std::vector<std::shared_ptr<Sprite>> m_pool;
};


template <typename Sprite>
SpritePool<Sprite>::SpritePool(int size, int growth)
    : m_growth(growth)
    , m_counter(size)
    , m_pool(size) {
    int index = size;
    while (--index > -1) {
        std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();
        sprite->initialize();
        m_pool[index] = sprite;
    }
}

template <typename Sprite>
std::shared_ptr<Sprite> SpritePool<Sprite>::getSprite(void) {
    if (m_counter > 0) {
        Ptr& result = m_pool[--m_counter];
        return std::move(result);
    }
    int index = m_growth;
    while (--index > -1) {
        m_pool.push_back(std::make_shared<Sprite>());
    }
    m_counter = m_growth;
    return getSprite();
}

template <typename Sprite>
void SpritePool<Sprite>::setSprite(Ptr sprite) {
    m_pool[m_counter++] = std::move(sprite);
}



#endif // SPRITEPOOL_H
