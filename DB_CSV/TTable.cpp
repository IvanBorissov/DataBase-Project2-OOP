#include "TIntNode.h"
#include "TStringNode.h"
#include "TDoubleNode.h"
#include "TRow.h"
#include "TTable.h"
TTable::TTable(char* TableName)
{
	if (TableName == nullptr)
	{
		m_strTableName = new char[1];
		m_strTableName[0] = '\0';
	}
	else
	{
		m_strTableName = new char[strlen(TableName) + 1];
#pragma warning(suppress : 4996)
		strcpy(m_strTableName, TableName);
		m_strTableName[strlen(TableName)] = '\0';
	}

	m_pFieldsDefinitions = new TLineList();;
	m_pRows = new TLineList();
}

TTable::~TTable()
{
	delete m_pFieldsDefinitions;
	delete m_pRows;
	delete m_strTableName;
}

bool TTable::LoadFromFile(char* FileName)
{
	bool bResult = false;

	string strFileName(FileName);

	ifstream file(strFileName);
	string strRow;
	int iRow = 0;

	if (file.is_open())
	{
		//while (file >> strRow)
		while (getline(file, strRow))
		{
			if (iRow == 0)
				ParseFieldDefinitions(strRow);
			else
				ParseDataRow(strRow);

			iRow++;
		}

		bResult = true;
	}

	m_pRows->Process();

	return bResult;
};

bool TTable::ParseFieldDefinitions(std::string strFields)
{
	stringstream ss(strFields);
	string strField;
	while (getline(ss, strField, ';'))
	{
		stringstream sss(strField);
		string strFieldName;
		string strFieldType;
		getline(sss, strFieldName, ':');
		getline(sss, strFieldType, ':');

		TField* pField;
		if (strFieldType == "int")
		{
			pField = new TField(TField::ftInt, &strFieldName[0], 0);
		}
		else
			if (strFieldType == "double")
			{
				pField = new TField(TField::ftDouble, &strFieldName[0], 0);
			}
			else //string
			{
				pField = new TField(TField::ftString, &strFieldName[0], 0);
			}
		m_pFieldsDefinitions->Add(pField);
	}

	return true;
};

bool TTable::ParseDataRow(string strData)
{
	stringstream ss(strData);
	string strField;
	int iFieldIndex = 0;

	TRow* pRow = new TRow();
	while (getline(ss, strField, ';'))
	{
		TField* pFieldType = (TField*)m_pFieldsDefinitions->FindNode(iFieldIndex);
		if (pFieldType != NULL) //add data to m_pRows only when have a FieldDefinition
		{
			switch (pFieldType->GetFieldType())
			{
			case TField::ftInt:
			{
				TIntNode* pIntNode = new TIntNode(stoi(strField));
				pRow->Add(pIntNode);
			}
			break;

			case TField::ftString:
			{
				TStringNode* pStringNode = new TStringNode(&strField[0]);
				pRow->Add(pStringNode);
			}
			break;

			case TField::ftDouble:
			{
				TDoubleNode* pDoubleNode = new TDoubleNode(stod(strField));
				pRow->Add(pDoubleNode);
			}
			break;
			}
		}
		iFieldIndex++;
	}
	this->m_pRows->Add(pRow);

	return true;
};

void TTable::DescribeFields()
{
	TField* pField = (TField*)m_pFieldsDefinitions->GetFirst();
	if (pField == NULL)
		return;

	do
	{
		cout << pField->GetFieldName() << ":";
		switch (pField->GetFieldType())
		{
		case TField::ftInt: cout << "int;\n";
			break;
		case TField::ftDouble: cout << "double;\n";
			break;
		case TField::ftString: cout << "string;\n";
			break;
		}


		pField = (TField*)m_pFieldsDefinitions->GetNext(pField);
	} while (pField != NULL);
}

void TTable::Print()
{
	TRow* pRow = (TRow*)m_pRows->GetFirst();
	if (pRow == NULL)
		return;

	do
	{
		pRow->Print();

		//pRow = (TRow*)m_pFieldsDefinitions->GetNext(pRow); ????
		pRow = (TRow*)m_pRows->GetNext(pRow);
	} while (pRow != NULL);

}

string TTable::GetRowAsCSV(TRow* pRow)
{
	if (pRow == NULL)
		return "";

	string s = "";

	TNode* pN = pRow->GetFirst();
	if (pN != NULL)
		do
		{
			s += pN->GetValue();
			if (pN->GetNextNodePtr() != NULL)
				s += ";";
			else
				s += "\n";

			pN = pRow->GetNext(pN);
		} while (pN != NULL);

		return s;
}

bool TTable::Export(string FileName)
{
	ofstream file(FileName);
	try
	{
		if (file.is_open())
		{

			TField* pField = (TField*)m_pFieldsDefinitions->GetFirst();
			if (pField == NULL)
				return false;

			string s("");
			do
			{
				s += pField->GetFieldName();
				s += ":";
				switch (pField->GetFieldType())
				{
				case TField::ftInt: s += "int";
					break;
				case TField::ftDouble: s += "double";
					break;
				case TField::ftString: s += "string";
					break;
				}

				if (pField->GetNextNodePtr() != NULL)
					s += ";";
				else
					s += "\n";

				pField = (TField*)m_pFieldsDefinitions->GetNext(pField);
			} while (pField != NULL);

			//export field definitions to first row of the file
			file << s;

			TRow* pR = (TRow*)m_pRows->GetFirst();
			if (pR != NULL)
			{
				do
				{
					s = GetRowAsCSV(pR);
					file << s;

					pR = (TRow*)m_pRows->GetNext(pR);
				} while (pR != NULL);
			}

			file.close();
			return true;
		}
		return false;
	}
	catch (...)
	{
		return false;
	}

	return false;
}

bool TTable::SelectAllWhere(int iColumnNo, string strValue)
{
	TField* pF = (TField*)m_pFieldsDefinitions->FindNode(iColumnNo);
	if (pF == NULL)
		return false;


	TRow* pR = (TRow*)m_pRows->GetFirst();
	if (pR != NULL)
	{
		do
		{
			if (pR->Check(iColumnNo, pF->GetFieldType(), strValue))
			{
				string s = GetRowAsCSV(pR);
				cout << s;
			}

			pR = (TRow*)m_pRows->GetNext(pR);
		} while (pR != NULL);
	}
	return false;
}

bool TTable::DeleteAllWhere(int iColumnNo, string strValue)
{
	TField* pF = (TField*)m_pFieldsDefinitions->FindNode(iColumnNo);
	if (pF == NULL)
		return false;


	TRow* pR = (TRow*)m_pRows->GetFirst();
	if (pR != NULL)
	{
		do
		{
			if (pR->Check(iColumnNo, pF->GetFieldType(), strValue))
			{

				TRow* pRTmp = (TRow*)m_pRows->ExtractNode(pR->GetKey());
				if (pRTmp != NULL)
				{
					pR = (TRow*)pRTmp->GetNextNodePtr();
					delete pRTmp;

					if (pR != NULL)
						continue;
					else
						break;
				}

			}

			if (pR != NULL)
				pR = (TRow*)m_pRows->GetNext(pR);

		} while (pR != NULL);
		return true;
	}
	return false;
}

bool TTable::SelectCountWhere(int iColumnNo, string strValue)
{
	TField* pF = (TField*)m_pFieldsDefinitions->FindNode(iColumnNo);
	if (pF == NULL)
		return false;

	int iCount = 0;

	TRow* pR = (TRow*)m_pRows->GetFirst();
	if (pR != NULL)
	{
		do
		{
			if (pR->Check(iColumnNo, pF->GetFieldType(), strValue))
				iCount++;

			pR = (TRow*)m_pRows->GetNext(pR);
		} while (pR != NULL);

		cout << "Count = " << iCount << "\n";

		return true;
	}
	return false;
}

bool TTable::ColumnExists(string strColumnName)
{
	TField* pField = (TField*)m_pFieldsDefinitions->GetFirst();
	if (pField == NULL)
		return false;

	do
	{
		if (strColumnName == pField->GetFieldName())
			return true;

		pField = (TField*)m_pFieldsDefinitions->GetNext(pField);
	} while (pField != NULL);

	return false;
}

bool TTable::AddColumn(string strColumnName, string strColumnType)
{
	if (ColumnExists(strColumnName))
		return false;

	if (strColumnType != "int" && strColumnType != "double" && strColumnType != "string")
		return false;

	// add the field to m_pFieldsDefinitions
	TField* pField;
	if (strColumnType == "int")
	{
		pField = new TField(TField::ftInt, &strColumnName[0], 0);
	}
	else
		if (strColumnType == "double")
		{
			pField = new TField(TField::ftDouble, &strColumnName[0], 0);
		}
		else //string
		{
			pField = new TField(TField::ftString, &strColumnName[0], 0);
		}
	m_pFieldsDefinitions->Add(pField);

	//add emty values on the last place of each row

	TRow* pRow = (TRow*)m_pRows->GetFirst();
	if (pRow != NULL)
	{
		do
		{
			switch (pField->GetFieldType())
			{
			case TField::ftInt:
			{
				TIntNode* pIntNode = new TIntNode(0);
				pRow->Add(pIntNode);
			}
			break;

			case TField::ftString:
			{
				string s = "NULL";
				TStringNode* pStringNode = new TStringNode(&s[0]);
				pRow->Add(pStringNode);
			}
			break;

			case TField::ftDouble:
			{
				TDoubleNode* pDoubleNode = new TDoubleNode(0);
				pRow->Add(pDoubleNode);
			}
			break;
			}

			pRow = (TRow*)m_pRows->GetNext(pRow);
		} while (pRow != NULL);

		return true;
	}

	return false;
}

void TTable::Rename(string s)
{
	delete[] m_strTableName;
	int sz = s.size() + 1;
	m_strTableName = new char[sz];
	for (int i = 0; i < sz - 1; i++)
	{
		m_strTableName[i] = s[i];
	}
	m_strTableName[sz - 1] = '\0';
}
