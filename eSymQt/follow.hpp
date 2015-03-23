class FollowPopup : public Gtk::Window
{
protected:
	Gtk::Label label2;
	Gtk::Button button2;
	Gtk::VBox vbox1;
	Gtk::HBox hbox2;
	Gtk::CheckButton check1;
	virtual void on_follow_click();
	
public:
    FollowPopup();
    virtual ~FollowPopup(){}
	Gtk::Entry entry2;
	Gtk::Label label3;
};
