/*
 * mainform.cc
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

#include "main.h"

CommentInterface *pInterface;

GtkMainForm::GtkMainForm(int argc, char *argv[]) :
    item1("Database"), item2("Help"), subitem11("Connect"), subitem12("Option"),
    subitem13("Quit"), subitem21("Tutorial"),subitem22("Manual"),subitem23("About"),
    viewport1(*scrolledWindow2.get_hadjustment(), *scrolledWindow2.get_vadjustment()),
	button1("Edit complete. Write to Database."), label1("Welcome!", Gtk::ALIGN_CENTER),
	board(qQuery), member(qQuery), vote(qQuery)
{
	if(argc >= 3) {
		user = argv[1];
		pass = argv[2];
	} else {
		user = "dndd";
		pass = "dndddndd";
	}
    curLev = 1;
    frame = NULL; label = NULL; button = NULL; hBox = NULL;
    
	menuBar1Setup();
	toolbar1Setup();
    
	webview = auto_ptr<GtkWidget>(webkit_web_view_new());
	scrolledWindow1.add(*Glib::wrap(webview.get()));
    viewport1.set_resize_mode(Gtk::RESIZE_PARENT);
	
	set_title("Discussion & Democratic Decision making");
	set_default_size(1350,900);
	add(vBox1);
	vBox1.pack_start(menuBar1, Gtk::PACK_SHRINK);
	vBox1.pack_start(hBox1);
	
	hBox1.pack_start(vBox2, Gtk::PACK_EXPAND_WIDGET);
	hBox1.pack_start(scrolledWindow2, Gtk::PACK_SHRINK);
	scrolledWindow2.set_size_request(350);
	vBox2.pack_start(hBox3, Gtk::PACK_SHRINK);
    hBox3.pack_start(label2, Gtk::PACK_SHRINK);
	hBox3.pack_start(entry1);
	hBox3.pack_start(label5, Gtk::PACK_SHRINK);
	hBox3.pack_start(eventbox1, Gtk::PACK_SHRINK);
	eventbox1.add(label3);
	eventbox1.set_events(Gdk::BUTTON_PRESS_MASK);
	eventbox1.signal_button_press_event().connect(sigc::mem_fun(*this, &GtkMainForm::change_account));
	eventbox1.set_tooltip_text("change password & personal info");
   
	//Notebook
	vBox2.pack_start(notebook);
	notebook.append_page(scrolledWindow1, "Html view");
	notebook.append_page(vBox5, "Text view");
	notebook.signal_switch_page().connect(sigc::mem_fun(*this, &GtkMainForm::switch_page));
	vBox5.pack_start(scwin3);
	scwin3.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	scwin3.add(textView1);
	text_font.set_size(12 * PANGO_SCALE);
	title_font.set_size(14 * PANGO_SCALE);
	title_font.set_family("serif,monospace bold italic condensed 14");
	textView1.modify_font(text_font);
	entry1.modify_font(title_font);

	textView1.set_wrap_mode(Gtk::WRAP_WORD);
	vBox5.pack_start(button1, Gtk::PACK_SHRINK);

	vBox2.pack_start(hBox2, Gtk::PACK_SHRINK);
	hBox2.pack_start(label1, Gtk::PACK_SHRINK);
    label1.set_line_wrap_mode(Pango::WRAP_CHAR);
    label1.set_line_wrap();
	label1.set_alignment(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);
	label1.set_size_request(150);
	hBox2.pack_start(entry2, Gtk::PACK_SHRINK);
	entry2.set_size_request(50);
	entry2.set_activates_default(true);
	entry2.signal_activate().connect(sigc::mem_fun(*this, &GtkMainForm::on_toolbar_go));
    hBox2.pack_start(label4, Gtk::PACK_SHRINK);
	hBox2.pack_end(toolbar1);
	
    scrolledWindow2.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
	scrolledWindow2.add(viewport1);
	viewport1.add(vBox4);
	vBox4.set_spacing(5);
	vBox4.set_size_request(50);
    for (int i = 0; i <= 15 ; i++) {
        toolbar1.get_nth_item(i)->set_sensitive(false);
    }
	button1.set_sensitive(false);
	button1.signal_clicked().connect(sigc::mem_fun(*this, &GtkMainForm::on_button1_clicked));
	set_position(Gtk::WIN_POS_CENTER);
	show_all_children();
	on_menu_manual();
}

GtkMainForm::~GtkMainForm()
{
	freeComments();
}

void GtkMainForm::switch_page(GtkNotebookPage*, guint page_num)
{
	if(page_num == 0) webkit_web_view_load_html_string(WEBKIT_WEB_VIEW(webview.get()), textView1.get_buffer()->get_text().c_str(), "www.naver.com");
}

void GtkMainForm::freeComments()
{
    if(frame != NULL) {
		delete[] frame; frame = NULL;
	}
	if(button != NULL) {
        delete[] button; button = NULL;
	}	
    if(label != NULL) {
	    delete[] label; label = NULL;
	}
	if(hBox != NULL) {
		delete[] hBox; hBox = NULL;
	}
}

bool GtkMainForm::openConnection(string host, string _user, string _pass, string db)
{
	if(qQuery.connect(host, user, pass, db)) {
        member.login(_user, _pass);
        commentSetup("", 0, 0);
        label3.set_markup(" || <b>" + member.getName() + "</b>, <b>" + Util::Ltos(member.getLevel()) + "</b>");
        return true;
    }
    else return false;
}

int GtkMainForm::commentSetup(string field, int num, int page)
{
    maxPage = board.setPage(field, num, -1) - 1;
    curPage = page;
    if(field == "") {
        label1.set_label("Choose a bulletin board to enter.");
        curLev = 1;
    }
    else if (num == -1) {
        label1.set_label("Choose a post.");
        curLev = 2;
    }
    else {
        label1.set_label("Book Mode");
        entry2.set_text(Util::itos(page));
        label4.set_label("/" + Util::itos(maxPage));
        curLev = 3;
		toc = board.getTOC(board.getField(), board.getNumber());//change the board
    }
    if(num > 0) label2.set_label(field + " : " + Util::itos(num) + ".");
    else label2.set_label(field + " : ");
    
    //필드가 ""이면 게시판 테이블을 처리하고, num이 -1이면 목록을 보여준다..
    //page가 -1이면 페이지수를 리턴함.
    //이외의 경우는 일반적인 댓글이 달린 페이지를 보여준다.
	int count = board.setPage(field, num, page);//게시물 번호 num, 페이지 page의 결과의 행수를 리턴함.
	board.read();
	if (num > 0 && page >= 0) {
        if(page != 0) {
			string s = board.getText();
			textView1.get_buffer()->set_text(s);
			if(s.find_first_of('<', 0) < 10) notebook.set_current_page(0);
			else notebook.set_current_page(1);
			webkit_web_view_load_html_string(WEBKIT_WEB_VIEW(webview.get()), s.c_str(), "www.naver.com");
		}
        else {
            textView1.get_buffer()->set_text(toc);
			notebook.set_current_page(0);
			webkit_web_view_load_html_string(WEBKIT_WEB_VIEW(webview.get()), toc.c_str(), "www.naver.com");
        }
        label5.set_markup(" article by " + board.getId() + " <small><i>on " + board.getDate() + "</i></small>");
        entry1.set_text(board.getTitle());
		count--;
		board.read();
	}
	
	freeComments();	//should do this earlier than next line
    label = new Gtk::Label[count];
    frame = new Gtk::Frame[count];
	button = new Gtk::Button[count];
    hBox = new Gtk::HBox[count];
    
	for(int i = 0; i < count; i++) {
        string sbind;//bind args
        if(field == "") {
            string s = board.getText();
            while(s == "Users" || s == "Vote" || s == "Follow") {
                board.read();
                s = board.getText();
                count--;
            }
            label[i].set_label(s);
            sbind = s;
    	} else if (num == -1){
			frame[i].set_label(Util::itos(board.getNumber()) );
			label[i].set_label(board.getTitle());
            sbind = Util::itos(board.getNumber());
		} else {
			frame[i].set_label(board.getId());
			label[i].set_markup(board.getText() + "\n<i><small>\t\ton " + board.getDate() + "</small></i>");
            sbind = board.getId() + " " + board.getDate() + "\n" + board.getText();
		}
        
        label[i].set_use_markup(true);
        label[i].set_line_wrap_mode(Pango::WRAP_CHAR);
       	label[i].set_line_wrap();
       	label[i].set_justify(Gtk::JUSTIFY_FILL);
        label[i].set_size_request(290);
    
        button[i].set_label(">");
        vBox4.pack_start(frame[i], Gtk::PACK_SHRINK);
		frame[i].add(hBox[i]);
        hBox[i].pack_start(label[i]);
        hBox[i].pack_end(button[i], Gtk::PACK_SHRINK);
              
        button[i].signal_clicked().connect( sigc::bind<Glib::ustring>(sigc::mem_fun(*this, &GtkMainForm::comment_press), sbind.c_str()) );
		board.read();
	}
    setSensitive();
    this->show_all_children();
    return count;
}

int GtkMainForm::setSensitive()
{
    for (int i = 0; i <= 15 ; i++) {
        toolbar1.get_nth_item(i)->set_sensitive(false);
    }
	button1.set_sensitive(false);

    Level l = member.getLevel();

    if(curLev != 1) toolbar1.get_nth_item(2)->set_sensitive(true);//upper
    if(curLev == 2 && l > anonymous)
        toolbar1.get_nth_item(8)->set_sensitive(true);//new book
    if(curLev == 3) {
        toolbar1.get_nth_item(0)->set_sensitive(true);//go
        toolbar1.get_nth_item(14)->set_sensitive(true);//progress
        if(l > anonymous && l < representative)
            toolbar1.get_nth_item(12)->set_sensitive(true);//follow

        board.setPage(board.getField(), board.getNumber(), 0);
        board.read();
        Level w = board.getWrite();
        Level v = board.getVote();
        Level c = board.getComment();
        string e = board.getId();
        if(l >= c) toolbar1.get_nth_item(10)->set_sensitive(true);//comment
        if(l >= v) toolbar1.get_nth_item(13)->set_sensitive(true);//vote
        board.setPage(board.getField(), board.getNumber(), curPage);
        board.read();
        
        if (curPage == maxPage && l >= w && board.getTitle() != "Final result." && board.getTitle() != "Final notify.")
            toolbar1.get_nth_item(9)->set_sensitive(true);//add page
        if (curPage == maxPage && l >= w && member.getEmail() == e) {
            if(board.getTitle() != "Final result.") {
                toolbar1.get_nth_item(15)->set_sensitive(true);//finalize page
                if(board.getTitle() == "Final notify.") 
                    toolbar1.get_nth_item(15)->set_tooltip_text("Finalize");
                else toolbar1.get_nth_item(15)->set_tooltip_text("Final notify");
            }
        }
        if (curPage < maxPage) {//next,last
            toolbar1.get_nth_item(5)->set_sensitive(true);
            toolbar1.get_nth_item(6)->set_sensitive(true);
        }
        if(curPage > 0) {//previous, first
            toolbar1.get_nth_item(3)->set_sensitive(true);
            toolbar1.get_nth_item(4)->set_sensitive(true);
            if(e == member.getEmail()) {
                string s = board.getTitle();
                if(s != "Final notify." && s != "Final result.")
					button1.set_sensitive(true);
            }
        }
    }
    
    return 0;
}

bool GtkMainForm::join(string email, string pass, string name, string tel, string newpass)
{
	if(newpass == "") {//join
		if(Member::checkValidEmail(email) && !member.exist(email) &&
		   Util::noSpace(email) && Util::noSpace(pass)) {
			member.setInfo(email, pass, registered, name, tel);
			member.write();
			return true;
		}
	} else if(member.login(email, pass) && Util::noSpace(newpass)) {//changeaccount
			member.setInfo(email, newpass, registered, name, tel);
			member.write();
			member.login(email, newpass);
			return true;
	}
	return false;
}

bool GtkMainForm::change_account(GdkEventButton *event)
{
	if(member.getLevel() > anonymous) {
		changeAccount = auto_ptr<ChangeAccount>(new ChangeAccount(member.getEmail(), member.getName(), member.getTel()));
		changeAccount->set_transient_for(*this);
		changeAccount->show();
		return true;
	}
	else return false;
}

int GtkMainForm::create_new_book(int r, int w, int c, int v, bool turn, string ids,
                                  int respons, int options, string title)
{
    board.configToText(r, w, c, v, turn, ids, respons, options);
    board.setTitle(title);
    board.setPages(0);
    board.setName(member.getName());
    int i = board.setPage(board.getField(), -1, 0) +1;
    board.setNumber(i);
    board.setId(member.getEmail());
    board.write('n');
    commentSetup(board.getField(), i, 0);
    return i;
}

void GtkMainForm::comment_press(Glib::ustring& s)
{
    if(curLev == 3) {//popupId();
        string txt = s;
        int space = s.find_first_of(' ', 0);
		int newline = s.find_first_of('\n', space);
        int length = s.length();
        char date[30], id[30];
        s.copy(date, newline - space, space+1);
        date[newline - space] = '\0';
		s.copy(id, space, 0);
		id[space] = '\0';
        txt.erase(0, newline+1);
        if(member.getEmail() == id) {
			commentpopup = auto_ptr<CommentPopup>(new CommentPopup('e', txt, date));  
			commentpopup->set_transient_for(*this);
			commentpopup->show();
        }
        else if(member.getLevel() > anonymous && member.getLevel() < representative) {
            followPopup = auto_ptr<FollowPopup>(new FollowPopup);
            followPopup->entry2.set_text(id);
            followPopup->label3.set_label("currently following " + member.getFollow());
            followPopup->set_transient_for(*this);
            followPopup->show();
        }
        else label1.set_label("Only registered, regular can follow");
    }
	else if(curLev == 1) {
		commentSetup(s, -1, 0);
		curField = s;
	}
	else if(curLev == 2) {
		curNumber = Util::stoi(s);
        board.setPage(curField, curNumber, 0);
        board.read();
        if(member.getLevel() >= board.getRead()) {
			toc = board.getTOC(curField, curNumber);
            commentSetup(curField, curNumber, 0);
		}
        else label1.set_label("not enough level");
    }
}

int GtkMainForm::write(char option, string title, string text, string date)
{
	if(option == 'e') board.setDate(date);
	board.setId(member.getEmail());
    board.setText(text);//already set member data before call
    board.setTitle(title);//so just set what has changed
	board.setPages(curPage);
    board.write(option);//'a'->automatically increase page
    return commentSetup(board.getField(), board.getNumber(), curPage);//auto
}

int GtkMainForm::votedFor(int option, bool secret)
{
    Level l = member.getLevel();
    if(l >= representative && secret == true) return -1;//representatives cannot vote secretly
    vote.setVote(board.getField(), board.getNumber(), member.getEmail(), option, secret);
    vote.write();
    label1.set_label("voted for " + Util::itos(option));
    return l;
}

int GtkMainForm::followID(string s, bool secret)
{
    if(member.getLevel() == anonymous) return -1;//not logged in
    int i = 0;
    string e = member.getEmail();
    if(member.read(s)) {
        i = member.getLevel();
        if(i >= 3) member.writeFollow(member.getEmail(), e, secret);
        member.read(e);//return back
    }
    return i;
}



