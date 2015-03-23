/*
 * votepopup.cc
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
#include <gtkmm.h>
#include "interface.h"
#include "votepopup.h"
#include "member.h"
#include "util.h"

VotePopup::VotePopup(int option) :
	check("secret"), frame1("choose options"), button1("Vote"), button2("Exit")
{
	which = 0;
	radioButton = new Gtk::RadioButton[option];
	Gtk::RadioButton::Group group;
	group = radioButton[0].get_group();
	for (int i = 1; i < option; i++) {
		radioButton[i].set_group(group);
	}
	for (int i = 0; i < option; i++) {
		radioButton[i].set_label("option : " + Util::itos(i+1));
		radioButton[i].signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &VotePopup::on_radio_click), i));
		vbox2.pack_start(radioButton[i]);
	}

	add(vbox1);
	vbox1.pack_start(check);
	vbox1.pack_start(frame1);
	frame1.add(vbox2);
	vbox1.pack_start(hbox1);
	hbox1.pack_start(button1);
	hbox1.pack_start(button2);
	vbox1.pack_start(label1);
	button1.signal_clicked().connect(sigc::mem_fun(*this, &VotePopup::on_vote_click));
	button2.signal_clicked().connect(sigc::mem_fun(*this, &VotePopup::on_exit_click));
	set_modal(true);
	set_position(Gtk::WIN_POS_CENTER_ON_PARENT);
	show_all_children();
}

void VotePopup::on_vote_click()
{
	extern CommentInterface *pInterface;
	if(pInterface->votedFor(which + 1, check.get_active()) <= 0)
		label1.set_label("representatives cannot vote secretly");
	else hide();
}
