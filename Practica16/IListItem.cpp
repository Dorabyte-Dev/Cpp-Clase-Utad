#include "IListItem.h"
#include <cstring>
#include <cstdio>

StringItem::StringItem(const char* _value)
{
	if(_value)
	{
		unsigned int uLen = strlen(_value);
		value = new char[uLen + 1];
		strcpy_s(value, uLen + 1, _value);
	}
}

StringItem::~StringItem()
{
	delete[] value;
}

IListItem* StringItem::Clone() const
{
	IListItem* tClone = new StringItem(value);
	return tClone;
}

void StringItem::Print() const
{
	printf("String Item printing with value: %s\n", value);
}

IntItem::IntItem(int _value)
{
	value = _value;
}

IntItem::~IntItem()
{

}

IListItem* IntItem::Clone() const
{
	IListItem* tClone = new IntItem(value);
	return tClone;
}

void IntItem::Print() const
{
	printf("Int Item printing with value: %d\n", value);
}
