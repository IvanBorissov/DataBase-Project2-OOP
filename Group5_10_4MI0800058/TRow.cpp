#include "TRow.h"
#include "TField.h"
#include "TIntNode.h"
#include "TStringNode.h"
#include "TDoubleNode.h"

void TRow::Print()
{
	TNode* pNode = m_pFirst;
	if (pNode == NULL)
		return;

	do
	{
		pNode->Print();
		pNode = (TField*)GetNext(pNode);
	} while (pNode != NULL);
	cout << "\n";
}

bool TRow::Check(int iColumnNo, TField::TFieldType ftFieldType, string strValue) 
{ 
	TNode* pN = this->FindNode(iColumnNo);
	if (pN == NULL)
		return false;

	switch (ftFieldType)
	{
	case TField::ftInt:
		if (stoi(pN->GetValue()) - stoi(strValue) == 0)
			return true;
			break;
		case TField::ftDouble:
			if (stod(pN->GetValue()) - stod(strValue) < 0.0001)
			return true;
			break;
		case TField::ftString:
			if (pN->GetValue() == strValue)
				return true;
			break;

	}
	return false; 
}