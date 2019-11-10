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

class commentInfo
{
    public:
    string comment;
    string email;
    commentInfo();
    commentInfo(string c, string e);
};

int main()
{
    const string url=HOST;
    const string user=USER;
    const string database=DB;
    const string pass=PASS;

    Cgicc cgi;
    form_iterator comment = cgi.getElement("comment");
    string commentString = **comment;

    form_iterator email = cgi.getElement("email");
    string emailString = **email;

    form_iterator artID = cgi.getElement("ArtID");
    string artIDString = ** artID;
    
    form_iterator type = cgi.getElement("type");
    string typeString = **type;

    cout << "Content-Type: text/plain\n\n";
    sql::Driver* driver = sql::mysql::get_driver_instance();
    std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
    con->setSchema(database);
    std::auto_ptr<sql::Statement> stmt(con->createStatement());
    std::auto_ptr< sql::ResultSet > res;
    if (typeString == "add")
    {
        stmt->execute("INSERT INTO comments(Email, ARTID, Comment) VALUES('"+emailString+"', '"+artIDString+"', '"+commentString+"')");
    }
    else if (typeString == "display")
    {
        vector<commentInfo> list;
        stmt->execute("SELECT * FROM Phonebook WHERE ARTID = '"+artIDString+"'");
        do {
            res.reset(stmt->getResultSet());
            while (res->next()) {
                commentInfo entry(res->getString("Comment"), res->getString("Email"));
                list.push_back(entry);
            }
            }while (stmt ->getMoreResults());
        string output = "";
        for (int i = 0; i<list.size(); i++)
             {
                 output += list.at(i).comment + "^" + list.at(i).email;
             }
        cout << output << endl;           
    }
    return 0;
}

commentInfo::commentInfo()
{
    comment, email = "";
}
        
commentInfo::commentInfo(string c, string e)
{
    comment = c;
    email = e;
}
