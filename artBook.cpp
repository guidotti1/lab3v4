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
	//THIS NEXT DO-WHILE LOOP SHOULD BE IMPLEMENTED AS A PRIVATE MEMBER FUNCTION INSTEAD
	//AS IT IS REPEATED THROUGH EACH SEARCH TYPE
    do {
      res.reset(stmt->getResultSet());
      while (res->next()) {	   
            artEntry entry(res->getString("Author"),res->getString("Born-Diec"),
			   res->getString("Title"),res->getString("Date"),
	    res->getString("Technique"), res->getString("Location"), res->getString("URL"), 
	    res->getString("Form"), res->getString("Type"), res->getString("School"), res->getString("Timeframe"), res->getString("ARTID"));
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
	//THIS NEXT DO-WHILE LOOP SHOULD BE IMPLEMENTED AS A PRIVATE MEMBER FUNCTION INSTEAD
	//AS IT IS REPEATED THROUGH EACH SEARCH TYPE
    do {
      res.reset(stmt->getResultSet());
      while (res->next()) {	   
            artEntry entry(res->getString("Author"),res->getString("Born-Diec"),
			   res->getString("Title"),res->getString("Date"),
	    res->getString("Technique"), res->getString("Location"), res->getString("URL"), 
	    res->getString("Form"), res->getString("Type"), res->getString("School"), res->getString("Timeframe"), res->getString("ARTID"));
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
	//THIS NEXT DO-WHILE LOOP SHOULD BE IMPLEMENTED AS A PRIVATE MEMBER FUNCTION INSTEAD
	//AS IT IS REPEATED THROUGH EACH SEARCH TYPE
  do {
    res.reset(stmt->getResultSet());
    while (res->next()) {
	    artEntry entry(res->getString("Author"),res->getString("Born-Diec"),
			   res->getString("Title"),res->getString("Date"),
	    res->getString("Technique"), res->getString("Location"), res->getString("URL"), 
	    res->getString("Form"), res->getString("Type"), res->getString("School"), res->getString("Timeframe"), res->getString("ARTID"));
	  list.push_back(entry);

    }
  } while (stmt->getMoreResults());
  return list;

}

vector<artEntry> artBook::findByType(string findType)
{
  sql::Driver* driver = sql::mysql::get_driver_instance();
  std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
  con->setSchema(database);
  std::auto_ptr<sql::Statement> stmt(con->createStatement());

  vector<artEntry> list;
  stmt->execute("SELECT * FROM art WHERE Type like '%"+findType+"%'");
  std::auto_ptr< sql::ResultSet > res;
	//THIS NEXT DO-WHILE LOOP SHOULD BE IMPLEMENTED AS A PRIVATE MEMBER FUNCTION INSTEAD
	//AS IT IS REPEATED THROUGH EACH SEARCH TYPE
  do {
    res.reset(stmt->getResultSet());
    while (res->next()) {
	    artEntry entry(res->getString("Author"),res->getString("Born-Diec"),
			   res->getString("Title"),res->getString("Date"),
	    res->getString("Technique"), res->getString("Location"), res->getString("URL"), 
	    res->getString("Form"), res->getString("Type"), res->getString("School"), res->getString("Timeframe"), res->getString("ARTID"));
	  list.push_back(entry);

    }
  } while (stmt->getMoreResults());
  return list;
}

vector<artEntry> artBook::findByForm(string findForm)
{
  sql::Driver* driver = sql::mysql::get_driver_instance();
  std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
  con->setSchema(database);
  std::auto_ptr<sql::Statement> stmt(con->createStatement());

  vector<artEntry> list;
  stmt->execute("SELECT * FROM art WHERE Form like '%"+findForm+"%'");
  std::auto_ptr< sql::ResultSet > res;
	//THIS NEXT DO-WHILE LOOP SHOULD BE IMPLEMENTED AS A PRIVATE MEMBER FUNCTION INSTEAD
	//AS IT IS REPEATED THROUGH EACH SEARCH TYPE
  do {
    res.reset(stmt->getResultSet());
    while (res->next()) {
	    artEntry entry(res->getString("Author"),res->getString("Born-Diec"),
			   res->getString("Title"),res->getString("Date"),
	    res->getString("Technique"), res->getString("Location"), res->getString("URL"), 
	    res->getString("Form"), res->getString("Type"), res->getString("School"), res->getString("Timeframe"), res->getString("ARTID"));
	  list.push_back(entry);

    }
  } while (stmt->getMoreResults());
  return list;

}

vector<artEntry> artBook::findBySchool(string findSchool)
{
  sql::Driver* driver = sql::mysql::get_driver_instance();
  std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
  con->setSchema(database);
  std::auto_ptr<sql::Statement> stmt(con->createStatement());

  vector<artEntry> list;
  stmt->execute("SELECT * FROM art WHERE School like '%"+findSchool+"%'");
  std::auto_ptr< sql::ResultSet > res;
	//THIS NEXT DO-WHILE LOOP SHOULD BE IMPLEMENTED AS A PRIVATE MEMBER FUNCTION INSTEAD
	//AS IT IS REPEATED THROUGH EACH SEARCH TYPE
  do {
    res.reset(stmt->getResultSet());
    while (res->next()) {
	    artEntry entry(res->getString("Author"),res->getString("Born-Diec"),
			   res->getString("Title"),res->getString("Date"),
	    res->getString("Technique"), res->getString("Location"), res->getString("URL"), 
	    res->getString("Form"), res->getString("Type"), res->getString("School"), res->getString("Timeframe"), res->getString("ARTID"));
	  list.push_back(entry);

    }
  } while (stmt->getMoreResults());
  return list;

}
