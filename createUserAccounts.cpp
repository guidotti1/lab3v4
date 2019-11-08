
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stdlib.h>
#include <sstream>
#include <stdexcept>
#include <string>

// Stuff for AJAX
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"
#include "mysql_connection.h"
#include "mysql_driver.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>


#define XML_USE_STL

#define HOST "localhost"
#define USER "guidotti1"
#define DB "guidotti1"
#define PASS "S217026"

using namespace std;
using namespace cgicc; // Needed for AJAX functions.


class userInfo
{
public :
    string email;
    string password;
    userInfo();
    userInfo(string e, string p);

private :
};

void createAccount(string email, string password, string url, string user, string pass, string database);

int main()
{
    const string url=HOST;
    const string user=USER;
    const string database=DB;
    const string pass=PASS;

    Cgicc cgi;
    form_iterator email = cgi.getElement("email");
    string emailString = **email;

    form_iterator password = cgi.getElement("password");
    string pwString = **password;

    sql::Driver* driver = sql::mysql::get_driver_instance();
    std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
    con->setSchema(database);
    std::auto_ptr<sql::Statement> stmt(con->createStatement());
    vector<userInfo> list;
    stmt->execute("SELECT * FROM Users WHERE email like '"+emailString+"' AND pass like '"+pwString+"'");
    std::auto_ptr< sql::ResultSet > res;
    do {
      res.reset(stmt->getResultSet());
      while (res->next()) {
            userInfo entry(res->getString("email"),res->getString("pass"));
	  list.push_back(entry);

      }
    } while (stmt->getMoreResults());


    if (list.size() == 0)
        {
        //ACCOUNT CAN BE CREATED
        createAccount(emailString, pwString, url, user, pass, database);
        }
    else if (list.size() == 1)
        {
        //ACCOUNT ALREADY CREATED - GIVE ERROR MESSAGE.
        }
 return 0;
}

userInfo::userInfo()
{
    email, password = "";
}

userInfo::userInfo(string e, string p)
{
    email = e;
    password = p;
}

void createAccount(string email, string password, string url, string user, string pass, string database)
{
    sql::Driver* driver = sql::mysql::get_driver_instance();
    std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
    con->setSchema(database);
    std::auto_ptr<sql::Statement> stmt(con->createStatement());
    stmt->execute("INSERT INTO User(email, pass) VALUES ('"+email+"','"+password+"')");

}
