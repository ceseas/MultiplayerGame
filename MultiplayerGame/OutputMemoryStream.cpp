#include "OutputMemoryStream.h"

#include "Common.h"

OutputMemoryStream::OutputMemoryStream()
	:_buffer(nullptr), _head(0), _capacity(0), _context(nullptr)
{
	ReallocateBuffer(32);
}

OutputMemoryStream::~OutputMemoryStream()
{
	std::free(_buffer);
}

void OutputMemoryStream::Serialize(void * data, uint32 byteCount)
{
	Write(data, byteCount);
}

void OutputMemoryStream::Write(const void * data, size_t byteCount)
{
	uint32 nextHead = _head + static_cast<uint32>(byteCount);
	if (nextHead > _capacity)
	{
		ReallocateBuffer(max(_capacity * 2, nextHead ));
	}
	std::memcpy(_buffer + _head, data, byteCount);
	_head = nextHead;
}

void OutputMemoryStream::Write(uint32 data)
{
	Write(&data, sizeof(data));
}

void OutputMemoryStream::Write(int32 data)
{
	Write(&data, sizeof(data));
}

void OutputMemoryStream::Write(const GameObject * go)
{
	uint32 networkId = _context->GetNetworkId(const_cast<GameObject *>(go), false);
	Write(networkId);
}

void OutputMemoryStream::ReallocateBuffer(uint32 length)
{
	_buffer = static_cast<int8 *>(std::realloc(_buffer, length));
	_capacity = length;
}
