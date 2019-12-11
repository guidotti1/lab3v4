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



int main()
{
    const string url=HOST;
    const string user=USER;
    const string database=DB;
    const string pass=PASS;

    Cgicc cgi;


    form_iterator lastcomment = cgi.getElement("lastcomment");
    string lastcommentString = **lastcomment;
    
    form_iterator lastvote = cgi.getElement("lastvote");
    string lastvoteString = **lastvote;
    
    cout << "Content-Type: text/plain\n\n";

    string commentIDZero = lastcommentString;
    string voteIDZero = lastvoteString;


    sql::Driver* driver = sql::mysql::get_driver_instance();
    std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
    con->setSchema(database);
    std::auto_ptr<sql::Statement> stmt(con->createStatement());
    std::auto_ptr< sql::ResultSet > res;

    string output = "";

    vector<string> commentIDS;

    stmt->execute("SELECT CommentID FROM comments WHERE CommentID >= '"+commentIDZero+"'");
    do {
            res.reset(stmt->getResultSet());
            while (res->next()) {
                commentIDS.push_back(res->getString("CommentID"));
            }
        }while (stmt ->getMoreResults());
    
    output += commentIDS[commentIDS.size()-1];
    output += "^";
    
    vector<string> voteIDS;  
    stmt->execute("SELECT voteID FROM votes WHERE voteID >= '"+voteIDZero+"'");
    do {
            res.reset(stmt->getResultSet());
            while (res->next()) {
                voteIDS.push_back(res->getString("voteID"));
            }
        }while (stmt ->getMoreResults());
    
    output += voteIDS[voteIDS.size()-1];
    
    cout << output << endl;
    return 0;
}

