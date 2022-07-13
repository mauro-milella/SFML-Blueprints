#include "Player.hpp"

#include <SFML/Window/Event.hpp>

#include <math.h>

ActionMap<int> Player::_playerInputs;

Player::Player() :
ActionTarget(_playerInputs)
{
    // Key - Callback bindings
    // Default behaviour must be described in setDefaultsInput
    bind(PlayerInputs::Up, [this](const sf::Event&){
        // Insert callback here
    });

    bind(PlayerInputs::Left, [this](const sf::Event&){
        // Insert callback here
    });

    bind(PlayerInputs::Right, [this](const sf::Event&){
        // Insert callback here
    });
}

void Player::setDefaultsInput()
{
    _playerInputs.map(PlayerInputs::Up,     Action(sf::Keyboard::Up));
    _playerInputs.map(PlayerInputs::Right,  Action(sf::Keyboard::Right));
    _playerInputs.map(PlayerInputs::Left,   Action(sf::Keyboard::Left));
}