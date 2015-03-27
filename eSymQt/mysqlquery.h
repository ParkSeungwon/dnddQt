class Mysqlquery
{
private:
    QSqlDatabase qdb;

protected:


public:
    QSqlRecord record;
    QSqlQuery sqlQuery;
    bool connect(string host, string user, string pass, string db);
    bool myQuery(string str);
};
