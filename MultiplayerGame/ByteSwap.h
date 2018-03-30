#ifndef BYTE_SWAP_H
#define BYTE_SWAP_H

#include "TypeDef.h"

inline uint16 ByteSwap2(uint16 data)
{
	return (uint16)(data >> 8 | data << 8);
}

inline uint32 ByteSwap4(uint32 data)
{
	return (uint32)((data >> 24) & 0x000000ff |
					(data >> 8)  & 0x0000ff00 |
					(data << 8)  & 0x00ff0000 |
					(data << 24) & 0xff000000);
}

inline uint64 ByteSwap8(uint64 data)
{
	return (uint64)((data >> 56) & 0x00000000000000ff |
					(data >> 40) & 0x000000000000ff00 |
					(data >> 24) & 0x0000000000ff0000 |
					(data >> 8)  & 0x00000000ff000000 |
					(data << 8)  & 0x000000ff00000000 |
					(data << 24) & 0x0000ff0000000000 |
					(data << 40) & 0x00ff000000000000 |
					(data << 56) & 0xff00000000000000);
}

template <typename tFrom, typename tTo>
class TypeAliaser
{
public :
	TypeAliaser(tFrom fromValue)
		:fromType(fromValue)
	{
	}
	tTo &Get() 
	{
		return _toType
	}
	union
	{
		tFrom _fromType;
		tTo _toType;
	};
};

template <typename T, size_t tSize> class ByteSwapper;

template <typename T>
class ByteSwapper<T, 2>
{
public :
	T Swap(T data) const
	{
		uint16 result = ByteSwap2(TypeAliaser<T, uint16>(data).Get());
		return TypeAliaser<uint16, T>(result).Get();
	}
};

template <typename T>
class ByteSwapper<T, 4>
{
public :
	T Swap(T data) const
	{
		uint32 result = ByteSwap4(TypeAliaser<T, uint32>(data).Get());
		return TypeAliaser<uint32, T>(result).Get();
	}
};

template <typename T>
class ByteSwapper<T, 8>
{
public :
	T Swap(T data) const
	{
		uint64 result = ByteSwap8(TypeAliaser<T, uint64>(data).Get());
		return TypeAliaser<uint64, T>(result).Get();
	}
};

template <typename T>
T ByteSwap(T data)
{
	return ByteSwapper<T, sizeof(T)>().Swap(data);
}

#endif