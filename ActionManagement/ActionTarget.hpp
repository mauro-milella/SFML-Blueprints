#pragma once

#include "Action.hpp"

#include <SFML/Window/Event.hpp>

#include <functional>
#include <list>

class ActionTarget {

public:
    using FuncType = std::function<void(const sf::Event&)>;

public:
    ActionTarget();

    // To process events from events poll
    bool processEvent(const sf::Event& event) const;
    // To process real time events
    void processEvents() const;

    void bind(const Action& action, const FuncType& callback);
    void unbind(const Action& action);

private:
    std::list<std::pair<Action,FuncType>> _eventsRealTime;
    std::list<std::pair<Action,FuncType>> _eventsPoll;

};