#pragma once
#include "TNode.h"

///Class that houses an string value and inherits TNode
///Basically an string value with a Pointer to the next element stuck to it
class TStringNode :  public TNode
{
public:
	char* m_pString;
	TStringNode();
	TStringNode(char*  strValue);
	int GetLenght();
	void Copy(char s[], int iLenght, int iPos);
	///TStringNode(const TStringNode &s);
	///TStringNode operator =(const TStringNode &s);
	void Rename(string s);
	int Pos(char ch);
	virtual void Process();
	virtual void Print();
	virtual string GetValue();
	virtual ~TStringNode();
};
