#pragma once
#include<iostream>
#include<fstream>

#include "TNode.h"
#include "TLineList.h"
#include "TField.h"
#include "TRow.h"
using namespace std;

///A Table consists of a Name, definitions(Names) of all the fields in the table and a List for every row
class TTable :public TNode
{
public:
	char* m_strTableName;
	TLineList* m_pFieldsDefinitions;
	TLineList* m_pRows;
	TTable(char* TableName);
	virtual ~TTable();
	bool LoadFromFile(char* FileName);
	bool Export(string FileName);
	void DescribeFields();
	void Print();
	string GetRowAsCSV(TRow* pRow);
	bool SelectAllWhere(int iColumnNo, string strValue);
	bool DeleteAllWhere(int iColumnNo, string strValue);
	bool SelectCountWhere(int iColumnNo, string strValue);
	bool ColumnExists(string strColumnName);
	bool AddColumn(string strColumnName, string strColumnType);
private:
	bool ParseFieldDefinitions(string strFields);
	bool ParseDataRow(string strData);
};

