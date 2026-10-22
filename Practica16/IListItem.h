#pragma once
class IListItem
{
public:
	IListItem* m_pNext = nullptr;
	virtual ~IListItem() {}
	virtual IListItem* Clone() const = 0;
	virtual void Print() const = 0;
};

class StringItem : public IListItem
{
public:
	char* value = nullptr;
	StringItem(const char* _value);
	virtual ~StringItem() override;
	virtual IListItem* Clone() const override;
	virtual void Print() const override;
};
class IntItem : public IListItem
{
public:
	int value = 0;
	IntItem(int _value);
	virtual ~IntItem() override;
	virtual IListItem* Clone() const override;
	virtual void Print() const override;
};

