/*
 * commentpopup.h
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


class CommentPopup : public Gtk::Window
{
protected:
	char option;
	string date;
	Gtk::TextView textview1;
	Gtk::Button ok, cancel;
	Gtk::VBox vbox1;
	Gtk::HBox hbox1;
	//Gtk::ScrolledWindow scwin1;
	
	void on_ok_clicked();
	void on_cancel_clicked(){hide();}
	
public:
	CommentPopup(char option, string contents, string date);//option 'e' or 'n'
};

