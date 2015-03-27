#include <iostream>
#include <QtSql>
using namespace std;
#include "test.h"
#include "mysqlquery.h"

Test::Test(QString str)
{
    Mysqlquery qry;
    qry.connect("localhost", "dndd", "dndddndd", "dndd");

    cout << str.toStdString() << endl;
}

Test::~Test()
{

}

