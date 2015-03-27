/*
 * mysqlvote.cc
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
#include <string>
using namespace std;
#include "member.h"
#include "mysqlquery.h"
#include "util.h"
#include "vote.h"
#include "mysqlvote.h"

MysqlVote::MysqlVote(Mysqlquery *qQuery)
{
	mysqlQuery = qQuery;
}

void MysqlVote::write()
{
	string query = "insert into Vote values ('";
	query += field + "', ";
	query += Util::itos(number) + ", '";
	query += votingId + "', ";
	query += Util::itos(votedFor) + ", ";
	query += Util::itos(secret) + ", now());";
    //cout << query << endl;
	mysqlQuery->myQuery(query);
}

int MysqlVote::findMan(VoteResult *vr, int count, string email, int start) 
{
	for(int i = start; i<count; i++) {
		if(vr[i].email == email) return i;
	}
	return count;
}

int MysqlVote::findMan(FollowTable *vr, int count, string email, int start)
{
	for(int i = start; i<count; i++) {
		if(vr[i].email == email) return i;
	}
	return count;
}


string MysqlVote::calculateVoteHtml(string _field, int _number, int option)
{
	long vOption[option+1][2];
	for (int m = 0; m <= option; m++) {
		vOption[m][0] = 0;
		vOption[m][1] = 0;
	}

	string query = "select * from (select * from Vote inner join (select email, name, level from Users order by date desc) as my_table_tmp  using (email) where level > 2 and field = '";
	query += _field + "' and num = " + Util::itos(_number);
	query += " order by date desc) as my_table_tmp group by email order by email;";
	//cout << query << endl;
	mysqlQuery->myQuery(query);
    int cRep = mysqlQuery->sqlQuery.size();
	VoteResult vrRepresent[cRep];
	int i = 0;
    while (mysqlQuery->sqlQuery.next()) {
        int emailcol = mysqlQuery->record.indexOf("email");
        int namecol = mysqlQuery->record.indexOf("name");
        int votedforcol = mysqlQuery->record.indexOf("votedfor");
        int datecol = mysqlQuery->record.indexOf("date");
        vrRepresent[i].email = mysqlQuery->sqlQuery.value(emailcol).toString().toStdString();
        vrRepresent[i].name = mysqlQuery->sqlQuery.value(namecol).toString().toStdString();
        vrRepresent[i].votedfor = mysqlQuery->sqlQuery.value(votedforcol).toBool();
        vrRepresent[i].date = mysqlQuery->sqlQuery.value(datecol).toString().toStdString();
		vrRepresent[i].secret = false;
		i++;
	}

	query = "select * from (select * from Follow order by date desc) as my_table_tmp group by follower order by email, follower;";
	//cout << query << endl;
	mysqlQuery->myQuery(query);
    int cFT  = mysqlQuery->sqlQuery.size();
	FollowTable fTable[cFT];
	i = 0;
    while (mysqlQuery->sqlQuery.next()) {
        int emailcol = mysqlQuery->record.indexOf("email");
        int followercol = mysqlQuery->record.indexOf("follower");
        int secretcol = mysqlQuery->record.indexOf("secret");
        fTable[i].email = mysqlQuery->sqlQuery.value(emailcol).toString().toStdString();
        fTable[i].follower = mysqlQuery->sqlQuery.value(followercol).toString().toStdString();
        fTable[i].secret = mysqlQuery->sqlQuery.value(secretcol).toBool();
		i++;
	}

	query = "select * from (select * from Vote inner join (select email, name, level from Users order by date desc) as my_table_tmp  using (email) where level < 3 and field = '";
	query += _field + "' and num = " + Util::itos(_number);
	query += " order by date desc) as my_table_tmp group by email order by email;";
	//cout << query << endl;
	mysqlQuery->myQuery(query);
    int cReg = mysqlQuery->sqlQuery.size();
	VoteResult vrRegistered[cReg];
	i = 0;
    while (mysqlQuery->sqlQuery.next()) {
        int emailcol = mysqlQuery->record.indexOf("email");
        int namecol = mysqlQuery->record.indexOf("name");
        int votedforcol = mysqlQuery->record.indexOf("votedfor");
        int datecol = mysqlQuery->record.indexOf("date");
        int secretcol = mysqlQuery->record.indexOf("secret");
        vrRegistered[i].email = mysqlQuery->sqlQuery.value(emailcol).toString().toStdString();
        vrRegistered[i].name = mysqlQuery->sqlQuery.value(namecol).toString().toStdString();
        vrRegistered[i].votedfor = mysqlQuery->sqlQuery.value(votedforcol).toInt();
        vrRegistered[i].date = mysqlQuery->sqlQuery.value(datecol).toString().toStdString();
        vrRegistered[i].secret = mysqlQuery->sqlQuery.value(secretcol).toBool();
		i++;
	}
	
	
	string result = "<div style=\"text-align: center\"><br /><h1>Votes by representatives & followers</h1><br />";
	result += "<table style = \"width:100%\" border = \"1\"><tr><td>email</td><td>name</td><td>votedfor</td><td>date</td></tr>";
	int j = 0, k = 0;
	for (i = 0; i < cRep; i++) {//Representatives
		result += "<tr bgcolor=\"grey\"><th>" + vrRepresent[i].email;
		result += "</th><th>" + vrRepresent[i].name + "</th><th>";
		result += Util::itos(vrRepresent[i].votedfor) + "</th><th>";
		result += vrRepresent[i].date + "</th></tr>";
		vOption[vrRepresent[i].votedfor][vrRepresent[i].secret]++;
		for(j = 0; j < cFT; j++) {//follower
			j = findMan(fTable, cFT, vrRepresent[i].email, j);
			if(j != cFT) {//representative have follower
				if(fTable[j].secret == 0) {//follow publicly
					result += "<tr><td>followers :</td><td>";
					result += fTable[j].follower + "</td><td>";
					k = findMan(vrRegistered, cReg, fTable[j].follower, 0);
					if(k != cReg) {//follower himself voted
						if(vrRegistered[k].secret == 0) //follower vote publicly
							result += Util::itos(vrRegistered[k].votedfor) +"</td>";
						else result += "?</td>";
						vOption[vrRegistered[k].votedfor][vrRegistered[k].secret]++;
						vrRegistered[k].votedfor = 0;//mark calculated vote
					}
					else {//no vote->follow secret 
						result += "=</td>";
						vOption[vrRepresent[i].votedfor][fTable[j].secret]++;
					}
					result += "<td></td></tr>";
				}
			}
		}
	}
	result += "</table></div><br /><div style=\"text-align: center\"><br /><hr><h1>Votes by registered</h1><br />";
	for(i = 0; i < cReg; i++ ) {
		if(vrRegistered[i].votedfor != 0) {
			if(vrRegistered[i].secret == 0) {
				result += vrRegistered[i].email + "(";
				result += Util::itos(vrRegistered[i].votedfor) + ") ";
				//if(i%5 == 4) result += "<br />";
			}
			vOption[vrRegistered[i].votedfor][vrRegistered[i].secret]++;
		}
	}

	result += "</div><br />";

	string table = "<!DOCTYPE html><div style=\"text-align: center\"><br /><h1>Total voting calculation</h1><br />";
	table += "<table style = \"width:100%\" border = \"1\"><tr><th></th><th>Open vote</th><th>private vote</th><th>total</th><th>win%</th></tr>";
	long total_vote = 0;
	for(i = 1; i <= option; i++) total_vote += vOption[i][0] + vOption[i][1];
	if(total_vote == 0) return "No vote was performed";
	for (i = 1; i <= option; i++) {
		table += "<tr><th>option" + Util::itos(i) +"</th><td>"+ Util::itos(vOption[i][0]);
		table += "</td><td>" + Util::itos(vOption[i][1]) + "</td><td>";
		table += Util::itos(vOption[i][0] + vOption[i][1]) + "</td><td>";
		table += Util::itos( (vOption[i][0] + vOption[i][1])*100/total_vote) + "%</td></tr>";
	}
	table += "</table></div><br />";
	
	string graph = "<div style=text-align:right><font size=2 color=white>";
	for(i = 1; i<=option; i++) {
		graph += "<table border=0 bgcolor=teal width=";
		graph += Util::itos(vOption[i][0]*100/total_vote) + "%><tr><td>";
		if(vOption[i][0]*100/total_vote > 20) 
			graph += "option" + Util::itos(i) + " open vote: ";
		graph += Util::itos(vOption[i][0]);
		graph += "</td></tr></table><table border=0 bgcolor=blue width=";
		graph += Util::itos((vOption[i][1]+vOption[i][0])*100/total_vote) + "%><tr><td>";
		if((vOption[i][1]+vOption[i][0])*100/total_vote > 20) 
			graph += "option" + Util::itos(i) + " total vote: ";
		graph += Util::itos(vOption[i][1]+vOption[i][0]) + "</td></tr></table><br />";
	}
	graph += "</font></div>";
	
	return table + graph +"<hr>"+ result;
}
