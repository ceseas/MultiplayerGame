#include "InputMemoryStream.h"


InputMemoryStream::InputMemoryStream(int8 *buffer, uint32 byteCount)
	:_buffer(buffer), _capacity(byteCount)
{
}

InputMemoryStream::~InputMemoryStream()
{
	std::free(_buffer);
}

void InputMemoryStream::Serialize(void * buffer, uint32 byteCount)
{
	Read(buffer, byteCount);
}

uint32 InputMemoryStream::GetRemainingDataSize() const
{
	return _capacity - _head;
}

void InputMemoryStream::Read(void * buffer, int32 byteCount)
{
	uint32 nextHead = _head + byteCount;
	if (nextHead > _capacity)
	{
		//error
		return;
	}
	std::memcpy(buffer, _buffer + _head, byteCount);
	_head = nextHead;
}

void InputMemoryStream::Read(uint32 & data)
{
	Read(&data, sizeof(data));
}

void InputMemoryStream::Read(int32 & data)
{
	Read(&data, sizeof(data));
}

//void InputMemoryStream::Read(GameObject & go)
//{
//	uint32 networkId;
//	Read(networkId);
//	go = *_context->GetGameObject(networkId);
//}
