class Vote
{
 protected:
	string field;
	int number;
	string votingId;
	int votedFor;
	bool secret;

 public:
	Vote() {}
	void setVote(string field, int number, string votingId, int votedFor, bool secret);
	void show();
};

