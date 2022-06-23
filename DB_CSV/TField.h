#pragma once
#include "TNode.h"
class TField : public TNode
{
public:
	enum TFieldType { ftInt = 0, ftString, ftDouble };

	TField(TFieldType FieldType, char* FieldName, int iSize);

	TFieldType GetFieldType() { return m_FieldType; };
	void SetFieldType(TFieldType FieldType) { m_FieldType = FieldType; };

	virtual void Process();
	virtual ~TField();
	char* GetFieldName() { return m_strFieldName; };
	void SetFieldName(char* strValue);
	int GetSize() { return m_iSize; };
	void SetSize(int iSize) { m_iSize = iSize; };


private:
	TFieldType m_FieldType;
	char* m_strFieldName;
	int m_iSize;

};

