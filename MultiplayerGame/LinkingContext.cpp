#include "LinkingContext.h"

LinkingContext::LinkingContext()
	:_nextNetworkId(1)
{
}

uint32 LinkingContext::GetNetworkId(GameObject * go, bool shouldCreateIfNotFound)
{
	auto find = _gameObjectToNetworkIdMap.find(go);
	if (find != _gameObjectToNetworkIdMap.end())
	{
		return find->second;
	}
	else if(shouldCreateIfNotFound)
	{
		uint32 networkId = _nextNetworkId++;
		AddGameObject(go, networkId);
		return networkId;
	}
	else
	{
		return 0;
	}
}

void LinkingContext::AddGameObject(GameObject * go, uint32 networkId)
{
	_networkIdToGameObjectMap[networkId] = go;
	_gameObjectToNetworkIdMap[go] = networkId;
}

void LinkingContext::RemoveGameobject(GameObject * go)
{
	uint32 networkId = GetNetworkId(go);
	_networkIdToGameObjectMap.erase(networkId);
	_gameObjectToNetworkIdMap.erase(go);
}

uint32 LinkingContext::GetNetworkId(GameObject * go)
{
	auto find = _gameObjectToNetworkIdMap.find(go);
	if (find != _gameObjectToNetworkIdMap.end())
	{
		return find->second;
	}
	else
	{
		return 0;
	}
}

GameObject * LinkingContext::GetGameObject(uint32 networkId)
{
	auto find = _networkIdToGameObjectMap.find(networkId);
	if (find != _networkIdToGameObjectMap.end())
	{
		return find->second;
	}
	else
	{
		return nullptr;
	}
}

