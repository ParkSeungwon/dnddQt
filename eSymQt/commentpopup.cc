/*
 * commentpopup.cc
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
#include "commentpopup.h"
#include "interface.h"

CommentPopup::CommentPopup(char _option, string contents, string _date)
	: ok("ok"), cancel("cancel")
{
	set_title("Comment");
	set_default_size(500, 300);
	option = _option;
	date = _date;
	textview1.set_wrap_mode(Gtk::WRAP_CHAR);
	textview1.get_buffer()->set_text(contents);
	ok.signal_clicked().connect(sigc::mem_fun(*this, &CommentPopup::on_ok_clicked));
	cancel.signal_clicked().connect(sigc::mem_fun(*this, &CommentPopup::on_cancel_clicked));
	add(vbox1);
	vbox1.pack_start(textview1);
	vbox1.pack_end(hbox1, Gtk::PACK_SHRINK);
	//scwin1.add(textview1);
	//scwin1.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	hbox1.pack_start(ok);
	hbox1.pack_start(cancel);
	set_modal(true);
	set_position(Gtk::WIN_POS_CENTER_ON_PARENT);
	show_all_children();
}

void CommentPopup::on_ok_clicked()
{
	extern CommentInterface *pInterface;
	string s = textview1.get_buffer()->get_text();
	string t = "코멘트임.";
	pInterface->write(option, t, s, date);
	std::cout << t << std::endl;
	hide();
}


