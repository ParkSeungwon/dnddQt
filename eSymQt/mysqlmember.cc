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

 
#include <QtSql/QSqlDatabase>
using namespace std;
#include "member.h"
#include "mysqlquery.h"
#include "mysqlmember.h"
#include "util.h"

void MysqlMember::write() 
{
	string query = "insert into Users values('";
	query += email + "', password('";
	query += password + "'), ";
	query += Util::itos(level) + ", '";
	query += name + "', '";
	query += tel + "', now());";
	
	myQuery(query);
}

bool MysqlMember::read(string _id) 
{
	string query = "select * from Users where email = '";
	query += _id + "';";
	myQuery(query);
    if(sqlQuery.next()) {
        email = _id;
        password = sqlQuery.value("password").toString();
        level = (Level)sqlQuery.value("level").toInt();
        name = sqlQuery.value("name").toString();
        tel = sqlQuery.value("tel").toString();
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
    myQuery(query);
    if(sqlQuery.next()) {
        email = sqlQuery.value("email").toString();
        password = sqlQuery.value("password").toString();
        level = sqlQuery.value("level").toInt();
        name = sqlQuery.value(record.indexOf("name")).toString();
        tel = sqlQuery.value(record.indexOf("tel")).toString();
        //follow = res->getString("follow");
        query = "select email from (select * from Follow where follower = '";
        query += email + "' order by date desc) as my_table_tmp group by follower;";
        if(myQuery(query) && sqlQuery.next()) follow = sqlQuery.value("email").toString();
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
	myQuery(query);
    if(sqlQuery.next()) return true;
	else return false;
}

bool MysqlMember::writeFollow(string email, string follower, bool secret)
{
    string query = "insert into Follow values('";
    query += email + "', '" + follower + "', " + Util::itos(secret) + ", now());";
    //std::cout << query << std::endl;
    if(myQuery(query)) {
        follow = email;//return
        return true;
    }
    else return false;
}
