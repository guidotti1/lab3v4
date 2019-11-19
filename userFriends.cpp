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
#include "artEntry.h"


#define XML_USE_STL

#define HOST "localhost"
#define USER "guidotti1"
#define DB "guidotti1"
#define PASS "S217026"

using namespace std;
using namespace cgicc; // Needed for AJAX functions.

class Friend
{
    public:
      string receive;
      string send;
      Friend();
      Friend(string r, string s);
};

int main()
{
    const string url=HOST;
    const string user=USER;
    const string database=DB;
    const string pass=PASS;

    Cgicc cgi;
    form_iterator send = cgi.getElement("send");
    string sendString = **send;

    form_iterator receive = cgi.getElement("receive");
    string receiveString = **receive;
    
    form_iterator type = cgi.getElement("type");
    string typeString = **receive;


    cout << "Content-Type: text/plain\n\n";
    sql::Driver* driver = sql::mysql::get_driver_instance();
    std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
    con->setSchema(database);
    std::auto_ptr<sql::Statement> stmt(con->createStatement());
    std::auto_ptr< sql::ResultSet > res;
    
    string output = "";
    
    vector<Friend> list;
    if (typeString == "add")
    {
        
        stmt->execute("SELECT * FROM Friends WHERE sendEmail = '"+sendString+"' and receiveEmail = '"+receiveString+"'");
        do {
                res.reset(stmt->getResultSet());
                while (res->next()) {
                    Friend entry(res->getString("receiveEmail"), res->getString("sendEmail"));
                    list.push_back(entry);
                }
            }while (stmt ->getMoreResults());
         if (list.size() > 0)
         {
                output += "You already have added that profile";
         }
        else 
        {
                stmt->execute("INSERT INTO Friends(sendEmail, receiveEmail) VALUES('"+sendString+"', '"+receiveString+"')");
                output += "Success";
        }
    }
    
    else if (typeString == "retrieve")
    {
        stmt->execute("SELECT * FROM Friends WHERE sendEmail = '"+sendString+"'");
        do {
                res.reset(stmt->getResultSet());
                while (res->next()) {
                    Friend entry(res->getString("receiveEmail"), res->getString("sendEmail"));
                    list.push_back(entry);
                }
            }while (stmt ->getMoreResults());
         if (list.size() == 0)
         {
                output += "No friends added";
         }
        else 
        {
                for (int i = 0; i < list.size(); i++)
                {
                    output += list[i].receive;
                    output += " ";
                }
        }
        
    }

    cout << output << endl;
    
    
    return 0;
}

Friend::Friend(string r, string s)
{
    receive = r;
    send = s;
}



