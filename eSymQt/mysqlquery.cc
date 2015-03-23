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

#include <QSqlDatabase>

using namespace std;
#include "mysqlquery.h"


QSqlError Mysqlquery::myQuery(std::string str)
{
    sqlQuery.exec(str);
    record = sqlQuery.record();
    return qdb.lasterror();
}

bool Mysqlquery::connect(string host, string user, string pass, string database)
{
    qdb = QSqlDatabase::addDatabase("QMYSQL");
    qdb.setHostName(host);
    qdb.setDatabaseName(database);
    qdb.setUserName(user);
    qdb.setPassword(pass);
    return qdb.open();
}
