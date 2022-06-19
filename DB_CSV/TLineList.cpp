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

	pNode->iKey = m_iCount;
	
	if (m_pLast != NULL)
	{
		pNode->m_pNextNode = NULL;
		m_pLast->m_pNextNode = pNode;
	}
	else
		m_pFirst = pNode;

	m_pLast = pNode;

	m_iCount++;

	return pNode->iKey;
}

TNode* TLineList::FindNode(int iKey)
{
	TNode* pNode = m_pFirst;
	if (pNode == NULL)
		return NULL;

	do
	{
		if (pNode->iKey == iKey)
			return pNode;
		
		pNode = GetNext(pNode);
	} while (pNode != NULL);

	return NULL;
}

TNode* TLineList::GetNext(TNode* pNode)
{
	if (pNode != NULL)
		return pNode->m_pNextNode; 
	else
		return NULL;
}

TNode* TLineList::GetPrev(TNode* pNode)
{
	if (pNode == NULL)
		return NULL;
	
	TNode* pPrevNode = NULL;
	TNode* pFoundNode = m_pFirst;
	bool bNotFound = true;

	while (pFoundNode != NULL && bNotFound)
	{
		if (pFoundNode == pNode)
			bNotFound = false;
		else
		{
			pPrevNode = pFoundNode;
			pFoundNode = pFoundNode->m_pNextNode;
		}
	}

	return pPrevNode;
}

void TLineList::Reindex()
{
	m_iCount = 0;
	if (m_pFirst == NULL)
		return;

	TNode* pNode = m_pFirst;
	do
	{
		pNode->iKey = m_iCount;
		m_iCount++;
		pNode = GetNext(pNode);
	} while (pNode != NULL);
}

void TLineList::Process()
{
	if (m_pFirst == NULL)
		return;

	TNode * pNode = m_pFirst;
	do
	{
		std::cout << "Key=" << pNode->iKey<<"\n";
		pNode->Process();
		pNode = GetNext(pNode);
	} while (pNode != NULL);
}

TNode* TLineList::ExtractFirst()
{
	if (IsEmpty())
		return NULL;
	
	TNode* pNode;

	pNode = m_pFirst;
	m_pFirst = pNode->m_pNextNode;
	
	Reindex();
	return pNode;
}

TNode* TLineList::ExtractLast()
{
	if (IsEmpty())
		return NULL;
	
	TNode* pNode = m_pLast;
	m_pLast = GetPrev(m_pLast);
	pNode->m_pNextNode = NULL;
	m_pLast->m_pNextNode = NULL;
	Reindex();

	return pNode;
}




TLineList::~TLineList()
{
	std::cout << "Running the destructor of TLineList\n";
	bool bExit = true;
	TNode* pNode = m_pFirst;
	do
	{
		pNode = ExtractFirst();
		if (pNode != NULL)
		{
			if (pNode->m_pNextNode == NULL)
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
			pPrev->m_pNextNode = pNode->m_pNextNode;
			pNode->m_pNextNode = NULL;
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