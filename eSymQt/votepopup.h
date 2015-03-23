class VotePopup : public Gtk::Window
{
private:
	int which;
	
protected:
	Gtk::VBox vbox1, vbox2;
	Gtk::HBox hbox1;
	Gtk::Frame frame1;
	Gtk::RadioButton *radioButton;
	Gtk::CheckButton check;
	Gtk::Button button1, button2;
	Gtk::Label label1;
	void on_radio_click(int i) {which = i;}
	void on_exit_click() {hide();}
	void on_vote_click();
	
public:
    VotePopup(int option);
    ~VotePopup() {delete [] radioButton;}
};
