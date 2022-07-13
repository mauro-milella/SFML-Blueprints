#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Animation.hpp"
#include "AnimatedSprite.hpp"

int main(void) 
{
    sf::RenderWindow window(sf::VideoMode(600,800),"Example animation");

    //load of the texture image
    sf::Texture monster;
    monster.loadFromFile("assets/eye.png");

    //Creation of the different animations
    Animation walkLeft(&monster);
    walkLeft.addFramesLine(4,2,0);

    Animation walkRight(&monster);
    walkRight.addFramesLine(4,2,1);

    //Creation of the animates sprite
    AnimatedSprite sprite(&walkLeft,AnimatedSprite::Playing,sf::seconds(0.1));
    
    //game loop
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time delta = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) //close event
            window.close();
        }
        float speed = 50; // the movement speed of the entity
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) //move left
        {
            sprite.setAnimation(&walkLeft);
            sprite.play();
            sprite.move(-speed*delta.asSeconds(),0);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        //move right 
        {
            sprite.setAnimation(&walkRight);
            sprite.play();
            sprite.move(speed*delta.asSeconds(),0);
        }

        window.clear();
        sprite.update(delta); //update the animate sprite for possible frame change
        window.draw(sprite); //display the animation
        window.display();
    }

    return 0;
}