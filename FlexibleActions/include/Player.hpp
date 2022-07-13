#pragma once

#include "ActionTarget.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>

class Player : public sf::Drawable, public ActionTarget<int>{

public:
    // Player must not be copyable
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    Player();
    
    void processEvents();
    
    // Key code binding    
    enum PlayerInputs 
    {
        Up, 
        Left, 
        Right
    };
    static void setDefaultsInput();

private:
    static ActionMap<int> _playerInputs;
};