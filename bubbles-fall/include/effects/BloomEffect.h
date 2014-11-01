#ifndef BOOK_BLOOMEFFECT_HPP
#define BOOK_BLOOMEFFECT_HPP

#include "PostEffect.h"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Shader.hpp"
#include "ResourceManager.h"
#include "Resources.h"
#include <array>


class BloomEffect : public PostEffect {
public:
    BloomEffect(void);

    virtual void apply(const sf::RenderTexture& input, sf::RenderTarget& output);

private:
    typedef std::array<sf::RenderTexture, 2> RenderTextureArray;

private:
    void prepareTextures(sf::Vector2u size);
    void blurMultipass(RenderTextureArray& renderTextures);
    void blur(const sf::RenderTexture& input, sf::RenderTexture& output, sf::Vector2f offsetFactor);
    void downsample(const sf::RenderTexture& input, sf::RenderTexture& output);
    void add(const sf::RenderTexture& source, const sf::RenderTexture& bloom, sf::RenderTarget& target);

private:
    ShaderManager		m_shaderManager;
    sf::RenderTexture	m_brightnessTexture;
    RenderTextureArray	m_firstPassTextures;
    RenderTextureArray	m_secondPassTextures;
};

#endif // BOOK_BLOOMEFFECT_HPP
