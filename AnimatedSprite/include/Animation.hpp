#pragma once

#include <vector>
#include <SFML/Graphics/Texture.hpp>

class AnimatedSprite;

class Animation 
{
public:
    Animation(sf::Texture* texture = nullptr);
    ~Animation();

    void setTexture(sf::Texture* texture);
    sf::Texture* getTexture() const;

    Animation& addFrame(const sf::IntRect& rect);
    Animation& addFramesLine(int numberX, int numberY, int line);
    Animation& addFramesColumn(int numberX, int numberY, int column);

    size_t size() const;
    
    const sf::IntRect& getRect(size_t index) const;

private:
    friend class AnimatedSprite;
    std::vector<sf::IntRect> _frames;
    sf::Texture* _texture;
};