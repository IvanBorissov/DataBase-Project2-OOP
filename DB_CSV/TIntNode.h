#pragma once
#include "TNode.h"

///Class that houses an integer value and inherits TNode
///Basically an Integer value with a Pointer to the next element stuck to it
class TIntNode : public TNode
{
public:
	TIntNode(int iValue);
	int getIntValue() { return m_pValue; };
	void setValue(int iValue) { m_pValue = iValue; };
	virtual void Process();
	virtual void Print();
	virtual string GetValue();
	virtual ~TIntNode();
protected:
	int m_pValue;
};

