#pragma once
#include "TNode.h"

///Class that houses an string value and inherits TNode
///Basically an string value with a Pointer to the next element stuck to it
class TStringNode : public TNode
{
public:
	TStringNode();
	TStringNode(char* strValue);
	int GetLenght();
	char* GetString() { return m_pString; };
	void SetString(char* strValue);
	void Copy(char s[], int iLenght, int iPos);
	TStringNode(const TStringNode& s);
	TStringNode operator =(const TStringNode& s);
	void Rename(string s);
	int Pos(char ch);
	virtual void Process();
	virtual void Print();
	virtual string GetValue();
	virtual ~TStringNode();
protected:
	char* m_pString;
private:
	void Copy(const TStringNode& s);
};
