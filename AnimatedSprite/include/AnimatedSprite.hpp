#pragma once

#include <functional>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Time.hpp>

#include "Animation.hpp"

/*
    The main functionality of AnimatedSprite is to
    store an array of four vertices (see `vertices`)
    which represent a frame taken from an associated Animation.

    Also, this class contains informations such as the time
    between two frames and if the animation is a loop.
*/

class AnimatedSprite : public sf::Drawable, public sf::Transformable
{
public:
    AnimatedSprite(const AnimatedSprite&) = default;
    AnimatedSprite& operator=(const AnimatedSprite&) = default;
    AnimatedSprite(AnimatedSprite&&) = default;
    AnimatedSprite& operator=(AnimatedSprite&&) = default;

    using FuncType = std::function<void()>;
    static FuncType defaultFunc;
    FuncType onFinished;
    enum Status {Stopped, Paused, Playing};

    AnimatedSprite(
        Animation* animation = nullptr,
        Status status = Playing,
        const sf::Time& deltaTime = sf::seconds(0.15),
        bool loop = true, int repeat = 0
    );

    void setAnimation(Animation* animation);
    Animation* getAnimation() const;

    void setFrameTime(sf::Time deltaTime);
    sf::Time getFrameTime() const;

    void setLoop(bool loop);
    bool getLoop() const;

    void setRepeat(int repetitions);
    int  getRepeat() const;

    void play();
    void pause();
    void stop();
    Status getStatus() const;

    void setFrame(size_t index);
    void setColor(const sf::Color& color);
    void update(const sf::Time& deltaTime);

private:
    Animation* _animation;
    
    sf::Time _frameTime;
    sf::Time _elapsedTime;

    bool _loop;
    int _repeat;

    Status _status;
    size_t _currentFrame;
    sf::Vertex _vertices[4];

    void setFrame(size_t index, bool resetTime);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};