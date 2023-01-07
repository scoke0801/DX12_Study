#pragma once

template<typename T>
inline shared_ptr<T> Resources::Load(const wstring& key, const wstring& path)
{
	OBJECT_TYPE objectType = GetObjectType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(objectType)];

	// �̹� �����ϴ� ��ü�� ����� ��ȯ
	auto res = keyObjMap.find(key);
	if (res != keyObjMap.end()) {
		return static_pointer_cast<T>(res->second);
	}
	
	// TODO : Loadó���� ����
	// ������ ���� �����Ͽ� ��� �� ��ȯ.
	shared_ptr<T> object = make_shared<T>();
	object->Load(path);
	keyObjMap[key] = object;

	return object;
}

template<typename T>
bool Resources::Add(const wstring& key, shared_ptr<T> object)
{
	OBJECT_TYPE objectType = GetObjectType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(objectType)];
	 
	auto res = keyObjMap.find(key);
	if (res != keyObjMap.end()) {
		return false;
	}
	 
	keyObjMap[key] = object;
	return true;
}

template<typename T>
shared_ptr<T> Resources::Get(const wstring& key)
{
	OBJECT_TYPE objectType = GetObjectType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(objectType)];
	 
	auto res = keyObjMap.find(key);
	if (res != keyObjMap.end()) {
		return static_pointer_cast<T>(res->second);
	}

	return nullptr;
}

template<typename T>
OBJECT_TYPE Resources::GetObjectType()
{
	// is_same ~ C++11
	// is_same_v ~ C++17

	if (std::is_same<T, GameObject>::value)
	{
		return OBJECT_TYPE::GAMEOBJECT;
	}
	else if (std::is_same<T, Material>::value)
	{
		return OBJECT_TYPE::MATERIAL;
	}
	else if (std::is_same<T, Mesh>::value)
	{
		return OBJECT_TYPE::MESH;
	}
	else if (std::is_same < T, Shader>::value)
	{
		return OBJECT_TYPE::SHADER;
	}
	else if (std::is_same<T, Texture>::value)
	{
		return OBJECT_TYPE::TEXTURE;
	}
	else if (std::is_same<T, Component>::value)
	{
		return OBJECT_TYPE::COMPONENT;
	}

	assert(true);
	return OBJECT_TYPE::NONE;
}