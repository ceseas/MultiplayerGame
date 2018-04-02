#ifndef REPLICATION_MANAGER_H
#define REPLICATION_MANAGER_H

#include "Common.h"
#include "ReplicationHeader.h"

#include <unordered_set>

class ReplicationManager
{
public :
	void ReplicationWorldState(OutputMemoryStream &stream, const std::vector<GameObject *> &objects);

	void ReceiveWorld(InputMemoryStream &stream);

	void ReplicateCreate(OutputMemoryStream &stream, GameObject *go);
	void ReplicateUpdate(OutputMemoryStream &stream, GameObject *go);
	void ReplicateDestroy(OutputMemoryStream &stream, GameObject *go);

	void ProcessReplicationAction(InputMemoryStream &stream);

private :
	void ReplicateIntoStream(OutputMemoryStream &stream, GameObject *go);

	GameObject *ReceiveReplicatedObject(InputMemoryStream &stream);

	LinkingContext *_context;
	std::unordered_set<GameObject *> _objectsReplicatedToMe;
};


#endif