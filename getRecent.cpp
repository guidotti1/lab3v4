#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stdlib.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <stringstream> 

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



int main()
{
    const string url=HOST;
    const string user=USER;
    const string database=DB;
    const string pass=PASS;

    Cgicc cgi;


    form_iterator lastcomment = cgi.getElement("lastcomment");
    string lastcommentString = **lastcomment;
    cout << "Content-Type: text/plain\n\n";
    cout << "123123123123 " << endl;
    exit(0);
    int lastCommentInt;
    istringstream iss (lastcommentString);
    iss >> lastCommentInt;
    int fiveCommentsAgoInt = lastCommentInt - 5;
    stringstream ss;
    ss << fiveCommentsAgoInt;
    string fiveCommentsAgoString = ss.str();


    sql::Driver* driver = sql::mysql::get_driver_instance();
    std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
    con->setSchema(database);
    std::auto_ptr<sql::Statement> stmt(con->createStatement());
    std::auto_ptr< sql::ResultSet > res;

    string output = "";

    vector<string> artIDS;
    cout << "the request we are making : " << endl;
    cout << "SELECT DISTINCT ARTID FROM comments WHERE CommentID >= '"+fiveCommentsAgoString+"'" << endl;
    stmt->execute("SELECT DISTINCT ARTID FROM comments WHERE CommentID >= '"+fiveCommentsAgoString+"'");
    do {
            res.reset(stmt->getResultSet());
            while (res->next()) {
                artIDS.push_back(res->getString("ARTID"));
            }
        }while (stmt ->getMoreResults());
    
     for (int i = 0; i < artIDS.size(); i++)
     {
         cout << "artIDS[i] : " << artIDS[i] << endl;
     }
         

    return 0;
}

