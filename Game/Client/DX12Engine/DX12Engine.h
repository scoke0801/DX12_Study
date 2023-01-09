#pragma once

namespace __DX12Engine
{
	class DX12Engine
	{
	public:
		void Init(const WindowInfo& info);

		void PreUpdate();

		void Update(float deltaTime);
		void LateUpdate(float deltaTime);

	private:
#ifdef __SHOW_FPS__
		void ShowFPS();
#endif

		WindowInfo  _info;

		WCHAR		_titleText[50];
		size_t		_titleLength;

	private:
		shared_ptr<class Device> _device;
	};
}

