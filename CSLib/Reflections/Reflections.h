#ifndef REFLECTIONS_H
#define REFLECTIONS_H

#include "../CommonInclude.h"

enum PrimitiveType
{
	PT_Int,
	PT_String,
	PT_Float,
	PT_Vector,
	PT_Map,
	PT_COUNT,
};


class MemberVariable
{
public :
	MemberVariable(const char *name, PrimitiveType type, uint32 offset);

	std::string GetName() { return _name; }
	PrimitiveType GetType() { return _type; }
	uint32 GetOffset() { return _offset; }

private :

	std::string _name;
	PrimitiveType _type;
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