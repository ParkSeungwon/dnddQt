/*
 * main.cc
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

int main(int argc, char *argv[])
{
	Gtk::Main kit(argc, argv);
	GtkMainForm form(argc, argv);
	extern CommentInterface *pInterface;
	pInterface = &form;
	kit.run(form);
    return 0;
}

void GtkMainForm::toolbar1Setup()
{
	toolbar1.set_toolbar_style(Gtk::TOOLBAR_BOTH);
    
    Gtk::ToolButton* item = Gtk::manage(new Gtk::ToolButton("Go!"));
	item->set_icon_name("revert");
	item->set_is_important(false);
    item->set_tooltip_text("goto a page");
    toolbar1.append(*item);
    item->signal_clicked().connect( sigc::mem_fun(*this, &GtkMainForm::on_toolbar_go) );

    toolbar1.append( *(Gtk::manage(new Gtk::SeparatorToolItem)) );

	item = Gtk::manage(new Gtk::ToolButton("upper"));
    item->set_use_underline();
	item->set_is_important(false);
    item->set_icon_name("go-up");
    item->set_tooltip_text("go upper level");
    item->set_homogeneous(false);
    toolbar1.append(*item);
    item->signal_clicked().connect( sigc::mem_fun(*this, &GtkMainForm::on_toolbar_upper) );
    
	item = Gtk::manage(new Gtk::ToolButton("first"));
    item->set_use_underline();
	item->set_is_important(false);
    item->set_icon_name("go-first");
    item->set_tooltip_text("goto first page");
    item->set_homogeneous(false);
    toolbar1.append(*item);
    item->signal_clicked().connect( sigc::mem_fun(*this, &GtkMainForm::on_toolbar_first) );
    
    item = Gtk::manage(new Gtk::ToolButton("previous"));
    item->set_use_underline();
	item->set_is_important(false);
    item->set_icon_name("undo");
    item->set_tooltip_text("goto previous page");
    item->set_homogeneous(false);
    toolbar1.append(*item);
    item->signal_clicked().connect( sigc::mem_fun(*this, &GtkMainForm::on_toolbar_previous) );
    
	item = Gtk::manage(new Gtk::ToolButton("next"));
    item->set_use_underline();
	item->set_is_important(false);
    item->set_icon_name("redo");
    item->set_tooltip_text("goto next page");
    item->set_homogeneous(false);
    toolbar1.append(*item);
    item->signal_clicked().connect( sigc::mem_fun(*this, &GtkMainForm::on_toolbar_next) );
    
    item = Gtk::manage(new Gtk::ToolButton("last"));
	item->set_icon_name("go-last");
    item->set_tooltip_text("goto last page");
	item->set_is_important(false);
    toolbar1.append(*item);
    item->signal_clicked().connect( sigc::mem_fun(*this, &GtkMainForm::on_toolbar_last) );

    toolbar1.append( *(Gtk::manage(new Gtk::SeparatorToolItem)) );
    
    item = Gtk::manage(new Gtk::ToolButton("new book"));
    item->set_use_underline();
	item->set_is_important(false);
    item->set_icon_name("document-new");
    item->set_tooltip_text("creat a new post");
    item->set_homogeneous(false);
    toolbar1.append(*item);
    item->signal_clicked().connect( sigc::mem_fun(*this, &GtkMainForm::on_toolbar_new) );

    item = Gtk::manage(new Gtk::ToolButton("add page"));
    item->set_use_underline();
	item->set_is_important(false);
    item->set_icon_name("add");
    item->set_tooltip_text("append a new page. use title bar & lower right box.");
    item->set_homogeneous(false);
    toolbar1.append(*item);
    item->signal_clicked().connect( sigc::mem_fun(*this, &GtkMainForm::on_toolbar_save) );

    item = Gtk::manage(new Gtk::ToolButton("comment"));
    item->set_sensitive(false);
    item->set_use_underline();
	item->set_is_important(false);
    item->set_icon_name("user-idle");
    item->set_tooltip_text("attach a comment. use lower right text box.");
    item->set_homogeneous(false);
    toolbar1.append(*item);
    item->signal_clicked().connect( sigc::mem_fun(*this, &GtkMainForm::on_toolbar_comment) );

    toolbar1.append( *(Gtk::manage(new Gtk::SeparatorToolItem)) );
    
	item = Gtk::manage(new Gtk::ToolButton("follow"));
    item->set_use_underline();
	item->set_is_important(false);
    item->set_icon_name("system-users");
    item->set_tooltip_text("follow other person");
    item->set_homogeneous(false);
    toolbar1.append(*item);
    item->signal_clicked().connect( sigc::mem_fun(*this, &GtkMainForm::on_toolbar_follow) );

    item = Gtk::manage(new Gtk::ToolButton("Vote"));
    item->set_use_underline();
	item->set_is_important(false);
    item->set_icon_name("document-open");
    item->set_tooltip_text("vote for current post");
    item->set_homogeneous(false);
    toolbar1.append(*item);
    item->signal_clicked().connect( sigc::mem_fun(*this, &GtkMainForm::on_toolbar_vote) );
    
    item = Gtk::manage(new Gtk::ToolButton("progress"));
    item->set_use_underline();
    item->set_icon_name("gnome-foot");
    item->set_tooltip_text("see current vote status");
    item->set_homogeneous(false);
    toolbar1.append(*item);
	item->set_is_important(false);
    item->signal_clicked().connect( sigc::mem_fun(*this, &GtkMainForm::on_toolbar_progress) );

    item = Gtk::manage(new Gtk::ToolButton("Finalize"));
    item->set_use_underline();
	item->set_is_important(false);
    item->set_icon_name("exit");
    item->set_tooltip_text("Final notify for current post.");
    item->set_homogeneous(false);
    toolbar1.append(*item);
    item->signal_clicked().connect( sigc::mem_fun(*this, &GtkMainForm::on_toolbar_finalize) );
}

void GtkMainForm::menuBar1Setup()
{	
	submenu1.append(subitem11);
	submenu1.append(subitem12);
	submenu1.append(subitem13);
    item1.set_submenu(submenu1);
	
    submenu2.append(subitem21);
	submenu2.append(subitem22);
	submenu2.append(subitem23);
    item2.set_submenu(submenu2);

    menuBar1.append(item1);
    menuBar1.append(item2);

	subitem11.signal_activate().connect(sigc::mem_fun(*this, &GtkMainForm::on_menu_file_new_generic));
	subitem13.signal_activate().connect(sigc::mem_fun(*this, &GtkMainForm::on_menu_file_quit));
	subitem21.signal_activate().connect(sigc::mem_fun(*this, &GtkMainForm::on_menu_tutorial));
	subitem23.signal_activate().connect(sigc::mem_fun(*this, &GtkMainForm::on_menu_about));
	subitem22.signal_activate().connect(sigc::mem_fun(*this, &GtkMainForm::on_menu_manual));
	subitem12.signal_activate().connect(sigc::mem_fun(*this, &GtkMainForm::on_menu_option));
}

void GtkMainForm::on_toolbar_comment()
{
	commentpopup = auto_ptr<CommentPopup>(new CommentPopup('c', "", ""));
	commentpopup->set_transient_for(*this);
	commentpopup->show();
}

void GtkMainForm::on_toolbar_follow()
{
    followPopup = auto_ptr<FollowPopup>(new FollowPopup);
    string s = label5.get_label();
    char ar[30];
    int i = s.find(' ', 12);
    s.copy(ar, i-12, 12);
    ar[i-12] = 0;

    followPopup->entry2.set_text(ar);
    followPopup->label3.set_label("currently following " + member.getFollow());
    followPopup->set_transient_for(*this);
    followPopup->show();
}

void GtkMainForm::on_toolbar_vote()
{
    if(member.getLevel() >= representative) {
        board.setPage(board.getField(), board.getNumber(), maxPage);
        board.read(); 
        string t = board.getTitle();
        if(t == "Final notify." || t == "Final result.") {
            label1.set_label("representatives cannot vote after final notify.");
            goto here;
        }
    }
    board.setPage(board.getField(), board.getNumber(), 0);
    board.read();
    votePopup = auto_ptr<VotePopup>(new VotePopup(board.getVotingOption()));
    votePopup->set_transient_for(*this);
    votePopup->show();    
 here:;
}

void GtkMainForm::on_toolbar_progress()
{
	int p = board.getPage();
	board.setPage(board.getField(), board.getNumber(), 0);
	board.read();//for voting option
    string s = vote.calculateVoteHtml(board.getField(), board.getNumber(), board.getVotingOption());
	notebook.set_current_page(0);
	webkit_web_view_load_html_string(WEBKIT_WEB_VIEW(webview.get()), s.c_str(), "www.naver.com");
	board.setPage(board.getField(), board.getNumber(), p);
	board.read();
}

void GtkMainForm::on_toolbar_go()
{
	if(curLev == 3) {
   		int i = Util::stoi(entry2.get_text());
		if (i >= 0 && i <= maxPage) {
       		commentSetup(board.getField(), board.getNumber(), i);
       		label1.set_label("Done");
    	}
    	else label1.set_label("over limit");
    }
}

void GtkMainForm::on_toolbar_upper()
{
    if(curLev == 3) commentSetup(board.getField(), -1, 0);
    else commentSetup("", 0, 0);
}

void GtkMainForm::on_toolbar_new()
{
    newbook = auto_ptr<NewBook>(new NewBook);
    newbook->set_transient_for(*this);
    newbook->show();
}

void GtkMainForm::on_toolbar_save()//add page
{
	curPage++;
	textView1.get_buffer()->set_text("");
	notebook.set_current_page(1);
	button1.set_sensitive(true);
}

void GtkMainForm::on_toolbar_finalize()
{
    dialog1 = new Gtk::MessageDialog(*this, "This will end this post and calculate the votes. You will not be able to add any pages.\n\nAre you sure?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK_CANCEL);
    int result = dialog1->run();
    delete dialog1;
    if(result == Gtk::RESPONSE_OK) {
        string f = board.getField();
        int n = board.getNumber();
        board.setPage(f, n, 0);
        board.read();
        int o = board.getVotingOption();
        board.setPage(f, n, maxPage);
        board.read();
        board.setText(vote.calculateVoteHtml(f, n, o));
        board.setId(member.getEmail());
        board.write('f');
        commentSetup(f, n, board.getPage());
    }
}

void GtkMainForm::on_menu_tutorial()
{
	ifstream infile("tutorial.html");
	string s, t;
	while(infile>>s) t += s + " ";
	infile.close();
	//textView1.get_buffer()->set_text(t);
	notebook.set_current_page(0);
	webkit_web_view_load_html_string(WEBKIT_WEB_VIEW(webview.get()), t.c_str(), "www.naver.com");
}

void GtkMainForm::on_menu_manual()
{
    ifstream infile("manual.html");
    string s, t;
	while(infile>>s) t += s + " ";
	infile.close();
	//textView1.get_buffer()->set_text(t);
	notebook.set_current_page(0);
	webkit_web_view_load_html_string(WEBKIT_WEB_VIEW(webview.get()), t.c_str(), "www.naver.com");
}

void GtkMainForm::on_menu_option()
{
	if(toolbar1.get_toolbar_style() == Gtk::TOOLBAR_BOTH) 
		toolbar1.set_toolbar_style(Gtk::TOOLBAR_BOTH_HORIZ);
	else toolbar1.set_toolbar_style(Gtk::TOOLBAR_BOTH);
}

void GtkMainForm::on_menu_about()
{
	ifstream infile("licence.html");
    string s, t;
	while(infile>>s) t += s + " ";
	infile.close();
	//textView1.get_buffer()->set_text(t);
	notebook.set_current_page(0);
	webkit_web_view_load_html_string(WEBKIT_WEB_VIEW(webview.get()), t.c_str(), "www.naver.com");
	
	dialog1 = new Gtk::MessageDialog(*this, "Discussion & Democratic Decision making\nFollowing GPL licence\nmade by zezeon1@gmail.com");
	dialog1->run();
	delete dialog1;
}

void GtkMainForm::on_menu_file_new_generic()
{
	connPopup = auto_ptr<ConnectPopup>(new ConnectPopup);
    connPopup->set_transient_for(*this);
    connPopup->show();
}

void GtkMainForm::on_button1_clicked()
{
	if(curPage != maxPage + 1) {
		board.setPage(board.getField(), board.getNumber(), board.getPage());
		board.read();
	}
	board.setTitle(entry1.get_text());
	board.setText(textView1.get_buffer()->get_text());
	if(curPage == maxPage + 1) {
		//board.setPages(curPage);
		board.write('a');
	}
	else board.write('e');
	commentSetup(board.getField(), board.getNumber(), curPage);
}
