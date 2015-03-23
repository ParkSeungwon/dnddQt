struct VoteResult
{
    string email;
    string name;
    int votedfor;
    string date;
    bool secret;
};

struct FollowTable
{
    string email;
    string follower;
    bool secret;
};

class MysqlVote : public Vote, public Mysqlquery
{
private:
    int findMan(VoteResult *vr, int count, string email, int start);
    int findMan(FollowTable *ft, int count, string email, int start);
    
public:
	void write();
	string calculateVote(int option); //토론 종료시 표결결과를 마지막페이지에 써넣는다. 그 텍스트.
	string calculateVoteHtml(string field, int number, int option);
};

