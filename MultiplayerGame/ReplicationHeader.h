#ifndef REPLICATION_HEADER_H
#define REPLICATION_HEADER_H

#include "TypeDef.h"
#include "Common.h"

enum ReplicationAction
{
	RA_Create,
	RA_Update,
	RA_Destroy,
	RA_MAX
};

class ReplicationHeader
{
public :
	ReplicationHeader()
	{
	}

	ReplicationHeader(ReplicationAction action, uint32 networkId, uint32 classId)
		:_action(action), _networkId(networkId), _classId(classId)
	{
	}

	void Write(OutputMemoryStream &stream);
	void Read(InputMemoryStream &stream);

	ReplicationAction _action;
	uint32 _networkId;
	uint32 _classId;

private :

};

#endif