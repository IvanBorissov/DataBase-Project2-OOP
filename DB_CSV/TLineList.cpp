#include "TLineList.h"

TLineList::TLineList()
{
	m_pFirst = NULL;
	m_pLast = NULL;
	m_iCount = 0;
}

bool TLineList::IsEmpty()
{
	return (m_iCount == 0);
}

int TLineList::Add(TNode* pNode)
{
	if (pNode == NULL)
		return -1;

	pNode->SetKey(m_iCount);

	if (m_pLast != NULL)
	{
		pNode->SetNextNodePtr(NULL);//pNode->m_pNextNode = NULL;
		m_pLast->SetNextNodePtr(pNode);
	}
	else
		SetFirst(pNode);

	SetLast(pNode);

	int i = GetCount() + 1;
	SetCount(i);

	return pNode->GetKey();
}

TNode* TLineList::FindNode(int iKey)
{
	TNode* pNode = GetFirst();
	if (pNode == NULL)
		return NULL;

	do
	{
		if (pNode->GetKey() == iKey)
			return pNode;

		pNode = GetNext(pNode);
	} while (pNode != NULL);

	return NULL;
}

TNode* TLineList::GetNext(TNode* pNode)
{
	if (pNode != NULL)
		return pNode->GetNextNodePtr();
	else
		return NULL;
}

TNode* TLineList::GetPrev(TNode* pNode)
{
	if (pNode == NULL)
		return NULL;

	TNode* pPrevNode = NULL;
	TNode* pFoundNode = GetFirst();
	bool bNotFound = true;

	while (pFoundNode != NULL && bNotFound)
	{
		if (pFoundNode == pNode)
			bNotFound = false;
		else
		{
			pPrevNode = pFoundNode;
			pFoundNode = pFoundNode->GetNextNodePtr();
		}
	}

	return pPrevNode;
}

void TLineList::Reindex()
{
	SetCount(0);
	if (GetFirst() == NULL)
		return;

	TNode* pNode = GetFirst();
	do
	{
		pNode->SetKey(m_iCount);
		int i = GetCount();
		SetCount(i++);
		pNode = GetNext(pNode);
	} while (pNode != NULL);
}

void TLineList::Process()
{
	if (GetFirst() == NULL)
		return;

	TNode* pNode = m_pFirst;
	do
	{
		std::cout << "Key=" << pNode->GetKey() << "\n";
		pNode->Process();
		pNode = GetNext(pNode);
	} while (pNode != NULL);
}

TNode* TLineList::ExtractFirst()
{
	if (IsEmpty())
		return NULL;

	TNode* pNode;

	pNode = GetFirst();
	m_pFirst = pNode->GetNextNodePtr();

	Reindex();
	return pNode;
}

TNode* TLineList::ExtractLast()
{
	if (IsEmpty())
		return NULL;

	TNode* pNode = GetLast();//m_pLast;
	SetLast(GetPrev(pNode));
	//m_pLast = GetPrev(m_pLast);

	pNode->SetNextNodePtr(NULL);
	m_pLast->SetNextNodePtr(NULL);
	Reindex();

	return pNode;
}




TLineList::~TLineList()
{
	std::cout << "Running the destructor of TLineList\n";
	bool bExit = true;
	TNode* pNode = GetFirst();
	do
	{
		pNode = ExtractFirst();
		if (pNode != NULL)
		{
			if (pNode->GetNextNodePtr() == NULL)
				bExit = false;
			delete pNode;
		}
		else
			bExit = false;


	} while (bExit);
}

TNode* TLineList::ExtractNode(int iKey)
{
	TNode* pPrev = NULL;
	TNode* pNode = FindNode(iKey);

	if (pNode != NULL)
	{
		pPrev = GetPrev(pNode);
		if (pPrev != NULL)
		{
			//pPrev->m_pNextNode = pNode->m_pNextNode;
			pPrev->SetNextNodePtr(pNode->GetNextNodePtr());
			pNode->SetNextNodePtr(NULL);
			Reindex();
			return pNode;
		}
		else
			return ExtractFirst();

	}

	return NULL;
}
bool   TLineList::DeleteNode(int iKey)
{
	bool bResult = false;
	TNode* pNode = ExtractNode(iKey);
	if (pNode != NULL)
	{
		delete pNode;
		bResult = true;
	}


	return bResult;
}