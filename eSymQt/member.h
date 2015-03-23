enum Level {anonymous, registered, regular, representative, senior, root};
	
class Member 
{
 private:
	
 protected:
	string email;
	string password;
	Level level;
	string name;
	string tel;
	string follow;
    void show();
    
 public:
	Member() {}
	bool auth(string _password); //MysqlMember에서 같은 이름의 함수가 있다.
	static bool checkValidEmail(string _email);
	string setInfo(string email, string password, Level level, string name, string tel, string follow = "");
    string getEmail() {return email;}
    string getName() {return name;}
    Level getLevel() {return level;}
    string getFollow() {return follow;}
    string getTel() {return tel;}
};
