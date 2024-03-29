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

string firstCharUpper(string s)
{
	string returnS = s;
	for (int i = 1; i < s.size(); i++)
	{
		returnS[i] =  char(tolower(s[i]));
	}
	return returnS;
}


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
    string lastvoteString = ** lastvote;
	
    cout << "Content-Type: text/plain\n\n";

    int lastCommentInt;
    istringstream iss (lastcommentString);
    iss >> lastCommentInt;
    int fiveCommentsAgoInt = lastCommentInt - 5;
    stringstream ss;
    ss << fiveCommentsAgoInt;
    string fiveCommentsAgoString = ss.str();
	
    int lastVoteInt;
    istringstream iss1 (lastvoteString);
    iss1 >> lastVoteInt;
    int fiveVotesAgoInt = lastVoteInt - 5;
    stringstream ss1;
    ss1 << fiveVotesAgoInt;
    string fiveVotesAgoString = ss1.str();
    



    sql::Driver* driver = sql::mysql::get_driver_instance();
    std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
    con->setSchema(database);
    std::auto_ptr<sql::Statement> stmt(con->createStatement());
    std::auto_ptr< sql::ResultSet > res;

    string output = "®";

    vector<string> artIDS;

    stmt->execute("SELECT DISTINCT ARTID FROM comments WHERE CommentID >= '"+fiveCommentsAgoString+"'");
    do {
            res.reset(stmt->getResultSet());
            while (res->next()) {
                artIDS.push_back(res->getString("ARTID"));
            }
        }while (stmt ->getMoreResults());
    

    int nextCommentInt =fiveCommentsAgoInt;
    for (int i =0; i < artIDS.size(); i++)
         {
            string nextCommentString;
            stringstream ss2;
            ss2 << nextCommentInt;
            nextCommentString = ss2.str();
        
            stmt->execute("SELECT * FROM art where ARTID = '"+artIDS[i]+"'");
            do {
                 res.reset(stmt->getResultSet());
                 while (res->next()) {
                    string first, last;
                    stringstream nameStream(res->getString("Author"));
                    getline(nameStream, last, ',');
                    getline(nameStream, first);
                    output += "^" + firstCharUpper(last) + "^" + first + "^" + res->getString("URL") + "^" + res->getString("Title");

                 }
                }while (stmt ->getMoreResults());

             stmt->execute("SELECT * FROM comments where CommentID >= '"+nextCommentString+"' AND ARTID = '"+artIDS[i]+"'");
             do {
                 res.reset(stmt->getResultSet());
                 while (res->next()) {
                    output += "^" + res->getString("Comment");
                 }
                }while (stmt ->getMoreResults());
             output += "‰"; //CHARAACTER SIGNIFIES END OF COMMENTS FOR THE GIVEN USERNAME FOR A SPECIFIC PAINTING
             
           
             nextCommentInt++;
          }
    
            output += "®";  //CHARACTER SIGNIFIES END OF ALL COMMENTS FOR THE GIVEN USERNAME
    

    
            
            vector<string> upvotedArt;
	
            stmt->execute("SELECT * FROM votes where voteID >= '"+fiveVotesAgoString+"' AND voteType = 'Upvote'");
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
                        output += "^" + firstCharUpper(last) + "^" + first + "^" + res->getString("URL") + "^" + res->getString("Title");
                     }
                    }while (stmt ->getMoreResults());
            }
            output += "µ"; //CHARACTER SIGNIFIES END OF UPVOTES


            vector<string> downvotedArt;
            stmt->execute("SELECT * FROM votes where voteID >= '"+fiveVotesAgoString+"' AND voteType = 'Downvote'");
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
                        output += "^" + firstCharUpper(last) + "^" + first + "^" + res->getString("URL") + "^" + res->getString("Title");
                     }
                    }while (stmt ->getMoreResults());
            }
            
    cout << output << endl;
          
    return 0;
}

