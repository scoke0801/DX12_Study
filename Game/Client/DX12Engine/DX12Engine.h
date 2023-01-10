#pragma once

namespace __DX12Engine
{
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
		shared_ptr<class Device> GetDevice() { return _device; }
		shared_ptr<class SwapChain> GetSwapChain() { return _swapChain; }
		shared_ptr<class CommandQueue> GetCommandQueue(CommandQueueType type) { return _cmdLists[static_cast<uint8>(type)]; }
		shared_ptr<class RootSignature> GetRootSignature(RootSignatureType type) { return _rootSignatures[static_cast<uint8>(type)]; }

	private:
#ifdef __SHOW_FPS__
		void ShowFPS();
#endif

		WindowInfo  _info;

		WCHAR		_titleText[50];
		size_t		_titleLength;

	private:
		shared_ptr<class Device>	_device;
		shared_ptr<class SwapChain>	_swapChain;
		array< shared_ptr<class CommandQueue>, COMMAND_LIST_COUNT >		_cmdLists;
		array< shared_ptr<class RootSignature>, ROOT_SIGNATURE_COUNT >	_rootSignatures;
	};
}

