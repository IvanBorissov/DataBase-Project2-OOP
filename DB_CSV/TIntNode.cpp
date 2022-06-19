#include "TIntNode.h"

TIntNode::TIntNode(int iValue)
{
	m_pValue = iValue;
}

TIntNode::~TIntNode()
{
	std::cout << "Running the destructor of TIntNode: --> " << m_pValue << "\n";
}

void TIntNode::Process()
{
	std::cout << "Int value:" << m_pValue << "\n";
}

void TIntNode::Print()
{
	cout << m_pValue << ";";
}

string TIntNode::GetValue()
{
	return to_string(m_pValue);
}


