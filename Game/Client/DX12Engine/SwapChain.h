#pragma once

namespace __DX12Engine
{
	class SwapChain
	{
	public:
		uint8 GetBackBufferIndex() { return _currentIndex; }

	private:
		uint8			_currentIndex;
	};
}

