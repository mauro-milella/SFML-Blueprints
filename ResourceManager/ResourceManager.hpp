#pragma once

#include <unordered_map> 
#include <string> 
#include <memory> 

#include <SFML/Audio.hpp>

namespace Engine
{
    template<typename RESOURCE,typename IDENTIFIER = int>
    class ResourceManager
    {
        public:
            ResourceManager(const ResourceManager&) = delete;
            ResourceManager& operator=(const ResourceManager&) = delete;

            ResourceManager() = default;

            template<typename ... Args>
            void load(const IDENTIFIER& id, Args&& ... args);

            RESOURCE& get(const IDENTIFIER& id) const;

        private:
            std::unordered_map<IDENTIFIER, std::unique_ptr<RESOURCE>> _map;
    };

    template<typename IDENTIFIER>
    class ResourceManager<sf::Music, IDENTIFIER>
    {
        public:
            ResourceManager(const ResourceManager&) = delete;
            ResourceManager& operator=(const ResourceManager&) = delete;

            ResourceManager() = default;

            template<typename ... Args>
            void load(const IDENTIFIER& id, Args&& ... args);

            sf::Music& get(const IDENTIFIER& id) const;

        private:
            std::unordered_map<IDENTIFIER, std::unique_ptr<sf::Music>> _map;
    };
}

#include <SFML-Book/ResourceManager.tpl>

#endif