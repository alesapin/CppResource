#pragma once
#include <string>
#include <string_view>
#include <unordered_map>
#include <optional>

namespace CppResource
{

class ResourceFactory;

/// Resource class for inner usage
namespace detail
{
class Resource
{
public:
    Resource(const unsigned char * data_, size_t size_)
        : data(reinterpret_cast<const char *>(data_))
        , size(size_)
    {
    }

    std::string toString() const { return std::string(data, size); }
    std::string_view toStringView() const { return std::string_view(data, size); }
private:
    const char * data;
    const size_t size;
};


}
namespace detail
{
class ResourceWrapper;
}

/// Class allows to read data bundled in binary
/// via add_resource CMake command. Singleton.
class ResourceFactory
{

    friend class detail::ResourceWrapper;
public:

    /// Get ResourceFactory instance
    static ResourceFactory & instance() {
        static ResourceFactory instance;
        return instance;
    }

    /// Check that factory contains some key
    bool has(const std::string & key) const
    {
        return data.count(key);
    }

    /// try get resource from factory as string
    /// return std::nullopt if not exists
    std::optional<std::string> tryGetAsString(const std::string & key) const
    {
        if (data.count(key))
            return data.at(key).toString();
        return {};
    }

    /// try get resource from factory as string_view
    /// return std::nullopt if not exists
    std::optional<std::string_view> tryGetAsStringView(const std::string & key) const
    {
        if (data.count(key))
            return data.at(key).toStringView();
        return {};
    }

    /// get resource from factory as string
    /// throws exception if not exists
    std::string getAsString(const std::string & key) const
    {
        return data.at(key).toString();
    }

    /// get resource from factory as string_view
    /// throws exception if not exists
    std::string_view getAsStringView(const std::string & key) const
    {
        return data.at(key).toStringView();
    }

private:
    ResourceFactory() = default;
    bool add(const std::string & key, const detail::Resource & resource)
    {
        return data.emplace(key, resource).second;
    }
private:
    std::unordered_map<std::string, detail::Resource> data;
};

namespace detail
{

class ResourceWrapper
{
public:
    ResourceWrapper(const std::string & key, const Resource & resource)
    {
        ResourceFactory::instance().add(key, resource);
    }
};

}

}
