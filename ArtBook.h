#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
/* uncomment for applications that use vectors */
#include <vector>

#include "mysql_connection.h"
#include "mysql_driver.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "artEntry.h"

#ifndef ARTBOOK_H
#define ARTBOOK_H

#define HOST "localhost"
#define USER "guidotti1"
#define DB "guidotti1"
#define PASS "S217026"

using namespace std;

class PhoneBook {
public:
    PhoneBook();
    vector<artEntry> findByFirst(string findFirst);
    vector<artEntry> findByLast(string findLast);
    vector<artEntry> findByTitle(string findTitle);
    //void addEntry(string first,string last,string phone,string type);
    //void editEntry(string idnum,string first,string last,string phone,string type);
    //void deleteEntry(string idnum);
private:
    const string url=HOST;
    const string user=USER;
    const string database=DB;
    const string pass=PASS;
    
};

#endif /* PHONEBOOK_H */

