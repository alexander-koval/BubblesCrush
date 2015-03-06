#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>
#include <ResourceDirectory.h>

template <typename Resource, typename Identifier>
class ResourceManager {
public:
    void load(Identifier id, const std::string& filename);

    void load(Identifier id, const char* filename1, const char* filename2);

    void load(Identifier id, const std::string &filename1, const std::string &filename2);

    template <typename Parameter>
    void load(Identifier id, const std::string& filename, const Parameter& param);

    Resource& get(Identifier id);

    const Resource& get(Identifier id) const;

private:
    void insert(Identifier id, std::unique_ptr<Resource> resource);

private:
    std::map<Identifier, std::unique_ptr<Resource>> m_resourceMap;
};

#include "ResourceManager.inl"

#endif // RESOURCEMANAGER_H
