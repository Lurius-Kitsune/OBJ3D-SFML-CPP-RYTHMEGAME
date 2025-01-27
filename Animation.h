#pragma once
#include "CoreMinimal.h"
#include "ShapeObject.h"
#include "TimerManager.h"

enum ReadDirection
{
    RD_ROW ,
    RD_ROW_REVERSE,
    RD_COLUMN,
    RD_COLUMN_REVERSE,
};

struct SpriteData
{
    float timeBetween;
    Vector2i start;
    Vector2i size;
};

struct LinkedAnimation
{
    function<bool()> transition;
    class Animation* animation;

    FORCEINLINE bool IsValid() const
    {
        return !transition || transition();
    }

    bool TryToChange();
};

struct AnimationData
{
    bool canLoop;
    bool hasExitTime;
    bool isReversed;
    int count;
    float duration;
    vector<SpriteData> sprites;
    map<u_int, function<void()>> notifies;
    ReadDirection direction;
    vector<LinkedAnimation> linkedAnimations;

    AnimationData() = default;
    AnimationData(const int _count, const float _duration, const SpriteData& _spriteData,
                  const bool _hasExitTime = true, const bool _canLoop = true,
                  const ReadDirection& _direction = RD_ROW, const bool _isReversed = false,
                  const vector<LinkedAnimation>& _linkedAnimations = {})
    {
        canLoop = _canLoop;
        hasExitTime = _hasExitTime;
        isReversed = _isReversed;
        count = _count;
        duration = _duration;
        direction = _direction;

        const function<Vector2i(const int _index)> _computeStart[] =
        {
            [&](const int _index)
            {
                return Vector2i
                {
                    _spriteData.start.x + _index * _spriteData.size.x,
                    _spriteData.start.y
                };
            },

            [&](const int _index)
            {
                return Vector2i
                {
                    _spriteData.start.x - _index * _spriteData.size.x,
                    _spriteData.start.y
                };
            },

            [&](const int _index)
            {
                return Vector2i
                {
                    _spriteData.start.x,
                    _spriteData.start.y + _index * _spriteData.size.y
                };
            },

            [&](const int _index)
            {
                return Vector2i
                {
                    _spriteData.start.x,
                    _spriteData.start.y - _index * _spriteData.size.y
                };
            }
        };

        for (int _index = 0; _index < _count; _index++)
        {
            const SpriteData& _data = { _spriteData.timeBetween, _computeStart[direction](_index), _spriteData.size};
            sprites.push_back(_data);
        }
    }
    AnimationData(const float _duration, const vector<SpriteData>& _spritesData,
                  const bool _hasExitTime = true, const bool _canLoop = true,
                  const ReadDirection& _direction = RD_ROW, const bool _isReversed = false,
                  const vector<LinkedAnimation>& _linkedAnimations = {})
    {
        canLoop = _canLoop;
        hasExitTime = _hasExitTime;
        isReversed = _isReversed;
        count = CAST(int, _spritesData.size());
        duration = _duration;
        sprites = _spritesData;
        direction = _direction;
        linkedAnimations = _linkedAnimations;
    }
};

class Animation
{
    int currentIndex;
    string name;
    AnimationData data;
    ShapeObject* shape;
    Timer<Seconds>* timer;

private:
    FORCEINLINE bool IsValidIndex() const
    {
        return currentIndex < data.count;
    }
public:
    FORCEINLINE string GetName() const
    {
        return name;
    }

public:
    Animation(const string& _name, ShapeObject* _shape, const AnimationData& _data);
    Animation(const Animation& _other);
    ~Animation();

private:
    void Update();
    void Reset();

public:
    void Start();
    void Resume();
    void Pause();
    void Stop();
};