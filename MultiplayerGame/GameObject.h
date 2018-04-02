#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Common.h"

#define CLASS_IDENTIFICATION(Code, Class) \
	enum {EClassId = Code}; \
	virtual uint32 GetClassId() const {return EClassId;} \
	static Class *CreateInstance() {return new Class();}

class GameObject
{
public:
	virtual ~GameObject()
	{
	}

	virtual void Update()
	{
	}

	virtual void Write(OutputMemoryStream &stream)
	{
	}

	virtual void Read(InputMemoryStream &stream)
	{
	}

	virtual void Destroy()
	{
	}

	CLASS_IDENTIFICATION('GOBJ', GameObject)

private :

};

#endif