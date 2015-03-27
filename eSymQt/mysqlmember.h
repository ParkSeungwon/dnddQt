class MysqlMember : public Member
{
private:
	Mysqlquery *mysqlQuery;
public:
    MysqlMember(Mysqlquery *qQuery);
	bool read(string _id);//email주소를 아이디로 사용함.
	void write();
	bool exist(string _email);
    bool login(string user, string pass);
    bool writeFollow(string email, string follower, bool secret);
};


