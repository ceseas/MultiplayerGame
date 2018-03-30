#ifndef OUTPUT_MEMORY_STREAM_H
#define OUTPUT_MEMORY_STREAM_H

#include "MemoryStream.h"
class GameObject;
class LinkingContext;

class OutputMemoryStream : public MemoryStream
{
public :
	OutputMemoryStream();
	~OutputMemoryStream();

	virtual void Serialize(void *data, uint32 byteCount);
	virtual bool IsInput() { return false; }

	void Write(const void *data, size_t byteCount);

	template <typename T>
	void Write(const T &data);

	template <typename T>
	void Write(const std::vector<T> &vec);

	void Write(uint32 data);
	void Write(int32 data);
	void Write(const GameObject *go);

	const int8 *GetBufferPtr() const { return _buffer; }
	uint32 GetLength() const { return _capacity; }

private :

	void ReallocateBuffer(uint32 length);

	int8 *_buffer;
	uint32 _head;
	uint32 _capacity;

	LinkingContext *_context;
};

template<typename T>
inline void OutputMemoryStream::Write(const T & data)
{
	static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value, 
		"Generic Write only supports primitive data types");
	Write(&data, sizeof(data));
}

template<typename T>
inline void OutputMemoryStream::Write(const std::vector<T>& vec)
{
	size_t elementCount = vec.size();
	Write(elementCount);

	for (const T &data : vec)
	{
		Write<T>(data);
	}
}

#endif
