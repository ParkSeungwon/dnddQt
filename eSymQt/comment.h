/*
 * comment.h
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

class Comment
{
private:
	string id;
	string date;
	
protected:
	string text;
	string name;
	
public:
	//setter & getter
	void setText(string s){text = s;}
	string getText() {return text;}
	string getId() {return id;}
	void setId(string s)	{id = s;}
	string getName() {return name;}
	void setName(string s) {name = s;}
	string getDate() {return date;}
	void setDate(string s) {date = s;}
}; 

class Board : public Comment
{
private:
	
protected:
	string field;
	string title;
	int number;
	int page;
    string spare;
		
public:
	//게시물의 설정을 텍스트의 내용으로 저장
	void configToText(int _read, int _write, int _comment, int _vote, bool _inturn, string _ids, int _response_term, int votingOption);
	bool getIntern();
	Level getWrite();
	Level getRead();
	Level getComment();
	Level getVote();
	int getResponseTerm();
	int getVotingOption();//1~9
	void show();
	
	//setter & getter
	int getPage() {return page;}
	void setField(string s) {field = s;}
    string getField() {return field;}
    void setTitle(string s) {title = s;}
    void setNumber(int n) {number = n;}
    void setPages(int n) {page = n;}
    void setName(string s) {name = s;}
    string getTitle() {return title;}
    int getNumber() {return number;}
    string getSpare() {return spare;}
    void setSpare(string s) {spare = s;}
};
