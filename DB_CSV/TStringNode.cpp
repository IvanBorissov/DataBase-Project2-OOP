#include "TStringNode.h"
TStringNode::TStringNode()
{
	m_pString = new char[1];
	m_pString[0] = '\0';
}

TStringNode::TStringNode(char* strValue)
{
	if (strValue == nullptr)
	{
		m_pString = new char[1];
		m_pString[0] = '\0';
	}
	else
	{
		m_pString = new char[strlen(strValue) + 1];
#pragma warning(suppress : 4996)
		strcpy(m_pString, strValue);
		m_pString[strlen(strValue)] = '\0';
	}
}

TStringNode::~TStringNode()
{
	std::cout << "Running the destructor of TStringNode: --> " << m_pString << "\n";
	delete m_pString;
}

void TStringNode::Process()
{
	std::cout << "String value: " << m_pString << "; Lenght of string: " << GetLenght() << "\n";
}

void TStringNode::Print()
{
	cout << m_pString << ";"; 
}

string TStringNode::GetValue()
{
	return m_pString;
}

int TStringNode::GetLenght()
{
	return strlen(m_pString);
}

void TStringNode::Copy(char s[], int iLenght, int iPos)
{
	for (int i = 0; i < iLenght; i++)
	{
		s[i] = m_pString[iPos + i];
	}
	
 	s[iLenght] = '\0';
}

int TStringNode::Pos(char ch)
{
	int iPos = -1;
	int iLenght = GetLenght();
	for (int i = 0; i < iLenght; i++)
	{
		if (m_pString[i] == ch)
		{
			iPos = i;
			break;
		}
	}

	return iPos;
}
