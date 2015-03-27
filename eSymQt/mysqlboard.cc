/*
 * mysqlboard.cc
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
#include <iostream>
using namespace std;
#include "member.h"
#include "comment.h"
#include "mysqlquery.h"
#include "mysqlboard.h"
#include "util.h"

Mysqlboard::Mysqlboard(Mysqlquery *qQuery)
{
	mysqlQuery = qQuery;
}

bool Mysqlboard::write(char option) //f,e만 유의
{
	if(option != 'f') {
		if(title == "Final notify." || title == "Final result.") title += ".";
	} else if(title == "Final notify.") {
		title = "Final result.";
	} else title = "Final notify.";
	if(option == 'f' || option == 'a') page++;//add page
	title = addBackSlash(title);
	text = addBackSlash(text);
	string str = "insert into " + field + " values (";
	str += Util::itos(number) + ", ";
	str += Util::itos(page) + ", '";
	str += getId() + "', '";
	str += title + "', '";
	str += text + "', ";
	if(option == 'e') str += "'" + getDate() + "', null);";
	else str += "now(), null);";
	//cout << str << endl;
	return mysqlQuery->myQuery(str);
}

string Mysqlboard::getTOC(string _field, int _num)
{
	setPage(_field, _num, 0);
	read();
	string s = "<h2>Level requirements & Voting options</h2>\n\nLevel higher than or equal to ";
	s += Util::Ltos(getRead());
	s += " can read this post.<br />\nLevel higher than or equal to ";
    s += Util::Ltos(getWrite()) + " can write pages to this post.<br />\n";
    s += "Level higher than or equal to " + Util::Ltos(getComment());
	s += " can attach comments to this post.<br />\nLevel higher than or equal to ";
    s += Util::Ltos(getVote()) + " can vote to this post.<br /><br>\n\n";
    s += "This post has " + Util::itos(getVotingOption()) + " voting options<br /><br />\n\n";
	
    string query = "select page, title from (select * from " + field;
    query += " order by date, edit desc) as my_table_tmp";
    query += " where num = " + Util::itos(number);
    query += " group by page;";
    mysqlQuery->myQuery(query);
    string toc = "\n<h2>Table of Contents</h2>\n\n";
    while(mysqlQuery->sqlQuery.next()) {
        int pagecol = mysqlQuery->record.indexOf("page");
        int titlecol = mysqlQuery->record.indexOf("title");
        toc += mysqlQuery->sqlQuery.value(pagecol).toString().toStdString() + ". ";
        toc += mysqlQuery->sqlQuery.value(titlecol).toString().toStdString() + "<br />\n";
    }
    return s + toc;
}

void Mysqlboard::read()
{
    if(mysqlQuery->sqlQuery.next()) {
		if(field == "") {
            setText(mysqlQuery->sqlQuery.value(1).toString().toStdString());
		} else {
            int numcol = mysqlQuery->record.indexOf("num");
            int titlecol = mysqlQuery->record.indexOf("title");
            int emailcol = mysqlQuery->record.indexOf("email");
            int contentscol = mysqlQuery->record.indexOf("contents");
            int datecol = mysqlQuery->record.indexOf("date");
            int pagecol = mysqlQuery->record.indexOf("page");
            setNumber(mysqlQuery->sqlQuery.value(numcol).toInt());
            setTitle(mysqlQuery->sqlQuery.value(titlecol).toString().toStdString());
            setId (mysqlQuery->sqlQuery.value(emailcol).toString().toStdString());
            setText (mysqlQuery->sqlQuery.value(contentscol).toString().toStdString());
            setDate (mysqlQuery->sqlQuery.value(datecol).toString().toStdString());
            setPages(mysqlQuery->sqlQuery.value(pagecol).toInt());
		}
        //show();
	}
}

size_t Mysqlboard::setPage(string _field, int _num, int _page)
{
	field = _field;
	number = _num;
    page = _page;
    string query;
    
	if(field == "") query = "show tables;";//field
    else if(_num == -1) {//목록
		query = "select * from " + field;
		query += " group by num order by num;";
	} else if(_page == -1) {//페이지수
        query = "select * from (select * from " + field;
        query += " order by date, edit desc) as my_table_tmp";
		query += " where num = " + Util::itos(number);
		query += " group by page;";
    } else {//일반적인 경우
        query = "select * from (";
		query += "select * from " + field;
		query += " where num = " + Util::itos(number);
		query += " and page = " + Util::itos(page);
		query += " order by date, edit desc)";
        query += " as my_table_tmp group by date, email;";
	} 
	//cout << query << endl;
    mysqlQuery->myQuery(query);
    return mysqlQuery->sqlQuery.size();
}

void Mysqlboard::showtables() {
	string query = "show tables;";
	mysqlQuery->myQuery(query);
}

string Mysqlboard::addBackSlash(string s) {
    int apo, i=0;
    while((apo = s.find_first_of('\'', i)) < s.length()) {
        if(s[apo-1] != '\\') {
            s.insert(apo, 1, '\\');
            i = apo + 2;
        } else i = apo + 1;
    }
    return s;
}

