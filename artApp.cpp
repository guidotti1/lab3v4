#include <iostream>
#include <fstream>
#include <string>
#include <map>

// Stuff for AJAX
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

#include "artBook.h"
#include "artEntry.h"

#define XML_USE_STL

using namespace std;
using namespace cgicc; // Needed for AJAX functions.

ofstream logfile; 

string firstCharUpper(string s)
{
	string returnS = s;
	for (int i = 1; i < s.size(); i++)
	{
		returnS[i] =  char(tolower(s[i]));
	}
	return returnS;
}

int main() {
  Cgicc cgi;    // Ajax object
  char *cstr;

  artBook ab; // Phone Book SQL Interface Object
  vector<artEntry> abResults;
  
  // Create AJAX objects to recieve information from web page.
  form_iterator op = cgi.getElement("operation");
  string operation = **op;
  logfile.open("guidottiart.log",ios::out | ios::app);
  logfile << "Op:" << operation << endl;
  logfile.close();
  string output = "Error = "+operation+ " - Operation not support yet!";
  if (operation == "Search by last name") 
  {
    form_iterator searchString = cgi.getElement("find");
    string search = **searchString;
    
    abResults = ab.findByLast(search);
    if (abResults.size() > 0)
    	{
	      output = "";
	      for (int i = 0; i<abResults.size(); i++) 
	      {
	      	  output += firstCharUpper(abResults.at(i).last) + "^"
		  + abResults.at(i).first + "^"
		  + abResults.at(i).bornDied + "^"
		  + abResults.at(i).title + "^"
		  + abResults.at(i).date + "^"
		  + abResults.at(i).technique + "^"
		  + abResults.at(i).location + "^"
		  + abResults.at(i).url + "^"
		  + abResults.at(i).form + "^"
		  + abResults.at(i).type + "^"
		  + abResults.at(i).school + "^"
		  + abResults.at(i).timeframe + "^"
	          + abResults.at(i).ARTID + "^";
      	     }
    	}
  else 
    	{
		output = "No Match Found";
    	}
  }

  if (operation == "Search by first name") 
  {
    form_iterator searchString = cgi.getElement("find");
    string search = **searchString;
    
    abResults = ab.findByFirst(search);
    if (abResults.size() > 0)
    	{
	      //output = "success";
	      output = "";
	      for (int i = 0; i<abResults.size(); i++) 
	      {
	      	  output +=  firstCharUpper(abResults.at(i).last) + "^"
		  + abResults.at(i).first + "^"
		  + abResults.at(i).bornDied + "^"
		  + abResults.at(i).title + "^"
		  + abResults.at(i).date + "^"
		  + abResults.at(i).technique + "^"
		  + abResults.at(i).location + "^"
		  + abResults.at(i).url + "^"
		  + abResults.at(i).form + "^"
		  + abResults.at(i).type + "^"
		  + abResults.at(i).school + "^"
		  + abResults.at(i).timeframe + "^"
		  + abResults.at(i).ARTID + "^";
      	     }
    }
  else 
    {
    	output = "No Match Found";
    }
  }
	
  if (operation == "Search by title") 
  {
    form_iterator searchString = cgi.getElement("find");
    string search = **searchString;
    
    abResults = ab.findByTitle(search);
    if (abResults.size() > 0)
    	{
	      //output = "success";
	      output = "";
	      for (int i = 0; i<abResults.size(); i++) 
	      {
	      	  output += firstCharUpper(abResults.at(i).last) + "^"
		  + abResults.at(i).first + "^"
		  + abResults.at(i).bornDied + "^"
		  + abResults.at(i).title + "^"
		  + abResults.at(i).date + "^"
		  + abResults.at(i).technique + "^"
		  + abResults.at(i).location + "^"
		  + abResults.at(i).url + "^"
		  + abResults.at(i).form + "^"
		  + abResults.at(i).type + "^"
		  + abResults.at(i).school + "^"
		  + abResults.at(i).timeframe + "^"
		  + abResults.at(i).ARTID + "^";
      	     }
    }
  else 
    {
      	output = "No Match Found";
    }
  }
	
  if (operation == "Search by form") 
  {
    form_iterator searchString = cgi.getElement("find");
    string search = **searchString;
    
    abResults = ab.findByForm(search);
    if (abResults.size() > 0)
    	{
	      //output = "success";
	      output = "";
	      for (int i = 0; i<abResults.size(); i++) 
	      {
	      	  output += firstCharUpper(abResults.at(i).last) + "^"
		  + abResults.at(i).first + "^"
		  + abResults.at(i).bornDied + "^"
		  + abResults.at(i).title + "^"
		  + abResults.at(i).date + "^"
		  + abResults.at(i).technique + "^"
		  + abResults.at(i).location + "^"
		  + abResults.at(i).url + "^"
		  + abResults.at(i).form + "^"
		  + abResults.at(i).type + "^"
		  + abResults.at(i).school + "^"
		  + abResults.at(i).timeframe + "^"
		  + abResults.at(i).ARTID + "^";
      	     }
    }
  else 
    {
      	output = "No Match Found";
    }
  }
	
  if (operation == "Search by school") 
  {
    form_iterator searchString = cgi.getElement("find");
    string search = **searchString;
    
    abResults = ab.findBySchool(search);
    if (abResults.size() > 0)
    	{
	      //output = "success";
	      output = "";
	      for (int i = 0; i<abResults.size(); i++) 
	      {
	      	  output += firstCharUpper(abResults.at(i).last) + "^"
		  + abResults.at(i).first + "^"
		  + abResults.at(i).bornDied + "^"
		  + abResults.at(i).title + "^"
		  + abResults.at(i).date + "^"
		  + abResults.at(i).technique + "^"
		  + abResults.at(i).location + "^"
		  + abResults.at(i).url + "^"
		  + abResults.at(i).form + "^"
		  + abResults.at(i).type + "^"
		  + abResults.at(i).school + "^"
		  + abResults.at(i).timeframe + "^"
		  + abResults.at(i).ARTID + "^";
      	     }
    }
  else 
    {
      	output = "No Match Found";
    }
  }
	
  if (operation == "Search by type") 
  {
    form_iterator searchString = cgi.getElement("find");
    string search = **searchString;
    
    abResults = ab.findByType(search);
    if (abResults.size() > 0)
    	{
	      //output = "success";
	      output = "";
	      for (int i = 0; i<abResults.size(); i++) 
	      {
	      	  output += firstCharUpper(abResults.at(i).last) + "^"
		  + abResults.at(i).first + "^"
		  + abResults.at(i).bornDied + "^"
		  + abResults.at(i).title + "^"
		  + abResults.at(i).date + "^"
		  + abResults.at(i).technique + "^"
		  + abResults.at(i).location + "^"
		  + abResults.at(i).url + "^"
		  + abResults.at(i).form + "^"
		  + abResults.at(i).type + "^"
		  + abResults.at(i).school + "^"
		  + abResults.at(i).timeframe + "^"
		  + abResults.at(i).ARTID + "^";
      	     }
    }
  else 
    {
      	output = "No Match Found";
    }
  }
	
  	
	

  cout << "Content-Type: text/plain\n\n";

  cout << output << endl;
  
  
  return 0;
}

