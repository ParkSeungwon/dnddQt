/*
 * mysqlquery.cc
 * This file is part of dndd
 *
 * Copyright (C) 2015 - Seungwon Park
 *
 * dndd is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * dndd is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dndd. If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtSql>
#include <QString>
using namespace std;
#include "mysqlquery.h"


bool Mysqlquery::myQuery(string str)
{
    bool ok = sqlQuery.exec(QString::fromStdString(str));
    record = sqlQuery.record();
    return ok;
    //record = sqlQuery.record();
    //return qdb.lasterror();
}

bool Mysqlquery::connect(string host, string user, string pass, string database)
{
    qdb = QSqlDatabase::addDatabase("QMYSQL");
    qdb.setHostName(QString::fromStdString(host));
    qdb.setDatabaseName(QString::fromStdString(database));
    qdb.setUserName(QString::fromStdString(user));
    qdb.setPassword(QString::fromStdString(pass));
    return qdb.open();
}
