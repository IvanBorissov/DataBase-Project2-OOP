#pragma once
#include "TNode.h"

///TNode is the backbone of the project, but TLineList is how the project comes together
///Dynamic connected list with pointers to the first and last element
///has all the necessary functions to go through the List and realise all the functions needed
class TLineList : public TNode
{
public:
	TLineList();
	int Add(TNode* pNode);
	TNode* FindNode(int iKey);
	TNode* GetNext(TNode* pNode);
	TNode* GetPrev(TNode* pNode);
	TNode* GetFirst() { return m_pFirst; };
	void   SetFirst(TNode* pNode) { m_pFirst = pNode; };
	TNode* GetLast() { return m_pLast; };
	void   SetLast(TNode* pNode) { m_pLast = pNode; };
	int	   GetCount() { return m_iCount; };
	void   SetCount(int iCount) { m_iCount = iCount; };
	TNode* ExtractFirst();
	TNode* ExtractLast();
	TNode* ExtractNode(int iKey);
	bool   DeleteNode(int iKey);
	void   Reindex();
	bool   IsEmpty();
	virtual void Process();
	virtual ~TLineList();
private:
	TNode* m_pFirst;
	TNode* m_pLast;
	int    m_iCount;
};

