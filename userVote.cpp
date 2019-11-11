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

class voteInfo
{
    public:
    string voteType;
    string ARTID;
    string email;
    //int voteID;
    voteInfo();
    voteInfo(string v, string a, string e);
};

int main()
{
    const string url=HOST;
    const string user=USER;
    const string database=DB;
    const string pass=PASS;

    Cgicc cgi;
    form_iterator vote = cgi.getElement("voteType");
    string voteString = **vote;

    form_iterator email = cgi.getElement("email");
    string emailString = **email;

    form_iterator artID = cgi.getElement("ArtID");
    string artIDString = ** artID;

    cout << "Content-Type: text/plain\n\n";
    sql::Driver* driver = sql::mysql::get_driver_instance();
    std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
    con->setSchema(database);
    std::auto_ptr<sql::Statement> stmt(con->createStatement());
    std::auto_ptr< sql::ResultSet > res;
    
    vector<voteInfo> list;
    stmt->execute("SELECT * FROM votes WHERE ARTID = '"+artIDString+"' and email = '"+emailString+"'");
    do {
        res.reset(stmt->getResultSet());
        while (res->next()) {
            commentInfo entry(res->getString("voteType"), res->getString("ARTID"), res->getString("email"));
            list.push_back(entry);
        }
        }while (stmt ->getMoreResults());
        
    if (list.size() > 0)
    {
        cout << "You have already commented on that piece of art" << endl;
    }
    else 
    {
        if (voteString == "Upvote")
        {
        //add upvote to database
        }
        else
        {
        //add downvote to database
        }
     }
        
        

    return 0;
}

voteInfo::voteInfo()
{
    voteType, ARTID, email = "";
}
        
voteInfo::voteInfo(string v, string a, string e)
{
  voteType = v;
  ARTID =a ;
  email = e;
}