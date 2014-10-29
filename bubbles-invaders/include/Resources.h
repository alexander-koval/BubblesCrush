#ifndef RESOURCES_H
#define RESOURCES_H

namespace sf {
class Texture;
class Font;
class Shader;
}

namespace Textures {
enum class ID {
    Background,
    Particle
};
}

namespace Shaders {
enum ID {
    BrightnessPass,
    DownSamplePass,
    GaussianBlurPass,
    AddPass,
};
}

namespace Fonts {
enum class ID {
    Main
};
}

template <typename Resource, typename Identifier>
class ResourceManager;

typedef ResourceManager<sf::Font, Fonts::ID> FontManager;
typedef ResourceManager<sf::Texture, Textures::ID> TextureManager;
typedef ResourceManager<sf::Shader, Shaders::ID> ShaderManager;

#endif // RESOURCES_H
