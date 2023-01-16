#pragma once

namespace __DX12Engine
{
	class Device;
	class SwapChain;
	class CommandQueue;
	class RootSignature;
	class DescriptorHeap;

	class DX12Engine : public Singleton<DX12Engine>
	{
	private:
		friend class DX12Engine;

	public:
		void Init(const WindowInfo& info);

		void PreUpdate();

		void Update(float deltaTime);
		void LateUpdate(float deltaTime);

	public:
		shared_ptr<Device> GetDevice() { return _device; }
		shared_ptr<SwapChain> GetSwapChain() { return _swapChain; }
			
	private:
#ifdef __SHOW_FPS__
		void ShowFPS();
#endif

		WindowInfo  _info;

		WCHAR		_titleText[50];
		size_t		_titleLength;
		
	private:
		shared_ptr<Device>	_device;
		shared_ptr<SwapChain>	_swapChain;
	};
}

