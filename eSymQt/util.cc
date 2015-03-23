/*
 * util.cc
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

 
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;
#include "member.h"
#include "util.h"


string Util::itos(int i) {
	ostringstream os;
	os << i;
	return os.str();
}

bool Util::noSpace(string s)
{
    if(s.find(' ', 0) == string::npos) return true;
    else return false;
}

int Util::ctoi(char c) 
{
	return c - '0';
}

int Util::stoi(string s)
{
    char ar[10];
    strcpy(ar, s.c_str());
    return atoi(ar);
}

Level Util::ctoL(char c)
{
	switch (c - '0')
	{
	case 0 : return anonymous;
	case 1 : return registered;
    case 2 : return regular;
	case 3 : return representative;
	case 4 : return senior;
	case 5 : return root;
	default : throw 2;
	}
}

Level Util::itoL(int i)
{
	switch (i)
	{
	case 0 : return anonymous;
	case 1 : return registered;
    case 2 : return regular;
	case 3 : return representative;
	case 4 : return senior;
	case 5 : return root;
	default : throw 2;
    }
}

string Util::Ltos(Level _level)
{
	string s;
	switch (_level)
	{
	case 0 :
		s = "anonymous"; break;
	case 1 :
		s = "registered"; break;
    case 2 :
        s = "regular"; break;
	case 3 :
		s = "representative"; break;
	case 4 :
		s = "senior"; break;
	case 5 :
		s = "root"; break;
	}
	return s;
}

		
