#ifndef LINKING_CONTEXT_H
#define LINKING_CONTEXT_H


#include <unordered_map>
#include "TypeDef.h"

class GameObject;

class LinkingContext
{
public :
	LinkingContext();

	uint32 GetNetworkId(GameObject *go, bool shouldCreateIfNotFound);

	uint32 GetNetworkId(GameObject *go);
	GameObject *GetGameObject(uint32 networkId);

	void AddGameObject(GameObject *go, uint32 networkId);
	void RemoveGameobject(GameObject *go);

private :
	uint32 _nextNetworkId;

	std::unordered_map<uint32, GameObject *> _networkIdToGameObjectMap;
	std::unordered_map<GameObject *, uint32> _gameObjectToNetworkIdMap;
};


#endif