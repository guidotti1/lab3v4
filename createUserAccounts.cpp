
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

// Stuff for AJAX
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"


#define XML_USE_STL



using namespace std;
using namespace cgicc; // Needed for AJAX functions.

#define HOST "localhost"
#define USER "guidotti1"
#define DB "guidotti1";
#define PASS "S217026;

class user
{
public :
    string email;
    string password;
    user();
    user(string e, string p);

private :
};

void createAccount(string email, string password);

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
    vector<user> list;
    stmt->execute("SELECT * FROM Users WHERE email like '"+email+"' AND pass like '"+pwString+"'");
    do {
      res.reset(stmt->getResultSet());
      while (res->next()) {
            user entry(res->getString("email"),res->getString("pass"));
	  list.push_back(entry);

      }
    } while (stmt->getMoreResults());


    if (list.size() == 0)
        {
        //ACCOUNT CAN BE CREATED
        createAccount(email, password);
        }
    else if (list.size() == 1)
        {
        //ACCOUNT ALREADY CREATED - GIVE ERROR MESSAGE.
        }

}

user::user()
{
    email, password = "";
}

user::user(string e, string p)
{
    email = e;
    password = p;
}

void createAccount(string email, string password)
{
    sql::Driver* driver = sql::mysql::get_driver_instance();
    std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
    con->setSchema(database);
    std::auto_ptr<sql::Statement> stmt(con->createStatement());
    stmt->execute("INSERT INTO User(email, pass) VALUES ('"+email+"','"+password+"')");

}
