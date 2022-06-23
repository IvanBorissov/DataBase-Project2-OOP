#pragma once
#include "TNode.h"

///Class that houses an integer value and inherits TNode
///Basically an Integer value with a Pointer to the next element stuck to it
class TIntNode : public TNode
{
public:
	int m_pValue;
	TIntNode(int iValue);
	virtual void Process();
	virtual void Print();
	virtual string GetValue();
	virtual ~TIntNode();
};

