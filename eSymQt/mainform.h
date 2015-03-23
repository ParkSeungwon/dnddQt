class GtkMainForm : public Gtk::Window, public CommentInterface
{
 private:
	void menuBar1Setup();
	void toolbar1Setup();
    void freeComments();
    int curPage, maxPage, curLev, curNumber;
    string user, pass, toc, curField;
    int setSensitive();
    Pango::FontDescription title_font, text_font;
	
 protected:
	Gtk::VBox vBox1, vBox2, vBox4, vBox5;
	Gtk::HBox hBox1, hBox2, hBox3, *hBox;
	Gtk::Entry entry1, entry2;
	Gtk::Toolbar toolbar1;
	Gtk::TextView textView1;
	Gtk::MenuBar menuBar1;
	Gtk::ScrolledWindow scrolledWindow1, scrolledWindow2, scwin3;
    Gtk::Notebook notebook;
    Gtk::CheckButton check1;
    
    Gtk::Frame *frame;
    Gtk::Label *label, label1, label2, label3, label4, label5;
	Gtk::Viewport viewport1;
    Gtk::Button *button, button1;
	Gtk::EventBox eventbox1;

	Gtk::MenuItem item1, item2, subitem11, subitem12, subitem13,
		subitem21, subitem22, subitem23;
    Gtk::Menu submenu1, submenu2;
    
	void on_menu_file_new_generic();
	void on_menu_file_quit() {hide();}
    void on_menu_tutorial();
    void on_menu_manual();
    void on_menu_about();
    void on_menu_option();
    void on_button1_clicked();
	void on_toolbar_go();
	void on_toolbar_comment();
    void on_toolbar_next() {commentSetup(board.getField(), board.getNumber(), ++curPage);}
    void on_toolbar_previous() {commentSetup(board.getField(), board.getNumber(), --curPage);}
    void on_toolbar_first() {commentSetup(board.getField(), board.getNumber(), curPage = 0);}
    void on_toolbar_last() {commentSetup(board.getField(), board.getNumber(), curPage = maxPage);}
    void on_toolbar_new();
    void on_toolbar_upper();
    void on_toolbar_save();
    void on_toolbar_follow();
    void on_toolbar_vote();
    void on_toolbar_progress();
    void on_toolbar_finalize();
    void switch_page(GtkNotebookPage*, guint page_num);
    virtual bool change_account(GdkEventButton* event);
    virtual void comment_press(Glib::ustring& s);
    int commentSetup(string field, int num, int page);

    Mysqlboard board;
    MysqlMember member;
    MysqlVote vote;
    auto_ptr<GtkWidget> webview;
    auto_ptr<ConnectPopup> connPopup;
    auto_ptr<NewBook> newbook;
    auto_ptr<FollowPopup> followPopup;
    auto_ptr<VotePopup> votePopup;
    //auto_ptr<Progress> progress;
    auto_ptr<CommentPopup> commentpopup;
    auto_ptr<ChangeAccount> changeAccount;
    Gtk::MessageDialog* dialog1;
    
 public:
	GtkMainForm(int argc, char *argv[]);
    ~GtkMainForm();
   
    virtual bool openConnection(string host, string user, string pass, string db);
    virtual bool join(string email, string pass, string name, string tel, string newps);
    virtual int create_new_book(int r, int w, int c, int v, bool turn, string ids, int respons, int options, string title);
    virtual int followID(string s, bool secret);
    virtual int votedFor(int option, bool secret);
	virtual int write(char option, string title, string contents, string date);
};


