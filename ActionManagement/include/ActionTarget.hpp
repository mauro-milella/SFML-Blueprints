#pragma once

#include "Action.hpp"
#include "ActionMap.hpp"

#include <SFML/Window/Event.hpp>

#include <functional>
#include <utility>
#include <list>

template <typename T = int>
class ActionTarget {
public:
    ActionTarget(const ActionTarget<T>&) = delete;
    ActionTarget<T>& operator=(ActionTarget<T>&) = delete;

    using FuncType = std::function<void(const sf::Event&)>;

    ActionTarget(const ActionMap<T>& map);

    // To process events from events poll
    bool processEvent(const sf::Event& event) const;
    // To process real time events
    void processEvents() const;

    void bind(const T& key, const FuncType& callback);
    void unbind(const T& key);

private:
    std::list<std::pair<T,FuncType>> _eventsRealTime;
    std::list<std::pair<T,FuncType>> _eventsPoll;

    const ActionMap<T>& _actionMap;

};

#include "ActionTarget.inl"