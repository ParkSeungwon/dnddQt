/*
 * vote.cc
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
#include "vote.h"

void Vote::setVote(string _field, int _number, string _votingId, int _votedFor, bool _secret)
{
	field = _field;
	number = _number;
	votingId = _votingId;
	votedFor = _votedFor;
	secret = _secret;
}

void Vote::show()
{
	cout << field << endl;
	cout << "게시물번호 : " << number << endl;
	cout << votingId << endl;
	cout << "기호 : " << votedFor << endl;
	cout << "공개여부 : " << secret << endl;
}
