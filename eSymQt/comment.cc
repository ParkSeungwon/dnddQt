/*
 * comment.cc
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

 

#include <iostream>
using namespace std;
#include "member.h"
#include "comment.h"
#include "util.h"
#include <cstdlib>

void Board::configToText(int _read, int _write, int _comment, int _vote, bool _inturn, string _ids, int _response_term, int _votingOption) 
{
	text = Util::itos(_read) + Util::itos(_write) +  Util::itos(_comment);
	text += Util::itos(_vote) + Util::itos(_inturn) + Util::itos(_votingOption);
	text += Util::itos(_response_term) + "\n";
	text += _ids;
}

Level Board::getRead() 
{
	return Util::ctoL(text[0]);
}
Level Board::getWrite()
{
	return Util::ctoL(text[1]);
}
Level Board::getComment()
{
	return Util::ctoL(text[2]);
}
Level Board::getVote()
{
	return Util::ctoL(text[3]);
}
bool Board::getIntern() 
{
	return Util::ctoi(text[4]);
}
int Board::getVotingOption()
{
	return Util::ctoi(text[5]);
}

int Board::getResponseTerm()
{
	int i = 6;
	string s = "";
	while (text[i] != '\n') {
		s += text[i++];
	}
	return atoi(s.c_str());
}

void Board::show()
{
	cout << "id : " << getId() << endl;
	cout << "date : " << getDate() << endl;
	cout << "게시판 : " << field << endl;
	cout << "제목 : " << title << endl;
	cout << "게시물번호 : " << number << endl;
	cout << "페이지 : " << page << endl;
	cout << "내용 : " << text << endl;
}
