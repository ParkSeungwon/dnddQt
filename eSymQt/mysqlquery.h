class Mysqlquery 
{
private:
    static QSqlDatabase qdb;
    static QSqlRecord record;

protected:
    static QSqlQuery sqlQuery;
    QSqlError myQuery(string str);

public:
    bool connect(string host, string user, string pass, string db);
};
