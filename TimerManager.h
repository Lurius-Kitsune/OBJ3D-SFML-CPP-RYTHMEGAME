#pragma once
#include "Singleton.h"
#include "GameManager.h" 

using Seconds = float;
using MilliSec = int32_t;
using MicroSec = int64_t;

template <typename DurationType>
class Timer;

template <typename DurationType = Seconds>
class TimerManager : public Singleton<TimerManager<DurationType>>
{
	using T = Timer<DurationType>;
	friend T;

	// Objet qui contient toutes les données de temps
	Clock clock;
	// Temps depuis le début du programme
	DurationType time;
	// Stocke temporairement la précédente durée de la frame
	DurationType lastTime;
	// Mettre à jour le compteur de FPS
	DurationType lastFrameTime;
	// Temps depuis la dernière image rendue
	DurationType elapsedTime;
	// Temps depuis la dernière image rendue avec le 'timeScale'
	DurationType deltaTime;
	// Vitesse à laquelle le temps s'écoule
	float timeScale;
	// Nombre d'images qui ont été rendu depuis le début du programme
	l_long framesCount;
	// Maximum d'images à rendre par seconde
	u_short maxFrameRate;
	// Collection de tous les timers existants
	set<T*> allTimers;

	map<type_index, DurationType> durations;

private:
	FORCEINLINE DurationType GetDuration() const
	{
		return durations.at(typeid(DurationType));
	}
	FORCEINLINE DurationType GetTime(const Time& _time) const
	{
		map<type_index, function<DurationType()>> _durationCallback =
		{
			{ typeid(Seconds),  [&]() { return _time.asSeconds(); }},
			{ typeid(MilliSec), [&]() { return _time.asMilliseconds(); }},
			{ typeid(MicroSec), [&]() { return _time.asMicroseconds(); }},
		};

		return _durationCallback.at(typeid(DurationType))();
	}
public:
	FORCEINLINE string GetCurrentRealTime() const
	{
		const time_t& _now = std::time(0);

		tm _ltm;
		localtime_s(&_ltm, &_now);

		const string& _date = to_string(_ltm.tm_mday) + "/" + to_string(1 + _ltm.tm_mon) + "/" + to_string(1900 + _ltm.tm_year);
		const string& _time = to_string(_ltm.tm_hour) + ":" + to_string(_ltm.tm_min) + ":" + to_string(_ltm.tm_sec);

		return _date + " " + _time;
	}
	FORCEINLINE void AddTimer(T* _timer)
	{
		allTimers.insert(_timer);
	}
	FORCEINLINE void RemoveTimer(T* _timer)
	{
		if (!allTimers.contains(_timer)) return;

		_timer->Stop();
		allTimers.erase(_timer);
		delete _timer;
	}
	FORCEINLINE void SetTimerScale(const DurationType& _timeScale)
	{
		timeScale = _timeScale;
	}
	FORCEINLINE DurationType ComputeFPS() const
	{
		return GetDuration() / (time - lastFrameTime);
	}
	FORCEINLINE Time GetDeltaTime() const
	{
		return Time(seconds(CAST(float, deltaTime * GetDuration())));
	}

public:
	TimerManager()
	{
		clock = Clock();
		time = DurationType();
		lastTime = DurationType();
		lastFrameTime = DurationType();
		elapsedTime = DurationType();
		deltaTime = DurationType();
		timeScale = 1.0f;
		framesCount = 0;
		maxFrameRate = 60;
		allTimers = set<T*>();
		durations =
		{
			{ typeid(Seconds), 1 },
			{ typeid(MilliSec), 1000 },
			{ typeid(MicroSec), 1000000 }
		};
	}
	~TimerManager()
	{
		for (T* _timer : allTimers)
		{
			delete _timer;
		}
	}

	void Update()
	{
		lastTime = time;
		time = GetTime(clock.getElapsedTime());
		elapsedTime = time - lastTime;
		deltaTime = elapsedTime * timeScale;
		framesCount++;

		if (lastFrameTime == 0 || time - lastFrameTime <= maxFrameRate)
		{
			lastFrameTime = time;
			framesCount = 0;
			M_GAME.GetCurrent()->UpdateWindow();
		}
		
		using Iterator = set<T*>::iterator;
		for (Iterator _iterator = allTimers.begin(); _iterator != allTimers.end(); )
		{
			T* _timer = *_iterator;
			_timer->Update(deltaTime);

			if (_timer->IsToDelete())
			{
				--_iterator;
				RemoveTimer(_timer);
				continue;
			}

			++_iterator;
		}
	}
	void Pause()
	{
		for (Timer* _timer : allTimers)
		{
			_timer->Pause();
		}
	}
	void Resume()
	{
		for (T* _timer : allTimers)
		{
			_timer->Resume();
		}
	}
	void Stop()
	{
		for (T* _timer : allTimers)
		{
			_timer->Stop();
		}
	}
};

using TM_Seconds = TimerManager<Seconds>;
using TM_Milli = TimerManager<MilliSec>;
using TM_Micro = TimerManager<MicroSec>;

template <typename DurationType = Seconds>
class Timer
{
	using TM = TimerManager<DurationType>;

	bool isToDelete;
	bool isRunning;
	bool isLoop;
	DurationType currentTime;
	DurationType duration;
	function<void()> callback;

public:
	FORCEINLINE bool IsToDelete() const
	{
		return isToDelete;
	}
	FORCEINLINE bool IsRunning() const
	{
		return isRunning;
	}
	FORCEINLINE bool IsLoop() const
	{
		return isLoop;
	}
	FORCEINLINE DurationType GetCurrentTime() const
	{
		return currentTime;
	}

public:
	Timer(const function<void()>& _callback, const Time& _time, const bool _startRunning = false,
		const bool _isLoop = false)
	{
		TM& _manager = TM::GetInstance();

		isToDelete = false;
		isRunning = _startRunning;
		isLoop = _isLoop;
		currentTime = 0.0;
		duration = _manager.GetTime(_time);
		callback = _callback;

		_manager.AddTimer(this); //TODO check
	}
	Timer(const Timer& _other)
	{
		isToDelete = _other.isToDelete;
		isRunning = _other.isRunning;
		isLoop = _other.isLoop;
		currentTime = _other.currentTime;
		duration = _other.duration;
		callback = _other.callback;

		TM::GetInstance().AddTimer(this);
	}

public:
	void Start()
	{
		Reset();
		Resume();
	}
	void Update(const DurationType& _deltaTime)
	{
		if (!isRunning) return;

		currentTime += _deltaTime;

		if (currentTime >= duration)
		{
			if (callback)
			{
				callback();
			}

			if (!isLoop)
			{
				Stop();
			}

			Reset();
		}
	}
	void Stop()
	{
		Pause();
		isToDelete = true;
	}
	void Resume()
	{
		isRunning = true;
	}
	void Reset()
	{
		currentTime = DurationType();
	}
	void Pause()
	{
		isRunning = false;
	}
};