#ifndef INPUT_MEMORY_STREAM_H
#define INPUT_MEMORY_STREAM_H

#include "MemoryStream.h"

class GameObject;
class LinkingContext;

class InputMemoryStream : public MemoryStream
{
public :
	InputMemoryStream(int8 *buffer, uint32 byteCount);
	~InputMemoryStream();

	virtual void Serialize(void *buffer, uint32 byteCount);
	virtual bool IsInput() { return true; }

	uint32 GetRemainingDataSize() const;
	void Read(void *buffer, int32 byteCount);

	//template <typename T>
	//void Read(T &data);

	template <typename T>
	void Read(std::vector<T> &vec);

	void Read(uint32 &data);
	void Read(int32 &data);
	void Read(GameObject &go);

private :
	int8 *_buffer;
	uint32 _head;
	uint32 _capacity;

	LinkingContext *_context;
};


template<typename T>
inline void InputMemoryStream::Read(std::vector<T>& vec)
{
	size_t elementCount;
	Read(elementCount);
	vec.resize(elementCount);
	for (T & data : vec)
	{
		Read(data);
	}
}

#endif
