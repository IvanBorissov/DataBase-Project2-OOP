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
		int iKey = -1; ///index of the element
		int ID   = 0;
		string m_strDescription;
		TNode* m_pNextNode = nullptr;
	virtual void Process() {};
	virtual void Print() {};
	virtual string GetValue() { return ""; };
	virtual ~TNode() {};
};

