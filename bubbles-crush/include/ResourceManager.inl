template <typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string& filename) {
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename)) {
        throw std::runtime_error("ResourceManager::load - Failed to Load " + filename);
    }
    insert(id, std::move(resource));
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string &filename, const Parameter& param) {
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename, param)) {
        throw std::runtime_error("ResourceManager::load - Failed to load " + filename);
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
