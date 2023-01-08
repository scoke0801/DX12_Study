#pragma once

namespace __DX12Engine
{
	class Timer : public Singleton<Timer>
	{    
	private:
		friend class Singleton;
		Timer();

	public:
		void Start();
		void Update();
		void Stop();

		void Restart();
		void Reset();

		uint32 GetFPS() { return _fps; }
		float GetDeldatTime() { return _deltaTime; }

	private:
		// 경과 시간 계산용
		uint64	_frequency = 0;
		uint64	_prevCount = 0;
		float	_deltaTime = 0.f;

		// frame rate 계산용
		uint32	_frameCount = 0;
		float	_frameTime = 0.f;
		uint32	_fps = 0;

		bool	_stopped = false;
	};
}
