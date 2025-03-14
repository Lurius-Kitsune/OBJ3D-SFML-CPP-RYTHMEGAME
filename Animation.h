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
    Vector2i start;
    Vector2i size;
    float factor;

    SpriteData(const Vector2i& _start, const Vector2i& _size, const float _factor = 1.0f)
    {
        start = _start;
        size = _size;
        factor = _factor;
    }
};

struct LinkedAnimation
{
    function<bool()> transition;
    class Animation* animation;

    FORCEINLINE bool IsValid() const
    {
        return !transition || transition();
    }
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
                  const ReadDirection& _direction = RD_ROW, const bool _isReversed = false)
    {
        canLoop = _canLoop;
        hasExitTime = _hasExitTime;
        isReversed = _isReversed;
        count = _count;
        duration = _duration;
        notifies = map<u_int, function<void()>>();
        linkedAnimations = vector<LinkedAnimation>();

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
            const SpriteData& _data = SpriteData(_computeStart[_direction](_index), _spriteData.size, _spriteData.factor);
            sprites.push_back(_data);
        }
    }

    AnimationData(const float _duration, const vector<SpriteData>& _spritesData,
                  const bool _hasExitTime = true, const bool _canLoop = true,
                  const bool _isReversed = false)
    {
        canLoop = _canLoop;
        hasExitTime = _hasExitTime;
        isReversed = _isReversed;
        count = CAST(int, _spritesData.size());
        duration = _duration;
        sprites = _spritesData;
        notifies = map<u_int, function<void()>>();
        linkedAnimations = vector<LinkedAnimation>();
    }
};

class Animation
{
    int currentIndex;
    string name;
    AnimationData data;
    ShapeObject* shape;
    Timer<Seconds>* timer;
    function<void()> onAnimationEnded;

private:
    FORCEINLINE bool IsValidIndex() const
    {
        return currentIndex < data.count;
    }
    FORCEINLINE float ComputeDuration()
    {
        return ComputeDuration(*GetSpriteData());
    }
    FORCEINLINE float ComputeDuration(const SpriteData& _spriteData) const
    {
        return data.duration / data.count * _spriteData.factor;
    }
    FORCEINLINE SpriteData* GetSpriteData()
    {
        if (data.sprites.empty()) return nullptr;

        const int _index = currentIndex == 0 ? 0 : currentIndex - 1;
        return &data.sprites[_index];
    }
    
public:
    FORCEINLINE void AddLinkedAnimation(const function<bool()>& _transition, Animation* animation)
    {
        const LinkedAnimation& _linkedAnim = LinkedAnimation(_transition, animation);
        data.linkedAnimations.push_back(_linkedAnim);
    }
    FORCEINLINE string GetName() const
    {
        return name;
    }
    FORCEINLINE function<void()>& GetOnAnimationEnded()
    {
        return onAnimationEnded;
    }
    FORCEINLINE Animation* GetNextAnimation() const
    {
        for (const LinkedAnimation& _linkedAnim : data.linkedAnimations)
        {
            if (_linkedAnim.IsValid()) return _linkedAnim.animation;
        }

        return nullptr;
    }

public:
    Animation(const string& _name, ShapeObject* _shape, const AnimationData& _data);
    Animation(const Animation& _other);
    ~Animation();

private:
    void Update();
    void UpdateTimer(const SpriteData& _spriteData);
    void Reset();

public:
    void Start();
    void Resume();
    void Pause();
    void Stop();
};