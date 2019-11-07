#include <vector>
#include <iostream>
#include "artBook.h"
#include "artEntry.h"

artBook::artBook() 
{

}

vector<artEntry> artBook::findByLast(string findLast) 
  {
    sql::Driver* driver = sql::mysql::get_driver_instance();
    std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
    con->setSchema(database);
    std::auto_ptr<sql::Statement> stmt(con->createStatement());
    vector<artEntry> list;
    stmt->execute("SELECT * FROM art WHERE Author like '"+findLast+"%'");
    std::auto_ptr< sql::ResultSet > res;
    do {
      res.reset(stmt->getResultSet());
      while (res->next()) {	   
            artEntry entry(res->getString("Author"),res->getString("Born-Diec"),
			   res->getString("Title"),res->getString("Date"),
	    res->getString("Technique"), res->getString("Location"), res->getString("URL"), 
	    res->getString("Form"), res->getString("Type"), res->getString("School"), res->getString("Timeframe"));
	  list.push_back(entry);

      }
    } while (stmt->getMoreResults());
    return list;
}

vector<artEntry> artBook::findByFirst(string findFirst) 
  {
    sql::Driver* driver = sql::mysql::get_driver_instance();
    std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
    con->setSchema(database);
    std::auto_ptr<sql::Statement> stmt(con->createStatement());
    vector<artEntry> list;
    stmt->execute("SELECT * FROM art WHERE Author like '%"+findFirst+"'");
    std::auto_ptr< sql::ResultSet > res;
    do {
      res.reset(stmt->getResultSet());
      while (res->next()) {	   
            artEntry entry(res->getString("Author"),res->getString("Born-Diec"),
			   res->getString("Title"),res->getString("Date"),
	    res->getString("Technique"), res->getString("Location"), res->getString("URL"), 
	    res->getString("Form"), res->getString("Type"), res->getString("School"), res->getString("Timeframe"));
	  list.push_back(entry);

      }
    } while (stmt->getMoreResults());
    return list;
}
		  
vector<artEntry> artBook::findByTitle(string findTitle)
{
  sql::Driver* driver = sql::mysql::get_driver_instance();
  std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
  con->setSchema(database);
  std::auto_ptr<sql::Statement> stmt(con->createStatement());

  vector<artEntry> list;
  stmt->execute("SELECT * FROM art WHERE Title like '%"+findTitle+"%'");
  std::auto_ptr< sql::ResultSet > res;
  do {
    res.reset(stmt->getResultSet());
    while (res->next()) {
	    artEntry entry(res->getString("Author"),res->getString("Born-Diec"),
			   res->getString("Title"),res->getString("Date"),
	    res->getString("Technique"), res->getString("Location"), res->getString("URL"), 
	    res->getString("Form"), res->getString("Type"), res->getString("School"), res->getString("Timeframe"));
	  list.push_back(entry);

    }
  } while (stmt->getMoreResults());
  return list;

}
/*
void PhoneBook::addEntry(string first,string last,string phone, string type){
  sql::Driver* driver = sql::mysql::get_driver_instance();
  std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
  con->setSchema(database);
  std::auto_ptr<sql::Statement> stmt(con->createStatement());
  if(type != "Friend" && type != "Family" && type!="Business"){
      type="Other";
  }
  stmt->execute("INSERT INTO Phonebook(First,Last,Phone,Type) VALUES ('"+first+"','"+last+"','"+phone+"','"+type+"')");
}


void PhoneBook::editEntry(string idnum,string first,string last,string phone, string type){
  sql::Driver* driver = sql::mysql::get_driver_instance();
  std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
  con->setSchema(database);
  std::auto_ptr<sql::Statement> stmt(con->createStatement());
  if(type != "Friend" && type != "Family" && type!="Business"){
    type="Other";
  }
  stmt->execute("UPDATE Phonebook SET First = '"+first+"', Last ='"+last+"', Phone ='"+phone+"', Type ='"+type+"' WHERE ID='"+idnum+"'");
}


void PhoneBook::deleteEntry(string idnum){
  sql::Driver* driver = sql::mysql::get_driver_instance();
  std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
  con->setSchema(database);
  std::auto_ptr<sql::Statement> stmt(con->createStatement());

  stmt->execute("DELETE FROM Phonebook WHERE ID='"+idnum+"'");
}
*/
