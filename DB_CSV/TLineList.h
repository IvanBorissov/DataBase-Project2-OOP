#pragma once
#include "TNode.h"

///TNode is the backbone of the project, but TLineList is how the project comes together
///Dynamic connected list with pointers to the first and last element
///has all the necessary functions to go through the List and realise all the functions needed
class TLineList : public TNode
{
public:
	TNode* m_pFirst;
	TNode* m_pLast;
	int    m_iCount;
	TLineList();
	int Add(TNode* pNode);
	TNode* FindNode(int iKey);
	TNode* GetNext(TNode* pNode);
	TNode* GetPrev(TNode* pNode);
	TNode* ExtractFirst();
	TNode* ExtractLast();
	TNode* ExtractNode(int iKey);
	bool   DeleteNode(int iKey);
	void   Reindex();
	bool   IsEmpty();
	virtual void Process();
	virtual ~TLineList();
};

