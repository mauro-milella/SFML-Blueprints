#include <cassert>
#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite (
    Animation* animation,
    Status status,
    const sf::Time& frameTime,
    bool loop, int repeat
)
: _frameTime(frameTime)
, _loop(loop)
, _repeat(repeat)
, _status(status)
{
    setAnimation(animation);
}

void AnimatedSprite::setAnimation(Animation* animation)
{
    if (_animation != animation)
    {
        _animation = animation;
        _elapsedTime = sf::Time::Zero;
        _currentFrame = 0;
        setFrame(0, true);
    }
}

Animation* AnimatedSprite::getAnimation() const { return _animation; }

void AnimatedSprite::setFrameTime(sf::Time deltaTime) { _frameTime = deltaTime; }
sf::Time AnimatedSprite::getFrameTime() const         { return _frameTime;      }

void AnimatedSprite::setLoop(bool loop) { _loop = loop; }
bool AnimatedSprite::getLoop() const    { return _loop; }

void AnimatedSprite::setRepeat(int repetitions)  { _repeat = repetitions;    }
int  AnimatedSprite::getRepeat() const { return _repeat; }

void AnimatedSprite::play()  
{ 
    _status = Playing; 
}

void AnimatedSprite::pause() 
{ 
    _status = Paused;  
}

void AnimatedSprite::stop()  
{ 
    _status = Stopped; 
    _currentFrame = 0;
    setFrame(0, true);
}

AnimatedSprite::Status AnimatedSprite::getStatus() const { return _status; }

void AnimatedSprite::setFrame(size_t index)
{
    assert(_animation);
    _currentFrame = index % _animation->size();
    setFrame(_currentFrame, true);
}

// Change displayed image's color mask
void AnimatedSprite::setColor(const sf::Color& color)
{
    for (auto& v : _vertices) 
        v.color = color;
}

void AnimatedSprite::update(const sf::Time& deltaTime)
{
    if (_status == Playing && _animation)
    {
        _elapsedTime += deltaTime;

        if (_elapsedTime > _frameTime)
        {
            // Frame has to be changed
            _elapsedTime -= _frameTime;
            if (_currentFrame +1 < _animation->size())
                ++_currentFrame;
            else
            {
                // End of frame list reached
                _currentFrame = 0;

                if (!_loop)
                {
                    // Is another reptition possible=
                    --_repeat;
                    if (_repeat < 0)
                    {
                        // No
                        _status = Stopped;
                        onFinished();
                    }
                }
            }
        }
        // Update the frame
        setFrame(_currentFrame, false);
    }
}

// Update vertices attributes depending on Animation object internal state 
void AnimatedSprite::setFrame(size_t index, bool resetTime)
{
    if (_animation)
    {
        sf::IntRect rect = _animation->getRect(index);
        // Update vertice position
        _vertices[0].position = sf::Vector2f(0.f, 0.f);
        _vertices[1].position = sf::Vector2f(0.f, static_cast<float>(rect.height));
        _vertices[2].position = sf::Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height));
        _vertices[3].position = sf::Vector2f(static_cast<float>(rect.width), 0.f);

        // Compute the texture coords
        float left = static_cast<float>(rect.left);
        float right = left + static_cast<float>(rect.width);
        float top = static_cast<float>(rect.top);
        float bottom = top + static_cast<float>(rect.height);

        // Set the texture coords
        _vertices[0].texCoords = sf::Vector2f(left, top);
        _vertices[1].texCoords = sf::Vector2f(left, bottom);
        _vertices[2].texCoords = sf::Vector2f(right, bottom);
        _vertices[3].texCoords = sf::Vector2f(right, top);
    }

    if (resetTime)
        _elapsedTime = sf::Time::Zero;
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (_animation && _animation->_texture)
    {
        states.transform *= getTransform();
        states.texture = _animation->_texture;
        target.draw(_vertices, 4, sf::Quads, states);
    }
}
