class CommentInterface 
{
public:
    virtual bool openConnection(string host, string user, string pass, string db) = 0;
    virtual bool join(string, string, string, string, string) = 0;
    virtual int create_new_book(int r, int w, int c, int v, bool turn, string ids, int respons, int options, string title) = 0;
    virtual int followID(string s, bool secret) = 0;
    virtual int votedFor(int option, bool secret) = 0;
	virtual int write(char option, string, string, string) = 0;
};
