#include "Reflections.h"

MemberVariable::MemberVariable(const char * name, EPrimitiveType type, uint32 offset)
	:_name(name), _type(type), _offset(offset)
{
}

DataType::DataType(std::initializer_list<MemberVariable> variables)
	:_members(variables)
{
}
