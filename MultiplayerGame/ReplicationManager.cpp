#include "ReplicationManager.h"

#include "GameObject.h"

void ReplicationManager::ReplicationWorldState(OutputMemoryStream & stream, 
											   const std::vector<GameObject*>& objects)
{
	stream.Write(PT_ReplicationData);
	for (GameObject *go : objects)
	{
		ReplicateIntoStream(stream, go);
	}
}

void ReplicationManager::ReceiveWorld(InputMemoryStream & stream)
{
	std::unordered_set<GameObject *> receivedObjects;
	while (stream.GetRemainingDataSize() > 0)
	{
		GameObject *receivedObject = ReceiveReplicatedObject(stream);
		receivedObjects.insert(receivedObject);
	}

	for (GameObject *go : _objectsReplicatedToMe)
	{
		if (receivedObjects.find(go) == receivedObjects.end())
		{
			_context->RemoveGameobject(go);
			go->Destroy();
		}
	}
	_objectsReplicatedToMe = receivedObjects;
}

void ReplicationManager::ReplicateCreate(OutputMemoryStream & stream, GameObject * go)
{
	ReplicationHeader header(RA_Create, _context->GetNetworkId(go, true), go->GetClassId());
	header.Write(stream);
	go->Write(stream);
}

void ReplicationManager::ReplicateUpdate(OutputMemoryStream & stream, GameObject * go)
{
	ReplicationHeader header(RA_Update, _context->GetNetworkId(go, false), go->GetClassId());
	header.Write(stream);
	go->Write(stream);
}

void ReplicationManager::ReplicateDestroy(OutputMemoryStream & stream, GameObject * go)
{
	ReplicationHeader header(RA_Destroy, _context->GetNetworkId(go, false), go->GetClassId());
	header.Write(stream);
	go->Write(stream);
}

void ReplicationManager::ProcessReplicationAction(InputMemoryStream & stream)
{
}

void ReplicationManager::ReplicateIntoStream(OutputMemoryStream & stream, 
											 GameObject * go)
{
	stream.Write(_context->GetNetworkId(go, true));
	stream.Write(go->GetClassId());
	go->Write(stream);
}

GameObject * ReplicationManager::ReceiveReplicatedObject(InputMemoryStream & stream)
{
	uint32 networkId = 0;
	uint32 classId = 0;
	stream.Read(networkId);
	stream.Read(classId);

	GameObject *go = _context->GetGameObject(networkId);

	if (go == nullptr)
	{
		go = ObjectCreationRegistry::Get().CreateGameObject(classId);
		_context->AddGameObject(go, networkId);
	}
	go->Read(stream);

	return go;
}
