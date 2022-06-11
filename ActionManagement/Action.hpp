#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

class Action {

public:
    enum Type
    {
        RealTime    = 1,
        Pressed     = 1<<1,
        Released    = 1<<2
    };
    
public:
    Action();

    // Copy constructor and copy operator
    Action(const Action& other);
    Action& operator=(const Action& other);

    // One constructor for each type of handled event
    Action(const sf::Keyboard::Key& key,    int type=Type::RealTime|Type::Pressed);
    Action(const sf::Mouse::Button& button, int type=Type::RealTime|Type::Pressed);

    // Test whether the event is satisfied in real time
    bool test() const;

    // Comparison operator
    bool operator==(const sf::Event& event) const;
    bool operator==(const Action& other)    const;

private:
    friend class ActionTarget;
    sf::Event _event;
    int _type;

};