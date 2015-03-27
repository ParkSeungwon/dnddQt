/*
 * mysqlmember.cc
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
using namespace std;
#include "member.h"
#include "mysqlquery.h"
#include "mysqlmember.h"
#include "util.h"

MysqlMember::MysqlMember(Mysqlquery *qQuery)
{
	mysqlQuery = qQuery;
}

void MysqlMember::write() 
{
	string query = "insert into Users values('";
	query += email + "', password('";
	query += password + "'), ";
	query += Util::itos(level) + ", '";
	query += name + "', '";
	query += tel + "', now());";
	
	mysqlQuery->myQuery(query);
}

bool MysqlMember::read(string _id) 
{
	string query = "select * from Users where email = '";
	query += _id + "';";
	mysqlQuery->myQuery(query);
    if(mysqlQuery->sqlQuery.next()) {
        email = _id;
        int passcol = mysqlQuery->record.indexOf("password");
        int namecol = mysqlQuery->record.indexOf("name");
        int levelcol = mysqlQuery->record.indexOf("level");
        int telcol = mysqlQuery->record.indexOf("tel");
        password = mysqlQuery->sqlQuery.value(passcol).toString().toStdString();
        level = (Level)mysqlQuery->sqlQuery.value(levelcol).toInt();
        name = mysqlQuery->sqlQuery.value(namecol).toString().toStdString();
        tel = mysqlQuery->sqlQuery.value(telcol).toString().toStdString();
        //follow = res->getString("follow");
        return true;
    }
    else return false;
}

bool MysqlMember::login(string user, string pass)
{
    string query = "select * from (select * from (select * from Users where email = '";
    query += user + "' order by date desc) as my_table_tmp group by email) as my_table_tmp" ;
    query +=  " where password=password('" + pass + "');";
    //std::cout << query << std::endl;
    mysqlQuery->myQuery(query);
    if(mysqlQuery->sqlQuery.next()) {
        int passcol = mysqlQuery->record.indexOf("password");
        int namecol = mysqlQuery->record.indexOf("name");
        int levelcol = mysqlQuery->record.indexOf("level");
        int telcol = mysqlQuery->record.indexOf("tel");
        int emailcol = mysqlQuery->record.indexOf("email");
        email = mysqlQuery->sqlQuery.value(emailcol).toString().toStdString();
        password = mysqlQuery->sqlQuery.value(passcol).toString().toStdString();
        level = (Level)mysqlQuery->sqlQuery.value(levelcol).toInt();
        name = mysqlQuery->sqlQuery.value(namecol).toString().toStdString();
        tel = mysqlQuery->sqlQuery.value(telcol).toString().toStdString();
        //follow = res->getString("follow");
        query = "select email from (select * from Follow where follower = '";
        query += email + "' order by date desc) as my_table_tmp group by follower;";
        if(mysqlQuery->myQuery(query) && mysqlQuery->sqlQuery.next()) {
            int emailcol = mysqlQuery->record.indexOf("email");
            follow = mysqlQuery->sqlQuery.value(emailcol).toString().toStdString();
        }
        return true;
    } else {
        email = "anony@anony";
        level = anonymous;
        name = "anonymous";
        password = "anony";
        return false;
    }
}

bool MysqlMember::exist(string _email)
{//almost same as read
	string query = "select email from Users where email = '";
	query += _email + "';";
	mysqlQuery->myQuery(query);
    if(mysqlQuery->sqlQuery.next()) return true;
	else return false;
}

bool MysqlMember::writeFollow(string email, string follower, bool secret)
{
    string query = "insert into Follow values('";
    query += email + "', '" + follower + "', " + Util::itos(secret) + ", now());";
    //std::cout << query << std::endl;
    if(mysqlQuery->myQuery(query)) {
        follow = email;//return
        return true;
    }
    else return false;
}
