#pragma once
#include "TNode.h"

///Class that houses an integer value and inherits TNode
///Basically an Integer value with a Pointer to the next element stuck to it
class TDoubleNode : public TNode
{
public:
	TDoubleNode(double dValue);
	double getDoubleValue() { return m_pValue; };
	void setValue(double dValue) { m_pValue = dValue; };
	virtual void Process();
	virtual void Print();
	virtual string GetValue();
	virtual ~TDoubleNode();
protected:
	double m_pValue;
};

