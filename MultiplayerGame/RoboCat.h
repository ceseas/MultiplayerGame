#ifndef ROBO_CAT_H
#define ROBO_CAT_H

#include "GameObject.h"

class RoboCat : public GameObject
{
public :
	RoboCat() 
		:_health(10), _meowCount(3)
	{
	}

	virtual void Update();

	void Write(OutputMemoryStream &stream);
	void Read(InputMemoryStream &stream);

	static DataType *SDataType;
	static void InitDataType()
	{
		SDataType = new DataType(
		{
			MemberVariable("_health", EPT_Int, OFFSETOF(RoboCat, _health)),
			MemberVariable("_meowCount", EPT_Int, OFFSETOF(RoboCat, _meowCount)),
			MemberVariable("_name", EPT_String, OFFSETOF(RoboCat, _name))
		});
	}
	CLASS_IDENTIFICATION('ROCT', RoboCat)

private :

	int32 _health;
	int32 _meowCount;
	//GameObject *_homeBase;
	char _name[128] = {0, };
	//std::vector<int32> _miceIndices;
};

#endif