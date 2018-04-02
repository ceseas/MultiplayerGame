#ifndef OBJECT_CREATION_REGISTRY_H
#define OBJECT_CREATION_REGISTRY_H

#include "SingletonBase.h"
#include  "TypeDef.h"
#include <unordered_map>

class GameObject;

typedef GameObject *(*ObjectCreationFunction)();

class ObjectCreationRegistry : public SingletonBase<ObjectCreationRegistry>
{
public :

	template<class T>
	void RegisterCreationFunction()
	{
		if (_idToCreationFunctionMap.find(T::EClassId) == _idToCreationFunctionMap.end())
		{
			//ERROR
			return;
		}
		_idToCreationFunctionMap[T::EClassId] = T::CreateInstance;
	}

	GameObject *CreateGameObject(uint32 classId)
	{
		auto find = _idToCreationFunctionMap.find(classId);
		GameObject *go = find->second();
		return go;
	}

private :
	ObjectCreationRegistry()
	{
	}
	std::unordered_map<uint32, ObjectCreationFunction> _idToCreationFunctionMap;
};

#endif