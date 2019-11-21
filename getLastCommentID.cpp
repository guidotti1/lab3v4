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
    cout << "Content-Type: text/plain\n\n";

    string commentIDZero = lastcommentString;


    sql::Driver* driver = sql::mysql::get_driver_instance();
    std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
    con->setSchema(database);
    std::auto_ptr<sql::Statement> stmt(con->createStatement());
    std::auto_ptr< sql::ResultSet > res;

    string output = "";

    vector<string> commentIDS;
    //cout << "the request we are making : " << endl;
    //cout << "SELECT CommentID FROM comments WHERE CommentID >= '"+commentIDZero+"'" << endl;
    stmt->execute("SELECT CommentID FROM comments WHERE CommentID >= '"+commentIDZero+"'");
    do {
            res.reset(stmt->getResultSet());
            while (res->next()) {
                commentIDS.push_back(res->getString("CommentID"));
            }
        }while (stmt ->getMoreResults());
    /*

    for (int i = 0 ; i< commentIDS.size(); i++)
    {
        cout << "CommentIDS[i] : " << commentIDS[i] << endl;
    }
    */

    output += commentIDS[commentIDS.size()-1];
    cout << output << endl;
    return 0;
}

