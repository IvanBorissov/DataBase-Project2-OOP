#include "TField.h"
TField::TField(TFieldType FieldType, char* FieldName, int iSize)
{
	m_FieldType = FieldType;
	if (FieldName == nullptr)
	{
		m_strFieldName = new char[1];
		m_strFieldName[0] = '\0';
	}
	else
	{
		m_strFieldName = new char[strlen(FieldName) + 1];
#pragma warning(suppress : 4996)
		strcpy(m_strFieldName, FieldName);
		m_strFieldName[strlen(FieldName)] = '\0';
	}


	m_iSize = iSize;
}

void TField::SetFieldName(char* strValue)
{
	if (strValue == nullptr)
	{
		m_strFieldName = new char[1];
		m_strFieldName[0] = '\0';
	}
	else
	{
		m_strFieldName = new char[strlen(strValue) + 1];
#pragma warning(suppress : 4996)
		strcpy(m_strFieldName, strValue);
		m_strFieldName[strlen(strValue)] = '\0';
	}
}

void TField::Process()
{
	std::cout << "The Field is: " << m_FieldType << ";" << m_iSize << "\n";
}

TField::~TField()
{
	std::cout << "Running the destructor of TField " << m_FieldType << ";" << m_iSize << "\n";
	delete m_strFieldName;
}
