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

void appendResults(vector<artEntry>abResults,string&output);
//where abResults is initiated according to search type
//output changed according to search results
//if abResults.size()=0, output="No Match Found"

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
	//"operation" is search type: last name, first name, title, form, school, & type
  string operation = **op;
	
  logfile.open("guidottiart.log",ios::out | ios::app);
  logfile << "Op:" << operation << endl;
  logfile.close();
  string output = "Error = "+operation+ " - Operation not support yet!";
	
  //find results according to operation
  if (operation == "Search by Last Name") 
  {
    form_iterator searchString = cgi.getElement("find");
    string search = **searchString;
    
    abResults = ab.findByLast(search);
    //append abResults to output
    appendResults(abResults,output);
  }

  if (operation == "Search by First Name") 
  {
    form_iterator searchString = cgi.getElement("find");
    string search = **searchString;
    
    abResults = ab.findByFirst(search);
    appendResults(abResults,output);
  }
	
  if (operation == "Search by Title") 
  {
    form_iterator searchString = cgi.getElement("find");
    string search = **searchString;
    
    abResults = ab.findByTitle(search);
    appendResults(abResults,output);
  }
	
  if (operation == "Search by Form") 
  {
    form_iterator searchString = cgi.getElement("find");
    string search = **searchString;
    
    abResults = ab.findByForm(search);
    appendResults(abResults,output);
  }
	
  if (operation == "Search by School") 
  {
    form_iterator searchString = cgi.getElement("find");
    string search = **searchString;
    
    abResults = ab.findBySchool(search);
    appendResults(abResults,output);
  }
	
  if (operation == "Search by Type") 
  {
    form_iterator searchString = cgi.getElement("find");
    string search = **searchString;
    
    abResults = ab.findByType(search);
    appendResults(abResults,output);
  }
	
  	
	

  cout << "Content-Type: text/plain\n\n";
 
  //return output
  cout << output << endl;
  
  
  return 0;
}


void appendResults(vector<artEntry>abResults,string&output){
	if (abResults.size() > 0)		//if there are results
    	{
	      //output = "success";
	      output = "";			//empty output
	      for (int i = 0; i<abResults.size(); i++) 
	      {					//artEntry components delineated by "^"
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

