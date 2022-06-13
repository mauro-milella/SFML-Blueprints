#pragma once

#include "Action.hpp"

#include <map>

template <typename T = int>
class ActionMap {

public:
    ActionMap(const ActionMap<T>&) = delete;
    ActionMap& operator=(const ActionMap<T>&) = delete; 

    ActionMap() = default;

    void map(const T& key, const Action& action);
    const Action& get(const T& key) const;

private:
    std::unordered_map<T, Action> _map;

};

#include "ActionMap.inl"