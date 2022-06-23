// DB_CSV.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "TIntNode.h"
#include "TStringNode.h"
#include "TDoubleNode.h"
#include "TLineList.h"
#include "TField.h"
#include "TDataBase.h"
#include "IDataBase.h"
#include <direct.h>

int main(int argc, char* argv[])
{
    time_t tmStart = time(0);

    std::string argv_str(argv[0]);
    std::string strBase = argv_str.substr(0, argv_str.find_last_of("\\"));

   IDataBase Controller(strBase);

   Controller.Run();

    //std::cout << "Hello World!\n";

    //std::string argv_str(argv[0]);
    //std::string base = argv_str.substr(0, argv_str.find_last_of("\\"));

   /* TDataBase* pDataBase = new TDataBase();
    pDataBase->Init(&base[0]);
    pDataBase->Process();
    
    string s;
    bool bShowInfo = true;
    
    do
    {
        if (bShowInfo)
        {
            system("cls");
            cout << "Possible actions:\n\n";
            cout << "import <file name>                                  Import a new table from file into DB.\n";                                  //OK
            cout << "showtables                                          Display list of all tables in DB.\n";                                      //OK
            cout << "describe <name>                                     Display the types of columns of selected table.\n";                        //OK
            cout << "print <name>                                        Print all rows from selected table.\n";                                    //OK    
            cout << "export <name> <file name>                           Export table with <name> in file <filename>\n";                            //OK
            cout << "select <column n> <value> < table name >            Select all rows from <table name> where <column n> have a <value>\n";      //OK
            cout << "addcolumn <table name> <column name > <column type> Add new <clumn name> to <table> with empty values\n";                      //OK   
            cout << "delete <table name> <search column n> <search value>Delete all rows from table where column n have a <search value>\n";
            cout << "insert <table name> <column 1> … <column n>         Insert in <table name> a row with values <column 1>...<column n>\n";
            cout << "innerjoin <table 1> <column n1> <table 2> <column n2> Inner Join on two tables on <column n1> and <column n2>\n";
            cout << "rename <old name> <new name>                        Rename a table <old name> with <new name>\n";
            cout << "count <table name> <search column n> <search value> Display a count of rows having a <search value> in <search column n>\n\n";   //OK
            cout << "aggregate <table name> <search column n>            Performs an <operation> sum, product, maximum, minimum \n";
            cout << "          <search value> <target column n>          on the values of the column with sequence number <target column n>\n";
            cout << "          <operation>                               of all rows whose columns are numbered < search column n >\n";
            cout << "                                                    contain the value <search value>\n";
            cout << "\n\n";
        }
        bShowInfo = true;

        cout << ".>";
        std::getline(std::cin,s);

        //it's good to have a lexical analyzer here, but that's another topic

        int iPos = s.find("showtables");
        if ( iPos>=0)
        {
            pDataBase->ShowTables();
            bShowInfo = false;
            continue;
        }

        iPos = s.find("import");
        if (iPos >= 0)
        {
            stringstream ss(s);
            string strTmp;
            while(getline(ss, strTmp, ' '));
            if (!pDataBase->AddCSVFileToDB(strTmp))
                cout << "Error adding a file to DB\n";
            bShowInfo = false;
            continue;
        }

        iPos = s.find("describe");
        if (iPos >= 0)
        {
            stringstream ss(s);
            string strTmp;
            while (getline(ss, strTmp, ' '));
            if (!pDataBase->DescribeFields(strTmp))
                cout << "The table " << strTmp << " isn't in DB.\n";
            bShowInfo = false;
            continue;
        }

        iPos = s.find("print");
        if (iPos >= 0)
        {
            stringstream ss(s);
            string strTmp;
            while (getline(ss, strTmp, ' '));
            if (!pDataBase->Print(strTmp))
                cout << "The table " << strTmp << " isn't in DB.\n";
            bShowInfo = false;
            continue;
        }
 
        iPos = s.find("export");
        if (iPos >= 0)
        {
            stringstream ss(s);
            string strTmp, strTable, strFile;
            getline(ss, strTmp, ' ');
            getline(ss, strTable, ' '); 
            getline(ss, strFile, ' ');

            if (!pDataBase->TableExists(strTable))
            {
                cout << "The table " << strTable << " isn't in DB.\n";
            }
            else if (!pDataBase->Export(strTable,strFile))
                cout << "Error on exporting "<<strTable<<" to "<<strFile<<"\n";

            bShowInfo = false;
            continue;
        }

        iPos = s.find("select"); //select <search column n> <search value> <table name>
        if (iPos >= 0)
        {
            stringstream ss(s);
            string strTmp, strColumn, strValue, strTable;
            getline(ss, strTmp, ' ');
            getline(ss, strColumn, ' ');
            getline(ss, strValue, ' ');
            getline(ss, strTable, ' ');

            int iColumnNo = stoi(strColumn);

            if (!pDataBase->TableExists(strTable))
            {
                cout << "The table " << strTable << " isn't in DB.\n";
            }
            else if (!pDataBase->SelectAllWhere(iColumnNo, strValue, strTable))
                cout << "Error on select where " << strColumn << " have avalue " << strValue << " in table " << strTable << ".\n";

            bShowInfo = false;
            continue;
        }

        iPos = s.find("delete"); //delete <table name> <search column n> <search value> 
        if (iPos >= 0)
        {
            stringstream ss(s);
            string strTmp, strColumn, strValue, strTable;
            getline(ss, strTmp, ' ');
            getline(ss, strColumn, ' ');
            getline(ss, strValue, ' ');
            getline(ss, strTable, ' ');


            int iColumnNo = stoi(strColumn);

            if (!pDataBase->TableExists(strTable))
            {
                cout << "The table " << strTable << " isn't in DB.\n";
            }
            else if (!pDataBase->DeleteAllWhere(iColumnNo, strValue, strTable))
                cout << "Error on delete where " << strColumn << " have avalue " << strValue << " in table " << strTable << ".\n";

            bShowInfo = false;
            continue;
        }

        iPos = s.find("count"); //count <table name> <search column n> <search value>
        if (iPos >= 0)
        {
            stringstream ss(s);
            string strTmp, strColumn, strValue, strTable;
            getline(ss, strTmp, ' ');
            getline(ss, strTable, ' '); 
            getline(ss, strColumn, ' ');
            getline(ss, strValue, ' ');
            
            
            int iColumnNo = stoi(strColumn);

            if (!pDataBase->TableExists(strTable))
            {
                cout << "The table " << strTable << " isn't in DB.\n";
            }
            else if (!pDataBase->SelectCountWhere(iColumnNo, strValue, strTable))
                cout << "Error on select where " << strColumn << " have avalue " << strValue << " in table " << strTable <<".\n";

            bShowInfo = false;
            continue;
        }

        iPos = s.find("addcolumn"); //addcolumn <table name> <column name > <column type>
        if (iPos >= 0)
        {
            stringstream ss(s);
            string strTmp, strColumn, strColumnType, strTable;
            getline(ss, strTmp, ' ');
            getline(ss, strTable, ' ');
            getline(ss, strColumn, ' ');
            getline(ss, strColumnType, ' ');

            if (strColumnType != "int" && strColumnType != "double" && strColumnType != "string")
            {
                cout << "The type of " << strColumnType << " is not allowed.\n"; 
            }
            
            if (!pDataBase->TableExists(strTable))
            {
                cout << "The table " << strTable << " isn't in DB.\n";
            }
            else if (!pDataBase->AddColumnToTable(strTable, strColumn, strColumnType ))
                cout << "Error on adding a column " << strColumn << " with type " << strColumnType << " in table " << strTable << ".\n"; 

            bShowInfo = false;
            continue;
        }
       

    } while (s != "exit");
    

    delete pDataBase;
    */
}
    
//    TLineList* pList = new TLineList();
//    TLineList* pList1 = new TLineList();
//    
//    TIntNode* pInt = new TIntNode(10);
//    pList->Add(pInt);
//   
//    char chTmp[] = "Ala Bala Portokala ...";
//    TStringNode* pStr = new TStringNode(chTmp);
//    pList->Add(pStr);
//
//    TDoubleNode* pDbl = new TDoubleNode(1.2345678);
//    pList->Add(pDbl);
//
//    TIntNode* pInt1 = new TIntNode(15);
//    pList->Add(pInt1);
//
//    char chTmp1[] = "Koj iziade kashkavala ...";
//    TStringNode* pStr1 = new TStringNode(chTmp1);
//    pList->Add(pStr1);
//
//    TDoubleNode* pDbl1 = new TDoubleNode(56.36987);
//    pList->Add(pDbl1);
//
//    //stress test
//    int iCount = 100000;
//    for (int i = 0; i < iCount; i++)
//    {
//        TNode* pIN = new TIntNode(i);
//        pList->Add(pIN);
//
//        char tmp[10];
//        sprintf_s(tmp, "%d", i);
//        TNode* pSN = new TStringNode(tmp);
//        pList->Add(pSN);
//
//        TNode* pDN = new TDoubleNode(i * 0.123);
//        pList->Add(pDN);
//
//        TField* pField;
//        switch (i % 3)
//        {
//            case TField::ftInt :
//                pField = new TField(TField::ftInt, tmp, i*12);
//                pList->Add(pField);
//                break;
//            case TField::ftString:
//                pField = new TField(TField::ftString, tmp, i*13);
//                pList->Add(pField);
//                break;
//            case TField::ftDouble:
//                pField = new TField(TField::ftDouble, tmp, i*14);
//                pList->Add(pField);
//                break;
//        }
//        
//
//    }
//
//    TNode* p = pList->ExtractFirst();
//    if (p != NULL)
//    {
//        std::cout << "\n\nEXTRACTED NODE is:\n";
//        p->Process();
//        std::cout << "\n\n";
//        delete p;
//    }
//
//    p = pList->ExtractNode(2);
//    if (p != NULL)
//    {
//        std::cout << "\n\nEXTRACTED NODE is:\n";
//        p->Process();
//        std::cout << "\n\n";
//        delete p;
//    }
//
//    p = pList->ExtractLast();
//    if (p != NULL)
//    {
//        std::cout << "\n\nEXTRACTED NODE is:\n";
//        p->Process();
//        std::cout << "\n\n";
//        delete p;
//    }
//
//
//    if (pList->DeleteNode(2))
//        std::cout << "Node with a Key=2 is deleted.\n\n";
//
//    pList1->Add(pList);
//
//    char chTmp2[] = "Some text field ...";
//    TStringNode* pStr2 = new TStringNode(chTmp2);
//    pList1->Add(pStr2);
//
//    //pList->Process();
//    pList1->Process();
//
//    delete pList1;
//
//    time_t tmEnd = time(0);
//#pragma warning(suppress : 4996)
//    std::cout << "Start at: " << ctime(&tmStart) << std::endl;
//#pragma warning(suppress : 4996)
//    std::cout << "End in: " << ctime(&tmEnd) << std::endl;
//#pragma warning(suppress : 4996)
//    std::cout << "Execution Time: " << (double)(tmEnd - tmStart) << " Seconds" << std::endl;
//
//    std::string strKey;
//    std::cin >> strKey;

    //pInt->Process();
    //pStr->Process();

    /*TNode* pNode = NULL;

    pNode = pInt;
    pNode->Process();
    delete pNode;

    pNode = pStr;
    pNode->Process();
    delete pNode;

    pNode = pDbl;
    pNode->Process();
    delete pNode;*/
    
    //delete pInt;
    //delete pStr;
//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
