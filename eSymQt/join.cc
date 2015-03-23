/*
 * join.cc
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
#include "join.h"

JoinPopup::JoinPopup()
    :label1("email :"), label2("Nickname :"), label3("tel  :"), label4("password :"),
     label5("retype"), button1("Join"), button2("Exit"), label_message("---")
{
    set_title("Join");
    add(vbox1);
    vbox1.pack_start(hbox1);
    vbox1.pack_start(hbox2);
    vbox1.pack_start(hbox3);
		 
    vbox1.pack_end(label_message);
    vbox1.pack_end(hbox_button);
	vbox1.pack_end(hbox5);
	vbox1.pack_end(hbox4);
		 
    hbox1.pack_start(label1);
    hbox1.pack_start(entry1);
    hbox2.pack_start(label2);
    hbox2.pack_start(entry2);
    hbox3.pack_start(label3);
    hbox3.pack_start(entry3);
    
    hbox4.pack_start(label4);
    hbox4.pack_start(entry4);
    hbox5.pack_start(label5);
    hbox5.pack_start(entry5);
	hbox_button.pack_start(button1);
	hbox_button.pack_start(button2);
		 
    set_position(Gtk::WIN_POS_CENTER_ON_PARENT);
	entry4.set_visibility(false);
	entry5.set_visibility(false);
	entry1.set_max_length(30);
	entry2.set_max_length(30);
	entry3.set_max_length(30);
	entry4.set_max_length(30);
	entry5.set_max_length(30);
    label1.set_size_request(100);
    label2.set_size_request(100);
    label3.set_size_request(100);
    label4.set_size_request(100);
    label5.set_size_request(100);
    set_modal(true);

    button1.signal_clicked().connect(sigc::mem_fun(*this, &JoinPopup::on_join_click));
    button2.signal_clicked().connect(sigc::mem_fun(*this, &JoinPopup::on_exit_click));
    
    show_all_children();
}

void JoinPopup::on_join_click()
{
    extern CommentInterface *pInterface;
    string e = entry1.get_text();
    string p = vGetCurPass();
    string n = entry2.get_text();
    string t = entry3.get_text();
    string np = vGetNewPass();
	if(entry4.get_text() != entry5.get_text()) {
		label_message.set_label("password does not match!");
	}
    else if(pInterface->join(e, p, n, t, np)) label_message.set_label("Done! click Exit to login.");
    else label_message.set_label("email exists!");
}

string JoinPopup::vGetNewPass() {
    return "";
}
string JoinPopup::vGetCurPass() {
	return entry4.get_text();
}
string ChangeAccount::vGetCurPass() {
	return entry6.get_text();
}
string ChangeAccount::vGetNewPass() {
    return entry4.get_text();
}

ChangeAccount::ChangeAccount(string email, string name, string tel)
    : label6("current password:")
{
    set_title("change account information");
    button1.set_label("change");
	label4.set_label("new password:");
    entry1.set_text(email);
    entry3.set_text(tel);
    entry2.set_text(name);
    vbox1.pack_start(hbox6);
    hbox6.pack_start(label6);
    hbox6.pack_start(entry6);
    entry6.set_visibility(false);
	entry6.set_max_length(30);
    label6.set_size_request(100);
    entry1.set_editable(false);
    //set_position(Gtk::WIN_POS_CENTER);
    //set_modal(true);
    show_all_children();
}
