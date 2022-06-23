#include "IDataBase.h"
#include "TDataBase.h"

IDataBase::IDataBase(std::string PathToDB)
{
    pDataBase = new TDataBase();
    pDataBase->Init(&PathToDB[0]);
}

void IDataBase::Run()
{
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
        std::getline(std::cin, s);

        //it's good to have a lexical analyzer here, but that's another topic

        int iPos = s.find("showtables");
        if (iPos >= 0)
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
            while (getline(ss, strTmp, ' '));
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
            else if (!pDataBase->Export(strTable, strFile))
                cout << "Error on exporting " << strTable << " to " << strFile << "\n";

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
                cout << "Error on select where " << strColumn << " have avalue " << strValue << " in table " << strTable << ".\n";

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
            else if (!pDataBase->AddColumnToTable(strTable, strColumn, strColumnType))
                cout << "Error on adding a column " << strColumn << " with type " << strColumnType << " in table " << strTable << ".\n";

            bShowInfo = false;
            continue;
        }

        iPos = s.find("rename"); ///rename table with <old name> to a <new name>
        if (iPos >= 0)
        {
            stringstream ss(s);
            string strTmp, strOldName, strNewName;
            getline(ss, strTmp, ' ');
            getline(ss, strOldName, ' ');
            getline(ss, strNewName, ' ');

            if (!pDataBase->TableExists(strOldName))
            {
                cout << "No such Table" <<'\n';
            }
            else
            {
                if (pDataBase->TableExists(strNewName))
                {
                    cout << "Table with" << strNewName << " already exists" << '\n';
                }
                else
                {
                    if (!pDataBase->RenameTable(strOldName, strNewName))
                    {
                        cout << "Error with renaming table" << '\n';
                    }
                }
            }
            
            bShowInfo = false;
            continue;
        }


    } while (s != "exit");
}

IDataBase::~IDataBase()
{
    delete pDataBase;
}
