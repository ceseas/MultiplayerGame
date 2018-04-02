#include "ReplicationHeader.h"

void ReplicationHeader::Write(OutputMemoryStream & stream)
{
	stream.Write(_action);
	stream.Write(_networkId);
	if (_action != RA_Destroy)
	{
		stream.Write(_classId);
	}
}

void ReplicationHeader::Read(InputMemoryStream & stream)
{
	uint32 action = 0;
	stream.Read(action);
	stream.Read(_networkId);

	_action = (ReplicationAction)(action);

	if (_action != RA_Destroy)
	{
		stream.Read(_classId);
	}
}
