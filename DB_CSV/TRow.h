#pragma once
#include "TLineList.h"
#include "TField.h"
class TRow : public TLineList
{
public:
	virtual void Print();
	bool Check(int iColumnNo, TField::TFieldType ftFieldType, string strValue);
};

