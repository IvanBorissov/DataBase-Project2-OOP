#include <iostream>
#include <fstream>
#include <filesystem>
#include "TDataBase.h"
#include "TStringNode.h"
#include "TTable.h"

namespace fs = std::filesystem;

TDataBase::TDataBase()
{
	m_pCatalog = new TLineList();
	m_pTables = new TLineList();
};

TDataBase::~TDataBase()
{
	delete m_pCatalog;
	delete m_pTables;
};

bool TDataBase::Init(char* PathToDB)
{
	bool bResult = false;

	m_strPathToDB = PathToDB ;
	string strFileName(PathToDB);
	strFileName.append("\\catalog.txt");
	
	ifstream file(strFileName);
	string line;

	if (file.is_open())
	{
		while (file >> line)
		{
			strFileName.assign(PathToDB);
			strFileName.append("\\");
			strFileName.append(line);
			TStringNode* pStrNode = new TStringNode(&strFileName[0]);
			m_pCatalog->Add(pStrNode);
		}
	}
	
	if (m_pCatalog->IsEmpty())
		return bResult;
	
	TStringNode* pStrNode = (TStringNode*)m_pCatalog->m_pFirst;
	do
	{
		/*char arr[80];
		char* TblName = pStrNode->m_pString;
		pStrNode->Copy(arr, pStrNode->Pos('.'),0);*/

		string strTableName(pStrNode->m_pString);
		
		int iPos = strTableName.find_last_of("\\"); //strip the filepath form files
		strTableName = strTableName.substr(iPos + 1, strTableName.length() - iPos);
		strTableName = strTableName.substr(0, strTableName.find_last_of("."));
		TTable* pTable = new TTable(&strTableName[0]);
		pTable->LoadFromFile(pStrNode->m_pString);  
 		m_pTables->Add(pTable);

		pStrNode = (TStringNode*)m_pCatalog->GetNext(pStrNode);
	} while (pStrNode != NULL);


	return bResult;
};


bool TDataBase::AddCSVFileToDB(string FileName) 
{ 
	bool bResult = false;
	
	if (FileName.find(".csv") < 0)
		return bResult;

	string strDestFile(FileName);
	int iPos = strDestFile.find_last_of("\\");
	strDestFile = strDestFile.substr(iPos+1, strDestFile.length()-iPos);
	string strTableName(strDestFile);

	//search in Catalog
	if (!m_pCatalog->IsEmpty())
	{
		TStringNode* pStrN = (TStringNode*)m_pCatalog->m_pFirst;
		do
		{
			string strTmp(pStrN->m_pString);
			iPos = strTmp.find_last_of("\\");
			strTmp = strTmp.substr(iPos + 1, strTmp.length() - iPos);
			if (strTmp == strTableName)
				return bResult;//false

			pStrN = (TStringNode*)pStrN->m_pNextNode;
		} while (pStrN != NULL);
	}
	
	
	


	strDestFile = m_strPathToDB + "\\" + strDestFile;
	try
	{
		fs::copy(FileName, strDestFile, fs::copy_options::overwrite_existing);
		TStringNode* pStrNode = new TStringNode(&strDestFile[0]);
		m_pCatalog->Add(pStrNode);
		SaveCatalogToFile();

		TTable* pTable = new TTable(&strTableName[0]);
		pTable->LoadFromFile(&strDestFile[0]);
		m_pTables->Add(pTable);


		bResult = true;
	}
	catch(...)
	{
		bResult = false;
	}
	

	return bResult;
};

void TDataBase::ShowTables()
{

	TStringNode* pN = (TStringNode*)m_pCatalog->m_pFirst;
	if (pN == NULL)
		return;

	do
	{
		string s(pN->m_pString);
		int iPos = s.find_last_of("\\"); //strip the filepath form files
		cout << s.substr(iPos+1,s.length() - iPos) << "\n";
		pN = (TStringNode*)m_pCatalog->GetNext(pN);
	} while (pN != NULL);

}

void TDataBase::SaveCatalogToFile()
{
	TStringNode* pN = (TStringNode*)m_pCatalog->m_pFirst;
	if (pN == NULL)
		return;

	string strFileName(m_strPathToDB);
	strFileName.append("\\catalog.txt");

	ofstream file(strFileName);
	if (file.is_open())
	{

		do
		{
			string s(pN->m_pString);
			int iPos = s.find_last_of("\\"); //strip the filepath form files
			file << s.substr(iPos + 1, s.length() - iPos) << "\n";
			pN = (TStringNode*)m_pCatalog->GetNext(pN);
		} while (pN != NULL);
		
		file.close();
	}
}

bool TDataBase::DescribeFields(string TableName)
{
	TTable* pTable = (TTable*)m_pTables->m_pFirst;
	if (pTable == NULL)
		return false;

	do
	{
		string s(pTable->m_strTableName);
		if (s == TableName || s.append(".csv")== TableName)
		{
			pTable->DescribeFields();
			return true;
		}
		
		pTable = (TTable*)m_pCatalog->GetNext(pTable);
	} while (pTable != NULL);

	return false;
}

bool TDataBase::Print(string TableName)
{
	TTable* pTable = GetTable(TableName);
	if (pTable == NULL)
		return false;

	pTable->Print();
	return true;
}

TTable* TDataBase::GetTable(string TableName)
{
	TTable* pTable = (TTable*)m_pTables->m_pFirst;
	if (pTable == NULL)
		return NULL;

	do
	{
		string s(pTable->m_strTableName);
		if (s == TableName || s.append(".csv") == TableName)
			return pTable;
		
		pTable = (TTable*)m_pCatalog->GetNext(pTable);
	} while (pTable != NULL);

	return NULL;
}

bool TDataBase::TableExists(string TableName)
{
	
	return (GetTable(TableName)!=NULL);
}

bool TDataBase::Export(string TableName, string FileName)
{

	TTable* pTable = GetTable(TableName);
	if (pTable == NULL)
		return false;

	return pTable->Export(FileName);
}

bool TDataBase::SelectAllWhere(int iColumnNo, string strValue, string strTable)
{
	TTable* pTable = GetTable(strTable);
	if (pTable == NULL)
		return false;

	pTable->SelectAllWhere(iColumnNo, strValue);

	return true;
}

bool TDataBase::DeleteAllWhere(int iColumnNo, string strValue, string strTable)
{
	TTable* pTable = GetTable(strTable);
	if (pTable == NULL)
		return false;

	if (pTable->DeleteAllWhere(iColumnNo, strValue))
	{
		string strFileName = m_strPathToDB + "\\" + pTable->m_strTableName + ".csv";
		if (pTable->Export(strFileName))
			return true;
	}

	return false;
}

bool TDataBase::SelectCountWhere(int iColumnNo, string strValue, string strTable)
{
	TTable* pTable = GetTable(strTable);
	if (pTable == NULL)
		return false;

	pTable->SelectCountWhere(iColumnNo, strValue);

	return true;
}

bool TDataBase::AddColumnToTable(string strTable, string strColumn, string strColumnType)
{
	TTable* pTable = GetTable(strTable);
	if (pTable == NULL)
		return false;

	if (pTable->AddColumn(strColumn, strColumnType))
	{
		string strFileName = m_strPathToDB + "\\" + pTable->m_strTableName + ".csv";
		if (pTable->Export(strFileName))
			return true;
	}
	return false;
}