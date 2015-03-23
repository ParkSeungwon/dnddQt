class NewBook : public Gtk::Window
{
protected:
    Gtk::HScale scale1, scale2, scale3, scale4, scale6;
    Gtk::Label label1, label2, label3, label4, label6, label7, label9;
    Gtk::HBox hbox1, hbox2, hbox3, hbox4, hbox6, hbox7, hbox8, hbox9;
    Gtk::VBox vbox1;
    Gtk::Button button1, button2;
    Gtk::Entry entry1, entry2;

    void click_button1();
    void click_button2(){hide();}
    
public:
    NewBook();
    virtual ~NewBook(){}
};
