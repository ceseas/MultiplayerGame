#ifndef REFLECTIONS_H
#define REFLECTIONS_H

#include "Common.h"

enum EPrimitiveType
{
	EPT_Int,
	EPT_String,
	EPT_Float,
};


class MemberVariable
{
public :
	MemberVariable(const char *name, EPrimitiveType type, uint32 offset);

	std::string GetName() { return _name; }
	EPrimitiveType GetType() { return _type; }
	uint32 GetOffset() { return _offset; }

private :

	std::string _name;
	EPrimitiveType _type;
	uint32 _offset;
};

class DataType
{
public :
	DataType(std::initializer_list<MemberVariable> variables);

	const std::vector<MemberVariable> GetMembers() const { return _members; }

private :
	std::vector<MemberVariable> _members;

};



#endif