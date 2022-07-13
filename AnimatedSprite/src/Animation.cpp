#include "Animation.hpp"

Animation::Animation(sf::Texture* texture)
: _texture(texture)
{}

Animation::~Animation()
{}

void Animation::setTexture(sf::Texture* texture)
{
    _texture = texture;
}

sf::Texture* Animation::getTexture() const
{
    return _texture;
}

Animation& Animation::addFrame(const sf::IntRect& rect)
{
    _frames.emplace_back(rect);
    return *this;
}

Animation& Animation::addFramesLine(int numberX, int numberY, int line)
{
    const sf::Vector2u size = _texture->getSize();
    const float deltaX = size.x / float(numberX);
    const float deltaY = size.y / float(numberY);

    for(int i=0; i<numberX; ++i)
        addFrame(sf::IntRect(i*deltaX, line*deltaY, deltaX, deltaY));
    return *this;
}

Animation& Animation::addFramesColumn(int numberX, int numberY, int column)
{
    const sf::Vector2u size = _texture->getSize();
    float deltaX = (float)size.x / numberX;
    float deltaY = (float)size.y / numberY;

    for(int j=0; j<numberY; ++j)
        addFrame(sf::IntRect(column*deltaX, j*deltaY, deltaX, deltaY));
    return *this;
}

size_t Animation::size() const
{
    return _frames.size();
}

const sf::IntRect& Animation::getRect(size_t index) const
{
    return _frames[index];
}