#include "ResourceDirectory.h"

template <typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string& filename) {
    std::string path = getResourcePath();
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(path + filename)) {
        throw std::runtime_error("ResourceManager::load - Failed to Load " + filename);
    }
    insert(id, std::move(resource));
}

template <typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::load(Identifier id, const char *filename1, const char *filename2) {
    load(id, std::string(filename1), std::string(filename2));
}

template <typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string& filename1, const std::string& filename2) {
    std::string path = getResourcePath();
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(path + filename1, path + filename2)) {
        throw std::runtime_error("ResourceManager::load - Failed to resource");
    }
    insert(id, std::move(resource));
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string &filename, const Parameter& param) {
    std::string path = getResourcePath();
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(path + filename, param)) {
        throw std::runtime_error("ResourceManager::load - Failed to load " + path + filename);
    }
    insert(id, std::move(resource));
}

template <typename Resource, typename Identifier>
Resource& ResourceManager<Resource, Identifier>::get(Identifier id) {
    auto found = m_resourceMap.find(id);
    assert(found != m_resourceMap.end());
    return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceManager<Resource, Identifier>::get(Identifier id) const {
    auto found = m_resourceMap.find(id);
    assert(found != m_resourceMap.end());
    return *found->second;
}

template <typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::insert(Identifier id, std::unique_ptr<Resource> resource) {
    auto inserted = m_resourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}
