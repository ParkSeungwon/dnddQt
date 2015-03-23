/*
 * newbook.cc
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
#include "newbook.h"
#include "interface.h"

NewBook::NewBook()
    : label1("read level"), label2("write level"), label3("comment level"), 
      label4("vote level"), label6("voting option"), button1("Create"), button2("Exit"),
      scale1(0.0, 6.0, 1.0), scale2(1.0, 6.0, 1.0), scale3(1.0, 6.0, 1.0),
      scale4(1.0, 6.0, 1.0), scale6(2.0, 10.0, 1.0), label7("Title :"),
      label9("number : Level\n 0 : anonymous\n 1 : registered\n 2 : regular\n 3 : representative\n 4 : senior\n 5 : root")
{
    set_title("New Book privilege options");
    add(vbox1);
    vbox1.set_size_request(300, -1);
    vbox1.pack_start(hbox8);
    hbox8.pack_start(label7, Gtk::PACK_SHRINK);
    hbox8.pack_start(entry1);
    vbox1.pack_start(label9, Gtk::PACK_SHRINK);
    vbox1.pack_start(hbox1);
    vbox1.pack_start(hbox2);
    vbox1.pack_start(hbox3);
    vbox1.pack_start(hbox4);
    vbox1.pack_start(hbox6);
    vbox1.pack_start(hbox7);
    hbox1.pack_start(label1, Gtk::PACK_SHRINK);
    hbox2.pack_start(label2, Gtk::PACK_SHRINK);
    hbox3.pack_start(label3, Gtk::PACK_SHRINK);
    hbox4.pack_start(label4, Gtk::PACK_SHRINK);
    hbox6.pack_start(label6, Gtk::PACK_SHRINK);
    label1.set_size_request(100);
    label2.set_size_request(100);
    label3.set_size_request(100);
    label4.set_size_request(100);
    label6.set_size_request(100);
    label7.set_size_request(50);
    hbox1.pack_start(scale1);
    hbox2.pack_start(scale2);
    hbox3.pack_start(scale3);
    hbox4.pack_start(scale4);
    hbox6.pack_start(scale6);
    hbox7.pack_start(button1);
    hbox7.pack_start(button2);
    button1.signal_clicked().connect(sigc::mem_fun(*this, &NewBook::click_button1));
    button2.signal_clicked().connect(sigc::mem_fun(*this, &NewBook::click_button2));
    set_modal(true);
	set_position(Gtk::WIN_POS_CENTER_ON_PARENT);
    show_all_children();
}

void NewBook::click_button1()
{
    extern CommentInterface *pInterface;
    pInterface->create_new_book(scale1.get_value(), scale2.get_value(),
                                scale3.get_value(), scale4.get_value(), true,
                                "", 0,
                                scale6.get_value(), entry1.get_text() );
    hide();
}
