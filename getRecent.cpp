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


    form_iterator lastcomment = cgi.getElement("lastcomment");
    string lastcommentString = **lastcomment;
    
    
    int lastCommentInt;
   
    
    istringstream iss (lastcommentString);
    iss >> lastCommentInt;
    int fiveCommentsAgoInt = lastCommentInt - 5;
    stringstream ss;
    ss << fiveCommentsAgoInt;
    string fiveCommentsAgoString = ss.str();
     /*
    vector <int> lastFiveCommentIDSInt;
    for (int i = 0; i < 5; i ++)
    {
           lastFiveCommentIDSInt.push_back(lastCommentInt - i);
    }

    vector<string> lastFiveCOmmentIDSString;
    for (int i = 0; i < lastFiveCommentIDSInt.size(); i++)
    {
        stringstream ss;
        ss << lastFiveCommentIDSInt[i];
        lastFiveCOmmentIDSString.push_back(ss.str());
    }
    */
        
    cout << "Content-Type: text/plain\n\n";
    sql::Driver* driver = sql::mysql::get_driver_instance();
    std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
    con->setSchema(database);
    std::auto_ptr<sql::Statement> stmt(con->createStatement());
    std::auto_ptr< sql::ResultSet > res;
    /*
    sql::Driver* driver2 = sql::mysql::get_driver_instance();
    std::auto_ptr<sql::Connection> con2(driver2->connect(url, user, pass));
    con2->setSchema(database);
    std::auto_ptr<sql::Statement> stmt2(con2->createStatement());
    std::auto_ptr< sql::ResultSet > res2;
    */
    //cout << "EMAIL IS : " << emailString << endl;
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
         
     /*
     for (int i =0; i < artIDS.size(); i++)
     {
         stmt->execute("SELECT * FROM art where ARTID = '"+artIDS[i]+"'");
         do {
             res.reset(stmt->getResultSet());
             while (res->next()) {
                string first, last;
                stringstream nameStream(res->getString("Author"));
                getline(nameStream, last, ',');
                getline(nameStream, first);
                output += "^" + last + "^" + first + "^" + res->getString("URL") + "^" + res->getString("Title");

             }
            }while (stmt ->getMoreResults());
         
         stmt->execute("SELECT * FROM comments where Email = '"+emailString+"' AND ARTID = '"+artIDS[i]+"'");
         do {
             res.reset(stmt->getResultSet());
             while (res->next()) {
                output += "^" + res->getString("Comment");
             }
            }while (stmt ->getMoreResults());
         output += "‰"; //CHARAACTER SIGNIFIES END OF COMMENTS FOR THE GIVEN USERNAME FOR A SPECIFIC PAINTING
      }
    output += "®";  //CHARACTER SIGNIFIES END OF ALL COMMENTS FOR THE GIVEN USERNAME
    
    vector<string> upvotedArt;
    stmt->execute("SELECT * FROM votes where email = '"+emailString+"' AND voteType = 'Upvote'");
    do {
             res.reset(stmt->getResultSet());
             while (res->next()) {
               upvotedArt.push_back(res->getString("ARTID"));
             }
        }while (stmt ->getMoreResults());
    
    for (int i = 0; i <upvotedArt.size(); i++)
    {
            stmt->execute("SELECT * FROM art where ARTID = '"+upvotedArt[i]+"'");
            do {
             res.reset(stmt->getResultSet());
             while (res->next()) {
                string first, last;
                stringstream nameStream(res->getString("Author"));
                getline(nameStream, last, ',');
                getline(nameStream, first);
                output += "^" + last + "^" + first + "^" + res->getString("URL") + "^" + res->getString("Title");
             }
            }while (stmt ->getMoreResults());
    }
    output += "µ"; //CHARACTER SIGNIFIES END OF UPVOTES
    
           
    vector<string> downvotedArt;
    stmt->execute("SELECT * FROM votes where email = '"+emailString+"' AND voteType = 'Downvote'");
    do {
             res.reset(stmt->getResultSet());
             while (res->next()) {
               downvotedArt.push_back(res->getString("ARTID"));
             }
        }while (stmt ->getMoreResults());
    
    for (int i = 0; i <downvotedArt.size(); i++)
    {
            stmt->execute("SELECT * FROM art where ARTID = '"+downvotedArt[i]+"'");
            do {
             res.reset(stmt->getResultSet());
             while (res->next()) {
                string first, last;
                stringstream nameStream(res->getString("Author"));
                getline(nameStream, last, ',');
                getline(nameStream, first);
                output += "^" + last + "^" + first + "^" + res->getString("URL") + "^" + res->getString("Title");
             }
            }while (stmt ->getMoreResults());
    }
    //output += "€";  //CHARACTER SIGNIFIES END OF DOWNVOTES
    cout << output << endl;
    
    */
    return 0;
}

