#include "TDoubleNode.h"

TDoubleNode::TDoubleNode(double dValue)
{
	m_pValue = dValue;
}

TDoubleNode::~TDoubleNode()
{
	std::cout << "Running the destructor of TDoubleNode: --> " << m_pValue << "\n";
}

void TDoubleNode::Process()
{
	std::cout << "Double value:" << m_pValue << "\n";
}

void TDoubleNode::Print()
{
	cout << m_pValue << ";";
}

string TDoubleNode::GetValue()
{
	return to_string(m_pValue);
}
 

