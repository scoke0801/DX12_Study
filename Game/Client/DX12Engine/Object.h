#pragma once

namespace __DX12Engine
{
	class Object
	{
	public:
		Object() {}
		virtual ~Object() {}
	
		void SetName(const wstring& name) { _name = name; }
		const wstring& GetName() { return _name; }

	public:
		virtual void Load(const wstring& path) {}
		virtual void Save(const wstring& path) {}

	private:
		wstring		_name;
	};
}

