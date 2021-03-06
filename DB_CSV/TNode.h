#pragma once
#include<fstream>
#include <iostream>
#include <sstream>


using namespace std;

///Tnode is a Base Class for the whole project
///it has an iKey and a TNode pointer to the next element
///it works as a "hanger" for all types of objects
class TNode
{
public:
	TNode* GetNextNodePtr() { return m_pNextNode; };
	void SetNextNodePtr(TNode* pNode) { m_pNextNode = pNode; };
	int GetKey() { return m_iKey; };
	void SetKey(int iKey) { m_iKey = iKey; };
	string GetDescription() { return m_strDescription; };
	virtual void Process() {};
	virtual void Print() {};
	virtual string GetValue() { return ""; };
	virtual ~TNode() {};
protected:
	int m_iKey = -1; ///index of the element
	string m_strDescription;
	TNode* m_pNextNode = nullptr;
};

