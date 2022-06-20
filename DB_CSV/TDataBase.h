#pragma once
#include "TNode.h"
#include "TLineList.h"
#include "TTable.h"

///The DataBase consists of a list of the Catalog (names of all the tables in this database) and a list of all tables in the database
class TDataBase : public TNode
{
public:
	TLineList* m_pCatalog;
	TLineList* m_pTables;
	TDataBase();
	virtual ~TDataBase() ;
	bool Init(char* PathToDB);
	bool AddCSVFileToDB(string FileName);
	bool TableExists(string TableName);
	TTable* GetTable(string TableName);
	void ShowTables();
	bool DescribeFields(string TableName);
	bool Print(string TableName);
	bool Export(string TableName, string FileName);
	bool SelectAllWhere(int iColumnNo, string strValue, string strTable);
	bool DeleteAllWhere(int iColumnNo, string strValue, string strTable);
	bool SelectCountWhere(int iColumnNo, string strValue, string strTable);
	bool AddColumnToTable(string strTable, string strColumn, string strColumnType);
	bool RenameTable (string strOldName, string strNewName);
private:
	string m_strPathToDB;
	void SaveCatalogToFile();

};


