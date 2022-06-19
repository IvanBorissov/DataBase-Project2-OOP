#pragma once
#include "TNode.h"
class TField : public TNode
{
public:
	enum TFieldType { ftInt = 0, ftString, ftDouble};
	TFieldType m_FieldType;
	char* m_strFieldName;
	int m_iSize;
	TField(TFieldType FieldType, char* FieldName, int iSize);
	virtual void Process();
	virtual ~TField();
};

