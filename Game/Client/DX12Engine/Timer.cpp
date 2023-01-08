#include "pch.h"
#include "Timer.h"

__DX12Engine::Timer::Timer()
{ 
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&_frequency));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount));

	Start();
}

void __DX12Engine::Timer::Start()
{ 
	_deltaTime = 0.f;

	_frameCount = 0;
	_frameTime = 0.f;
	_fps = 0;	

	_frameCount = 0;
	_frameTime = 0.f;
	_fps = 0;

	_stopped = false;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount));
}

void __DX12Engine::Timer::Update()
{
	if (_stopped) { return; }

	uint64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

	_deltaTime = (currentCount - _prevCount) / static_cast<float>(_frequency);
	_prevCount = currentCount;

	_frameCount++;
	_frameTime += _deltaTime; 
	if (_frameTime > 1.f)
	{
		_fps = static_cast<uint32>(_frameCount / _frameTime);

		_frameTime = 0.f;
		_frameCount = 0;
	}
}

void __DX12Engine::Timer::Stop()
{
	_stopped = true;
}

void __DX12Engine::Timer::Restart()
{ 
	Start();
}

void __DX12Engine::Timer::Reset()
{
	Start();
} 