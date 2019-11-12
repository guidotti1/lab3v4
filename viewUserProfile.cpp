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



int main()
{
    const string url=HOST;
    const string user=USER;
    const string database=DB;
    const string pass=PASS;

    Cgicc cgi;
    //form_iterator vote = cgi.getElement("voteType");
    //string voteString = **vote;

    form_iterator email = cgi.getElement("email");
    string emailString = **email;

    //form_iterator artID = cgi.getElement("ArtID");
    //string artIDString = ** artID;
    
    //form_iterator type = cgi.getElement("type");
    //string typeString = **type;

    cout << "Content-Type: text/plain\n\n";
    sql::Driver* driver = sql::mysql::get_driver_instance();
    std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
    con->setSchema(database);
    std::auto_ptr<sql::Statement> stmt(con->createStatement());
    std::auto_ptr< sql::ResultSet > res;
    
    std::auto_ptr<sql::Statement> stmt2(con->createStatement());
    std::auto_ptr< sql::ResultSet > res2;
    output = "^";
    output += emailString;
    vector<string> artIDS;
    stmt->execute("SELECT DISTINCT ARTID FROM comments WHERE Email = '"+emailString+"'");
    do {
            res.reset(stmt->getResultSet());
            while (res->next()) {
                string currentID(res->getString("ARTID"));
                stmt2->execute("SELECT * FROM comments WHERE Email = '"+emailString+"' and ARTID = '"+currentID+"'");
                do {
                  res2.reselt(stmt2->getResultSet());
                  while (res2->next()) {
                  string currentComment(res->getString("Comment"));
                  output += "^";
                  output += currentComment;
                  }
                while (stmt2 ->getMoreResults());
            }
            }while (stmt ->getMoreResults());
     /*
    if (typeString == "vote")
    {
        stmt->execute("SELECT * FROM votes WHERE ARTID = '"+artIDString+"' and email = '"+emailString+"'");
        do {
            res.reset(stmt->getResultSet());
            while (res->next()) {
                voteInfo entry(res->getString("voteType"), res->getString("ARTID"), res->getString("email"));
                list.push_back(entry);
            }
            }while (stmt ->getMoreResults());

        if (list.size() > 0)
        {
            cout << "You have already voted on that piece of art" << endl;
        }
        else 
        {
            stmt->execute("INSERT INTO votes(voteType, ARTID, email) VALUES('"+voteString+"', '"+artIDString+"', '"+emailString+"')");
            cout << "Success" << endl;
         }
    }
        
    else if (typeString == "display")
    {
        stmt->execute("SELECT * FROM votes WHERE ARTID = '"+artIDString+"' and voteType = 'Upvote'");
        do {
            res.reset(stmt->getResultSet());
            while (res->next()) {
                voteInfo entry(res->getString("voteType"), res->getString("ARTID"), res->getString("email"));
                list.push_back(entry);
            }
            }while (stmt ->getMoreResults());
        int noUpvotes = list.size();
        list.clear();
       
        stmt->execute("SELECT * FROM votes WHERE ARTID = '"+artIDString+"' and voteType = 'Downvote'");
        do {
            res.reset(stmt->getResultSet());
            while (res->next()) {
                voteInfo entry(res->getString("voteType"), res->getString("ARTID"), res->getString("email"));
                list.push_back(entry);
            }
            }while (stmt ->getMoreResults());
        
        int noDownvotes = list.size();
        cout << "^" << noUpvotes << "^" << noDownvotes << endl;
 
    }
    */
    return 0;
}

