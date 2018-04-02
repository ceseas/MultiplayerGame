#ifndef MEMORY_STREAM_H
#define MEMORY_STREAM_H

#include "../CommonInclude.h"

#define STREAM_ENDIANESS 0
#define PLATFORM_ENDIANNESS 0

class MemoryStream
{
public :
	virtual ~MemoryStream()
	{
	}

	virtual void Serialize(void *data, uint32 byteCount) = 0;

	virtual bool IsInput() const = 0;

	template <typename T>
	void Serialize(T &data)
	{
		static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value,
			"Generic Serialize only supports primitive data types");
		if (STREAM_ENDIANNESS == PLATFORM_ENDIANNESS)
		{
			Serialize(&data, sizeof(T));
		}
		else
		{
			if (IsInput())
			{
				T data;
				Serialize(&data, sizeof(T));
				data = ByteSwap(data);
			}
			else
			{
				T swappedData = ByteSwap(data);
				Serialize(&swappedData, sizeof(T));
			}
		}
	}

};

#endif