class Mysqlquery 
{
private:
    QSqlDatabase qdb;

protected:
    QSqlQuery res;
    QSqlError myQuery(string str);

public:
    bool connect(string host, string user, string pass, string db);
};
