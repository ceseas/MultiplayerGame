#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Common.h"

class GameObject
{
public :

	virtual ~GameObject()
	{
	}

	virtual void Update() = 0;

private :

};

#endif