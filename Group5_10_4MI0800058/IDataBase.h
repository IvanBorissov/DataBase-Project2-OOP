#pragma once
#include "IDataBase.h"
#include "TDataBase.h"
#include <iostream>

class IDataBase
{
private:
	TDataBase* pDataBase;
public:
	IDataBase(std::string PathToDB);
	void Run();
	~IDataBase();
};